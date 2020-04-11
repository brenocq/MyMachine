#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "parser.h"
#include "shared.h"

using namespace std;

class Assembler
{
public:
	Assembler(string inName, string outName);
	~Assembler();

	void run(void);
private:
	void checkError(int code, string line);
	void checkLabel(int code, string line);

	string writeDInstruction(Command command, string line);
	string writeRInstruction(Command command, string line);
	string writeCInstruction(Command command, string line);
	string writeJInstruction(Command command, string line);
	string writeTInstruction(Command command, string line);
	string writeWInstruction(Command command, string line);
	
	string toBinary(int value);

	// Parser
	Parser *parser;
	// Shared
	Shared *shared;

	// Input/Output files
	ifstream in;
	ofstream out;

	// Counters
	int lineCounter;
};
#endif// ASSEMBLER_H
