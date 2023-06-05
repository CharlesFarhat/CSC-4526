#include "FunctionCall.h"
#include "Interpreter.h"
#include <cassert>

namespace logo {

FunctionCall::FunctionCall(Program const &mainProgram, std::string name, TokenList::const_iterator &currentPos) :
	myMainProgram(mainProgram),
	myName(name)
{
}

void FunctionCall::doExecute(Interpreter &interpreter) const
{
	Program *prog = myMainProgram.findSubProgram(myName);
	interpreter.pushNewContext(ExecutionContext{ prog->begin(), prog->end(), interpreter });
}

InstructionPointer FunctionCall::doGetNext(Interpreter &interpreter, GetNextReason reason) const
{
	if (reason == GetNextReason::FinishedInstruction)
	{
		// A function call doExecute has already preapared the call stack for next execution, no need to increment execution pointer
		return interpreter.currentPos();
	}
	else if (reason == GetNextReason::BackFromSubroutine)
	{
		return ++interpreter.currentPos();
	}
	else
	{
		assert(false);
		return interpreter.endOfBlock(); // Premature exit in case of error
	}
}


void FunctionCall::doDisplay(std::ostream &os) const
{
	os << "Calling " << myName;
}


} // namespace logo

