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

struct Define{
	string name;
	int memoryPos;
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
	static Constant getConstant(string name);
	static Label getLabel(string name);
	static Define getDefine(string name);
	static void insertLabel(Label label);
	static void insertDefine(Define define);

	static void getRegistersByBin(string lineBin, Register &rs1, Register &rs2, Register &rt);
	static void getConstantByBin(string lineBin, Register &rs, Register &rt, int &constant, bool &isNumber);
	static void getJumpByBin(string lineBin, Register &rs1, Register &rs2, int &jumpLine);
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

	// Defines
	static vector<Define> defines;	
};
#endif// SHARED_H
