#include "Program.h"

#include "FunctionCall.h"
#include "Move.h"
#include "Turn.h"
#include "SetPenPos.h"
#include <cassert>

using std::endl;

// A ajouter si le compilo ne connait pas make_unique
/*namespace std{
template<class T, class... Args>
unique_ptr<T> make_zunique(Args &&... args)
{
return unique_ptr<T>(new T(forward<Args>(args)...));
}
}*/

namespace logo {

Program::Program(TokenList const &tokens, TokenList::const_iterator &currentToken, Program *mainProgram) :
	isMainProgram(mainProgram == NULL)
{
	if (mainProgram == NULL)
	{
		mainProgram = this;
	}

	bool endProgram = false;
	while (currentToken != tokens.end() && !endProgram)
	{
		switch (currentToken->first)
		{
		case TokenKeyword:
			parseKeyword(tokens, currentToken, endProgram, mainProgram);
			break;
		case TokenName:
			{
				std::string name = currentToken->second;
				currentToken++;
				myInstructions.push_back(std::make_unique<FunctionCall>(*mainProgram, name, currentToken));
			}
			break;
		default:
			throw ParseError("Unexpected token type", currentToken);
		}
	}
}

Program::~Program()
{
}


void Program::display(std::ostream &os, bool subFunctions) const
{
	if (subFunctions)
	{
		for (auto const &func : myFunctions)
		{
			os << "Pour " << func.first << endl;
			func.second->display(os, false);
			os << "Fin" << endl;
		}
	}

	for (auto const &instr : myInstructions)
	{
		instr->display(os);
		os << std::endl;
	}
}

void Program::parseKeyword(TokenList const &tokens, TokenList::const_iterator &token, bool &endProgram, Program *mainProgram)
{
	if(token->second == kwForward)
	{
		myInstructions.push_back(std::make_unique <Move>(tokens, ++token, true));
	}
	else if(token->second == kwBackward)
	{
		myInstructions.push_back(std::make_unique<Move>(tokens, ++token, false));
	}
	else if(token->second == kwLeft)
	{
		myInstructions.push_back(std::make_unique <Turn>(tokens, ++token, false));
	}
	else if(token->second == kwRight)
	{
		myInstructions.push_back(std::make_unique <Turn>(tokens, ++token, true));
	}
	else if(token->second == kwUp)
	{
		myInstructions.push_back(std::make_unique <SetPenPos>(tokens, ++token, true));
	}
	else if(token->second == kwDown)
	{
		myInstructions.push_back(std::make_unique <SetPenPos>(tokens, ++token, false));
	}
	else if(token->second == kwFctDecl)
	{
		if (!isMainProgram)
		{
			throw ParseError("Functions cannot be nested", token);
		}
		++token;
		if (token->first != TokenName)
		{
			throw ParseError("Invalid function name", token);
		}
		std::string fctName = token->second;
		FunctionList::const_iterator it = myFunctions.find(fctName);
		if (it != myFunctions.end())
		{
			throw ParseError("Function redefinition", token);
		}
		++token;
		myFunctions.insert(std::make_pair(fctName, std::make_unique <Program>(tokens, token, mainProgram)));
	}
	else if(token->second == kwEnd)
	{
		++token;
		endProgram = true;
	}
	else
	{
		throw ParseError("Unimplemented keyword", token);
	}
}

Program *Program::findSubProgram(std::string const &name) const
{
	assert(isMainProgram);
	FunctionList::const_iterator it = myFunctions.find(name);
	return (it == myFunctions.end()) ? nullptr : it->second.get();
}

} // namespace logo


