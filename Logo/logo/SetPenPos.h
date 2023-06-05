#ifndef SETPENPOS_H
#define SETPENPOS_H


#include "Lexer.h"
#include "UnaryInstruction.h"

namespace logo {

class SetPenPos : public Instruction
{
public:
	SetPenPos(TokenList const &tokens, TokenList::const_iterator &currentPos, bool up);
private:
	virtual void doExecute(Interpreter &interpreter) const;
	virtual void doDisplay(std::ostream &os) const;
	bool isUp;
};

} // namespace logo


#endif // SETPENPOS_H
