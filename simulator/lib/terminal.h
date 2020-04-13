#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <curses.h>
#include "colorManager.h"

using namespace std;

class Terminal
{
public:
	Terminal();
	~Terminal();

	void display(void);
	void setWindow(WINDOW *_win);

	void printint(int constant);
	void printchar(char constant);
	void printnl();
private:
	void cleanTerminal();
	deque<string> buffer;

	WINDOW *win;
	int maxX, maxY;

	ColorManager *cm;
};
#endif// TERMINAL_H
