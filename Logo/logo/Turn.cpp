#include "Turn.h"

#include "Turtle.h"

namespace logo {

Turn::Turn(TokenList const &tokens, TokenList::const_iterator &currentPos, bool clockwise) :
	UnaryInstruction(tokens, currentPos),
	isClockwise(clockwise)
{
}

void Turn::doExecute(Interpreter &interpreter) const
{
	turtle::turtleDir += isClockwise ? myParameter : -myParameter;
}

void Turn::doDisplay(std::ostream &os) const
{
	os << (isClockwise ? "Droite " : "Gauche ") << myParameter;
}



} // namespace logo
