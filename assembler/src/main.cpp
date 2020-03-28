#include <fstream>
#include <iostream>
#include "defines.h"
#include "parser.h"
#include "assembler.h"


int main(int argc, char *argv[])
{
	// Input output files
	std::ifstream in;
	std::ofstream out;

	std::cout << BOLDWHITE << "BrenoCQ Assembler" << RESET << std::endl;
    if (argc < 2)
    {
		std::cout << BOLDRED << "[ERROR] " << RED << "No input file found" << RESET << std::endl; 
		std::cout << "\t" << "Please use one of the following:" << RESET << std::endl;
		std::cout << "\t" << argv[0] << " <in .basm file>" << std::endl;
		std::cout << "\t" << argv[0] << " <in .basm file> <out .bbin file>" << std::endl;
        exit(1);
    }

    return 0;
}
