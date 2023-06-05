#include "Move.h"

#include "Turtle.h"
#include <cmath>


using namespace turtle;

namespace logo {

Move::Move(TokenList const &tokens, TokenList::const_iterator &currentPos, bool forward) :
	UnaryInstruction(tokens, currentPos),
	isForward(forward)
{
}

void Move::doExecute(Interpreter &interpreter) const
{
	int value = isForward ? myParameter : -myParameter;
	// By convention, an angle of 0 is to the screen top, a positive angle is clockwise
	double oldX = turtleX;
	double oldY = turtleY;
	turtleX += value * std::sin(turtleDir*DEGREE_TO_RADIAN);
	turtleY -= value * std::cos(turtleDir*DEGREE_TO_RADIAN);
	if (turtlePenDown)
	{
		turtle::drawLine(oldX, oldY, turtleX, turtleY, turtleColor);
	}
}

void Move::doDisplay(std::ostream &os) const
{
	os << (isForward ? "Avance " : "Recule ") << myParameter;
}

} // namespace logo

