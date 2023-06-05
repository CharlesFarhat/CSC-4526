#ifndef TURN_H
#define TURN_H

#include "Lexer.h"
#include "UnaryInstruction.h"

namespace logo {

class Turn : public UnaryInstruction
{
public:
	Turn(TokenList const &tokens, TokenList::const_iterator &currentPos, bool clockwise);
private:
	virtual void doExecute(Interpreter &interpreter) const;
	virtual void doDisplay(std::ostream &os) const;
	bool isClockwise;
};

} // namespace logo



#endif // TURN_H
