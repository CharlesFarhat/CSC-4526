#include "SetPenPos.h"

#include "Turtle.h"

namespace logo {

SetPenPos::SetPenPos(TokenList const &tokens, TokenList::const_iterator &currentPos, bool up) :
	isUp(up)
{
}

void SetPenPos::doExecute(Interpreter &interpreter) const
{
	turtle::turtlePenDown = !isUp;
}

void SetPenPos::doDisplay(std::ostream &os) const
{
	os << (isUp ? "Lève" : "Baisse");
}



} // namespace logo
