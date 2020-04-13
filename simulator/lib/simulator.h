#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <curses.h>
#include "../../assembler/lib/defines.h"
#include "../../assembler/lib/shared.h"
#include "window.h"
#include "terminal.h"
#include "topbar.h"
#include "code.h"
#include "colorManager.h"

using namespace std;

class Simulator
{
public:
	Simulator(string inName);
	~Simulator();

	void run(void);
private:
	void checkTerminalSupport();
	void createWindows();
	void defineBaseColors();
	void defineBasePairs();
	void processInputFile();

	void runCommand();

	void DInstruction(Command command, string line);
	void RInstruction(Command command, string line);
	void CInstruction(Command command, string line);
	void JInstruction(Command command, string line);
	void TInstruction(Command command, string line);
	void WInstruction(Command command, string line);

	// Window
	Window *window;
	// Terminal
	Terminal *terminal;
	// Terminal
	Code *code;
	// Top bar
	Topbar *topbar;
	// Color Manager
	ColorManager *cm; 
	// Shared
	Shared *shared;

	//--------------- Window --------------//
	int maxX, maxY;

	//--------------- Machine -------------//
	// Input file
	ifstream in;
	vector<string> lines;
	// Registers
	vector<int> registers;
};
#endif// SIMULATOR_H
