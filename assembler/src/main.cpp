#include <fstream>
#include <iostream>
#include <string>
#include "defines.h"
#include "parser.h"
#include "assembler.h"

using namespace std;

void errorNoFiles(string fileName);
void errorTooManyFiles(string fileName);
void checkOneFiles(string &inName,string &outName);
void checkTwoFile(string &inName,string &outName);

int main(int argc, char *argv[])
{
	// Input output files
	string inName;
	string outName;

	cout << BOLDWHITE << "BrenoCQ Assembler" << RESET <<endl;
    if (argc < 2)
    {
		errorNoFiles(argv[0]);
	}
	else if(argc>3)
	{
		errorTooManyFiles(argv[0]);
    }
	else if(argc==2)
	{
		inName = argv[1];
		checkOneFiles(inName, outName);
	}
	else if(argc==3)
	{
		inName = argv[1];
		outName = argv[2];
		checkTwoFile(inName, outName);
	}

	// Assembler
	Assembler *assembler = new Assembler(inName, outName);
	assembler->run();
	
	delete(assembler);

    return 0;
}

void errorNoFiles(string fileName)
{
	cout << BOLDRED << "[ERROR] " << RED << "No input file found" << RESET <<endl; 
	cout << "\t" << "Please use one of the following:" << RESET <<endl;
	cout << "\t" << fileName << " <in .basm file>" <<endl;
	cout << "\t" << fileName << " <in .basm file> <out .bbin file>" <<endl;
	exit(0);
}

void errorTooManyFiles(string fileName)
{
	cout << BOLDRED << "[ERROR] " << RED << "Too many files as arguments" << RESET <<endl; 
	cout << "\t" << "Please use one of the following:" << RESET <<endl;
	cout << "\t" << fileName << " <in .basm file>" <<endl;
	cout << "\t" << fileName << " <in .basm file> <out .bbin file>" <<endl;
	exit(0);
}

void checkOneFiles(string &inName,string &outName)
{
	size_t basmPos = inName.find(".basm");

	if(basmPos == string::npos || basmPos > 100)
	{
		cout << BOLDRED << "[ERROR] " << RED << "File must be .basm" << RESET <<endl; 
		cout << RED << "\tFound: " << RESET << inName <<endl;
		exit(0);
	}
	else
	{
		outName = inName;
		outName.replace(basmPos, basmPos+4, ".bbin");

		cout << BOLDGREEN << "[OK] " << GREEN << "Input file ok" << RESET <<endl; 
		cout << GREEN << "\tInput: " << RESET << inName <<endl;
		cout << GREEN << "\tOutput: " << RESET << outName <<endl;
	}
}

void checkTwoFile(string &inName,string &outName)
{
	size_t basmPos = inName.find(".basm");
	size_t bbinPos = outName.find(".bbin");

	if(basmPos == string::npos || basmPos > 100 || bbinPos == string::npos || bbinPos > 100)
	{
		cout << BOLDRED << "[ERROR] " << RED << "First file must be .basm and second must be .bbin" << RESET <<endl; 
		cout << RED << "\tInput: " << RESET << inName <<endl;
		cout << RED << "\tOutput: " << RESET << outName <<endl;
		exit(0);
	}
	else
	{
		cout << BOLDGREEN << "[OK] " << GREEN << "Input file ok" << RESET <<endl; 
		cout << GREEN << "\tInput: " << RESET << inName <<endl;
		cout << GREEN << "\tOutput: " << RESET << outName <<endl;
	}
}
