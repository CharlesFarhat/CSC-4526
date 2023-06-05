#include "ExecutionContext.h"
#include "Interpreter.h"

namespace logo {
	ExecutionContext::ExecutionContext(InstructionList::iterator startingPos, InstructionPointer endOfBlock, Interpreter &interpreter) :
		myCurrentPos(startingPos),
		myEndOfBlock(endOfBlock),
		myInterpreter(interpreter)
	{
	}

	int &ExecutionContext::variable(std::string const &name)
	{
		return myVariables[name];
	}

	InstructionPointer ExecutionContext::currentPos()
	{
		return myCurrentPos;
	}

	void ExecutionContext::setCurrentPos(InstructionPointer pos)
	{
		myCurrentPos = pos;
	}

	InstructionPointer ExecutionContext::endOfBlock()
	{
		return myEndOfBlock;
	}




} // logo 

