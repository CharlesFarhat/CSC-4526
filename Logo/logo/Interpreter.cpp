#include "Interpreter.h"

#include <sstream>
#include "Lexer.h"
#include <stdexcept>
#include "Program.h"
#include "ExecutionContext.h"
#include <cassert>
#include "Instruction.h"


namespace logo {

Interpreter::Interpreter(std::string const &code)
{
	parse(code);
}

Interpreter::Interpreter(std::istream &is)
{
	std::stringstream buffer;
	buffer << is.rdbuf();
	std::string code = buffer.str();
	parse(code);
}

Interpreter::~Interpreter()
{
}

bool Interpreter::isProgramValid()
{
	return static_cast<bool>(myProgram);
}

std::string Interpreter::compilationMessage()
{
	return myCompilationMessage;
}

void Interpreter::startProgram()
{
	myCallStack.clear();
	myCallStack.push_back(ExecutionContext{ myProgram->begin(), myProgram->end(), *this });
}

bool Interpreter::isProgramRunning()
{
	return !myCallStack.empty();
}

void Interpreter::nextStep()
{
	if (isProgramRunning())
	{
		auto instruction = currentInstruction();
		instruction->execute(*this);
		auto newInstruction = instruction->getNext(*this, GetNextReason::FinishedInstruction);
		while (newInstruction == endOfBlock())
		{
			myCallStack.pop_back();
			if (myCallStack.empty())
			{
				return;
			}
			newInstruction = currentInstruction()->getNext(*this, GetNextReason::BackFromSubroutine);
		}
		myCallStack.back().setCurrentPos(newInstruction);
	}
}

Instruction *Interpreter::currentInstruction()
{
	return currentPos()->get();
}

InstructionPointer Interpreter::currentPos()
{
	assert(isProgramRunning());
	return myCallStack.back().currentPos();
}
InstructionPointer Interpreter::endOfBlock()
{
	assert(isProgramRunning());
	return myCallStack.back().endOfBlock();
}


void Interpreter::pushNewContext(ExecutionContext &&ec)
{
	myCallStack.push_back(ec);
}

void Interpreter::showTrace(std::ostream &os)
{
	if (!isProgramRunning())
	{
		os << "Program stopped";
		return;
	}
	os << std::string(myCallStack.size() - 1, '\t') << (**myCallStack.back().currentPos()) << std::endl;
}


void Interpreter::display(std::ostream &os)
{
	myProgram->display(os, true);
}
void Interpreter::parse(std::string const &code)
{
	try
	{
		TokenList tokens = getTokens(code);
		TokenList::const_iterator currentToken = tokens.begin();
		myProgram = std::make_unique<Program>(tokens, currentToken, nullptr);
	}
	catch(std::runtime_error &e)
	{
		myCompilationMessage = e.what();
		myProgram.release();
	}
}


} // namespace logo
