#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>

class Assembler()
{
public:
	Assembler(string inFile, string outFile);
	~Assembler();

	void run(void);
private:
	Parser *parser;
};
#endif// ASSEMBLER_H
