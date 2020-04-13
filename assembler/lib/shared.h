#ifndef SHARED_H
#define SHARED_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "defines.h"

using namespace std;

struct Command{
	string str;
	int code;
	string binary;
	char instructionType;
};

struct Register{
	string str;
	int code;
	string binary;
};

struct Label{
	string name;
	int lineNumber;
};

struct Constant{
	string name;
	int value;
};

class Shared
{
public:
	Shared();
	~Shared();

	static Command getCommand(int code);
	static Command getCommand(string str);
	static Command getCommandByOpCode(string opCode);
	static Register getRegister(int code);
	static Register getRegister(string str);
	static Label getLabel(string name);
	static Constant getConstant(string name);

	static void getRegistersByBin(string lineBin, Register &rs1, Register &rs2, Register &rt);
	static void getConstantByBin(string lineBin, Register &rs, Register &rt, int &constant, bool &isNumber);
private:
	static void initCommands(void);
	static void initRegisters(void);
	
	// Commands
	static vector<Command> commands;	

	// Registers
	static vector<Register> registers;	

	// Labels
	static vector<Label> labels;

	// Constants
	static vector<Constant> constants;	
};
#endif// SHARED_H
