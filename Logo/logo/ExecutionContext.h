#ifndef EXECUTION_CONTEXT_H
#define EXECUTION_CONTEXT_H

#include <string>
#include <map>

#include "Instruction.h"

namespace logo {

class Interpreter;

class ExecutionContext
{
public:
	ExecutionContext(InstructionPointer startingPos, InstructionPointer endOfBlock, Interpreter &interpreter);
	int &variable(std::string const &name); // TODO: Handle other types
	InstructionPointer currentPos();
	InstructionPointer endOfBlock();
	void setCurrentPos(InstructionPointer pos);
private:
	Interpreter &myInterpreter;
	InstructionPointer myCurrentPos;
	InstructionPointer myEndOfBlock;
	std::map<std::string, int> myVariables;
};

} // namespace logo

#endif // EXECUTION_CONTEXT_H
