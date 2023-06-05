#ifndef LOGOINSTRUCTION_H
#define LOGOINSTRUCTION_H

#include <ostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Lexer.h"

namespace logo {

class Interpreter;
class Instruction;
typedef std::vector<std::unique_ptr<Instruction>> InstructionList;
typedef InstructionList::iterator InstructionPointer;

enum class GetNextReason
{
	FinishedInstruction,
	BackFromSubroutine
};

/**
 * This is the virtual base class of all logo instructions
 */
class Instruction
{
public:
	virtual ~Instruction();
	void execute(Interpreter &ec) const;
	InstructionPointer getNext(Interpreter &interpreter, GetNextReason reason) const;
	void display(std::ostream &os) const;
private:
	virtual void doExecute(Interpreter &ec) const = 0;
	virtual InstructionPointer doGetNext(Interpreter &interpreter, GetNextReason reason) const;
	virtual void doDisplay(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, Instruction const &i);

/**
 * Exception class thrown when meeting an error
 */
class ParseError : public std::runtime_error
{
public:
	ParseError(std::string const &whatString, TokenList::const_iterator errorPos);
	TokenList::const_iterator errorPos();
private:
	TokenList::const_iterator myErrorPos;
};

typedef std::vector<std::unique_ptr<Instruction>> InstructionList;

} // namespace logo

#endif // LOGOINSTRUCTION_H

