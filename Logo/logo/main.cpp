#include <iostream>
#include "Interpreter.h"
#include "Instruction.h"
#include "Turtle.h"
#include <cstdio>
#include <sstream>
#include <fstream>

using namespace std;

void usage()
{
	cout << "logo file delay" << endl;
	cout << "\tfile: Path of the logo program to run" << endl;
	cout << "\tdelay: Delay to allow the user to see how the turtle moves [s]" << endl;
}


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		usage();
		return EXIT_FAILURE;
	}
	std::ifstream ifs(argv[1]);
	if (!ifs)
	{
		usage();
		return EXIT_FAILURE;
	}
	std::istringstream iss(argv[2]);
	float delay;
	iss >> delay;
	if (!iss)
	{
		usage();
		return EXIT_FAILURE;
	}

	logo::Interpreter interpreter(ifs);
	cout << interpreter.compilationMessage() << (interpreter.isProgramValid() ? " (valid)" : " (invalid)") << endl;
	if(!interpreter.isProgramValid())
	{
		return EXIT_FAILURE;
	}
	interpreter.display(cout);
	turtle::initTurtle();
	interpreter.startProgram();
	while (!turtle::interrupt() && interpreter.isProgramRunning())
	{
		// interpreter.showTrace(cout);
		interpreter.nextStep();
		turtle::redraw();
		turtle::rest(delay);
	}
	turtle::waitEnd();
	turtle::uninitTurtle();
    return 0;
}
