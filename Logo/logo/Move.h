#ifndef MOVE_H
#define MOVE_H

#include "Lexer.h"
#include "UnaryInstruction.h"

namespace logo {

class Move : public UnaryInstruction
{
public:
	Move(TokenList const &tokens, TokenList::const_iterator &currentPos, bool forward);
private:
	virtual void doExecute(Interpreter &interpreter) const;
	virtual void doDisplay(std::ostream &os) const;
	bool isForward;
};

} // namespace logo


#endif // MOVE_H
