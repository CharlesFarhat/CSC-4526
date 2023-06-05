#ifndef UNARYINSTRUCTION_H
#define UNARYINSTRUCTION_H

#include "Lexer.h"
#include "Instruction.h"

namespace logo {

class UnaryInstruction : public Instruction
{
public:
	UnaryInstruction(TokenList const &tokens, TokenList::const_iterator &currentPos);
protected:
	int myParameter;
};

} // namespace logo

#endif // UNARYINSTRUCTION_H
