#ifndef LOGOINTERPRETER_H
#define LOGOINTERPRETER_H

#include <string>
#include <istream>
#include <memory>
#include <vector>
#include "ExecutionContext.h"

namespace logo {

class Program;
class Instruction;

class Interpreter
{
public:
    Interpreter(std::string const &code);
    Interpreter(std::istream &is);
	~Interpreter();
    bool isProgramValid();
    std::string compilationMessage();

	void startProgram(); // If a program was already running, kill it
    void nextStep(); // Run one step of the program
	bool isProgramRunning(); // Return true between the call of startProgram and the end of execution
	void pushNewContext(ExecutionContext &&ec);

	Instruction *currentInstruction();
	InstructionPointer currentPos();
	InstructionPointer endOfBlock();

	void showTrace(std::ostream &os); // Disply the current position in the execution
    void display(std::ostream &os); // Display the content of the source code

private:
    void parse(std::string const &code);
    std::string myCompilationMessage;
    std::unique_ptr<Program> myProgram;
	std::vector<ExecutionContext> myCallStack;
};

} // namespace logo


#endif // LOGOINTERPRETER_H
