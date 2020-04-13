#ifndef CODE_H
#define CODE_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <curses.h>
#include "colorManager.h"
#include "../../assembler/lib/defines.h"
#include "../../assembler/lib/shared.h"

using namespace std;

class Code
{
public:
	Code();
	~Code();

	void display(void);
	void setWindow(WINDOW *_win);
	void setRegisters(vector<int> *_registers);
	void setLines(vector<string> *_lines);
private:
	void getLineArgs(Command command, string lineBin, string &arg1, string &arg2, string &arg3);

	vector<string> buffer;

	ColorManager *cm;
	WINDOW *win;
	int maxX, maxY;
	Shared *shared;

	// Input file lines
	vector<string> *lines;
	// Registers
	vector<int> *registers;
};
#endif// CODE_H
