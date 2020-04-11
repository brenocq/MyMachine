#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Terminal
{
public:
	Terminal();
	~Terminal();

	void run(void);
private:
	vector<string> buffer;
};
#endif// TERMINAL_H
