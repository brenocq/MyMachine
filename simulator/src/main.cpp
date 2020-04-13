#include <fstream>
#include <iostream>
#include <string>
#include "../../assembler/lib/defines.h"
#include "simulator.h"

using namespace std;

void errorNoFiles(string fileName);
void errorTooManyFiles(string fileName);
void checkFile(string &inName);

int main(int argc, char *argv[])
{
	// Input output files
	string inName;

	cout << BOLDWHITE << "BrenoCQ Simulator" << RESET <<endl;
    if (argc < 2)
    {
		errorNoFiles(argv[0]);
	}
	else if(argc>2)
	{
		errorTooManyFiles(argv[0]);
    }
	else if(argc==2)
	{
		inName = argv[1];
		checkFile(inName);
	}

	// Simulator
	Simulator *simulator = new Simulator(inName);
	simulator->run();
	
	delete(simulator);

    return 0;
}

void errorNoFiles(string fileName)
{
	cout << BOLDRED << "[ERROR] " << RED << "No input file found" << RESET <<endl; 
	cout << "\t" << "Please use the following:" << RESET <<endl;
	cout << "\t" << fileName << " <.bbin file>" <<endl;
	exit(0);
}

void errorTooManyFiles(string fileName)
{
	cout << BOLDRED << "[ERROR] " << RED << "Too many files as arguments" << RESET <<endl; 
	cout << "\t" << "Please use the following:" << RESET <<endl;
	cout << "\t" << fileName << " <.bbin file>" <<endl;
	exit(0);
}

void checkFile(string &inName)
{
	size_t basmPos = inName.find(".bbin");

	if(basmPos == string::npos || basmPos > 100)
	{
		cout << BOLDRED << "[ERROR] " << RED << "File must be .bbin" << RESET <<endl; 
		cout << RED << "\tFound: " << RESET << inName <<endl;
		exit(0);
	}
	else
	{
		cout << BOLDGREEN << "[OK] " << GREEN << "Input file ok" << RESET <<endl; 
		cout << GREEN << "\tInput: " << RESET << inName <<endl;
	}
}
