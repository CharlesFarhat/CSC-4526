#include "Lexer.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

namespace logo {

char const *keywords[] =
{
	kwRepeat,
	kwFctDecl,
	kwForward,
	kwBackward,
	kwRight,
	kwLeft,
	kwUp,
	kwDown,
	kwEnd
};

int const nbKeywords = sizeof(keywords)/sizeof(keywords[0]);

bool isSpace(char c)
{
	static string const spaces(" \t\n");
	return (spaces.find(c) != string::npos);
}

bool isSign(char c)
{
	static string const signs("[]");
	return (signs.find(c) != string::npos);
}

bool isFigure(char c)
{
	static string const figures("0123456789.");
	return (figures.find(c) != string::npos);
}

bool isChar(char c)
{
	static string const chars("abcdefghijklmnopqrstuvwxyz");
	return (chars.find(c) != string::npos);
}

string getNumber(string const &s, int currentChar)
{
	string result;
	while (static_cast<unsigned int>(currentChar)<s.size() && isFigure(s[currentChar]))
	{
		result.push_back(s[currentChar]);
		++currentChar;
	}
	return result;
}

string getString(string const &s, int currentChar)
{
	string result;
	while (static_cast<unsigned int>(currentChar)<s.size() && (isChar(s[currentChar]) || isFigure(s[currentChar])))
	{
		result.push_back(s[currentChar]);
		++currentChar;
	}
	return result;
}

void addData(TokenList &tok, TokenType type, string const &data)
{
	tok.push_back(make_pair(type, data));
}

bool isKeywork(string const &s)
{
    for (int i=0 ; i<nbKeywords ; ++i)
    {
        if (s == keywords[i])
        {
            return true;
        }
    }
    return false;
}

TokenList getTokens(string const &s)
{
	TokenList result;
	size_t currentChar = 0;
	while (	currentChar < s.size())
	{
		if (isSpace(s[currentChar]))
		{
			++currentChar;
		}
		else if (isSign(s[currentChar]))
		{
			addData(result, TokenSign, string(1,s[currentChar]));
			++currentChar;
		}
		else if (isFigure(s[currentChar]))
		{
			string number = getNumber(s, currentChar);
			currentChar += number.size();
			addData(result, TokenNumber, number);
		}
		else if (isChar(s[currentChar]))
		{
			string str = getString(s, currentChar);
			currentChar += str.size();
			addData(result, isKeywork(str) ? TokenKeyword:TokenName, str);
		}
		else
		{
			std::ostringstream message;
			message << "Invalid character at position " << currentChar
				<< "(" << s[currentChar] << ")";
			throw std::runtime_error(message.str());
		}
	}
	return result;
}

} // namespace logo
