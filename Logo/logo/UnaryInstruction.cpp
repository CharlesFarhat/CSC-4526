#include "UnaryInstruction.h"

#include <sstream>

namespace logo {

UnaryInstruction::UnaryInstruction(TokenList const &tokens, TokenList::const_iterator &currentPos)
{
	if (currentPos == tokens.end() || currentPos->first != TokenNumber)
	{
		throw ParseError("Instruction should be followed by a value", currentPos);
	}
	std::istringstream iss(currentPos->second);
	iss >> myParameter;
	currentPos++;
}


} // namespace logo



