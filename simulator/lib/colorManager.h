#ifndef COLORMANAGER_H
#define COLORMANAGER_H
#define MAX_PAIRS 16

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <curses.h>

using namespace std;

class ColorManager
{
public:
	ColorManager();
	~ColorManager();

	static void init(void);
	static void putColor(string name, int r, int g, int b);
	static int getColor(string name);
	static int getPair(string name);
	static void updatePairs(void);

private:
	static vector<string> color;
};
#endif// WINDOW_H
