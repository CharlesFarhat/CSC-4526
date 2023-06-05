#ifndef LOGOPROGRAM_H
#define LOGOPROGRAM_H

#include "Lexer.h"
#include <vector>
#include "Instruction.h"
#include <map>
#include <memory>

namespace logo {


class Program
{
public:
	/**
	 * Functions can only be defined at the main program level
	 * If mainProgram is NULL, we are creating a main program
	 */
	Program(TokenList const &tokens, TokenList::const_iterator &currentToken, Program *mainProgram);
	~Program();

	typedef std::map<std::string, std::unique_ptr<Program>> FunctionList;

	void display(std::ostream &os, bool subFunctions) const;

	InstructionPointer begin() { return myInstructions.begin(); }
	InstructionPointer end() { return myInstructions.end(); }
	Program *findSubProgram(std::string const &name) const;

private:
	// Prevent automatic generation
	Program(Program const &source);
	Program &operator=(Program const &source);

	void parseKeyword(TokenList const &tokens, TokenList::const_iterator &token, bool &endProgram, Program *mainProgram);

	InstructionList myInstructions;
	FunctionList myFunctions;
	bool isMainProgram;


};

} // namespace logo


#endif // LOGOPROGRAM_H
