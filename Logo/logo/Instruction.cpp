#include "Instruction.h"
#include "Interpreter.h"
#include <cassert>

namespace logo {

Instruction::~Instruction()
{
}

void Instruction::execute(Interpreter &ec) const
{
	doExecute(ec);
}

InstructionPointer Instruction::getNext(Interpreter &interpreter, GetNextReason reason) const
{
	return doGetNext(interpreter, reason);
}

void Instruction::display(std::ostream &os) const
{
	doDisplay(os);
}

std::ostream &operator<<(std::ostream &os, Instruction const &i)
{
	i.display(os);
	return os;
}

InstructionPointer Instruction::doGetNext(Interpreter &interpreter, GetNextReason reason) const
{
	assert(reason == GetNextReason::FinishedInstruction);
	return ++interpreter.currentPos();
}


ParseError::ParseError(std::string const &whatString, TokenList::const_iterator errorPos) :
	std::runtime_error(whatString + " (token: " + errorPos->second + ")"),
	myErrorPos(errorPos)
{
}

TokenList::const_iterator ParseError::errorPos()
{
	return myErrorPos;
}


} // namespace logo
