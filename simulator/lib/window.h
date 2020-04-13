#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <curses.h>
#include "colorManager.h"

using namespace std;

struct Pixel{
	char ch;
	int pairFgBg;
};

class Window
{
public:
	Window();
	~Window();

	void display(void);
	void setWindow(WINDOW *_win);
	void write(int position, int character, int fgColor, int bgColor);
private:
	vector<Pixel> pixels;

	WINDOW *win;
	int maxX, maxY;

	ColorManager *cm;
};
#endif// WINDOW_H
