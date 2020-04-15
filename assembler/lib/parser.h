#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "parser.h"
#include "defines.h"
#include "shared.h"

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();

	void removeComments(string &line);
	int getCode(string line);
	int getDefineCode(string line);
	int getWriteCode(string line);
	string getDefineName(string line);
	string getLabelName(string line);
	void getDefine(string line, string &str);
	void getDefine(string line, int &integer);
	void getDefine(string line, char &character);
	void getDefine(string line, bool &boolean);
	void getRegisters(string line, Register &rs1, Register &rs2, Register &rt);
	void getRegisters(string line, Register &rs, Register &rt);
	void getConstant(string line, int &value);
	void getJumpArguments(string line, Register &rs1, Register &rs2, Label &label);
private:
	vector<string> splitLine(string line);
	void trimWord(string &word);
	bool isLabel(string line);
	bool isDefine(string line);
	bool isWrite(string line);

	Shared *shared;
};
#endif// PARSER_H
