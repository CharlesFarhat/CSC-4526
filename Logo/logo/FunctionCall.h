#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include "Lexer.h"
#include "Instruction.h"
#include "Program.h"
#include <vector>

namespace logo {

class FunctionCall : public Instruction
{
public:
	FunctionCall(Program const &mainProgram, std::string name, TokenList::const_iterator &currentPos);
private:
	virtual void doExecute(Interpreter &interpreter) const override;
	virtual InstructionPointer doGetNext(Interpreter &interpreter, GetNextReason reason) const override;
	virtual void doDisplay(std::ostream &os) const override;
	Program const &myMainProgram;
	std::string myName;
};

} // namespace logo



#endif // FUNCTION_CALL_H
