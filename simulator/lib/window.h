#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Pixel{
	char ch;
	int textColor;
	int bgColor;
};

class Window
{
public:
	Window();
	~Window();

	void run(void);
private:
	vector<Pixel> pixels;
};
#endif// WINDOW_H
