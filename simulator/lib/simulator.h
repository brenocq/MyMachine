#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <curses.h>
#include "defines.h"
#include "window.h"
#include "terminal.h"
#include "topbar.h"
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

	// Window
	Window *window;
	// Terminal
	Terminal *terminal;
	// Top bar
	Topbar *topbar;
	// Color Manager
	ColorManager *cm; 

	//--------------- Window --------------//
	int maxX, maxY;

	//--------------- Machine -------------//
	// Input file
	ifstream in;
	// Counters
	int lineCounter;
	// Registers
	vector<int> *registers;
};
#endif// SIMULATOR_H
