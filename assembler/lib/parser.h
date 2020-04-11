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
	void getDefine(string line, string &name, int &value);
	void getRegisters(string line, int &rs1, int &rs2, int &rt);
	void getRegisters(string line, int &rs, int &rt);
	void getConstant(string line, int &value, bool &isNumber);
private:
	vector<string> splitLine(string line);
	void trimWord(string &word);
	bool isLabel(string line);

	Shared *shared;
};
#endif// PARSER_H
