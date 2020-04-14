#ifndef TOPBAR_H
#define TOPBAR_H

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

class Topbar
{
public:
	Topbar();
	~Topbar();

	void display(void);
	void setWindow(WINDOW *_win);
	void setRegisters(vector<int> *_registers);
	void setMode(string *_mode);
private:
	void cleanTopBar();
	WINDOW *win;
	int maxX, maxY;
	vector<int> *registers;
	string *mode;

	Shared *shared;
	ColorManager *cm;
};
#endif// TOPBAR_H
