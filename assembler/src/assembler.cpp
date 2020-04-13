#include "assembler.h"


Assembler::Assembler(string inName, string outName):
	lineCounter(0)
{
	in.open(inName);
	out.open(outName);

	parser = new Parser();	
	shared = new Shared();
}

Assembler::~Assembler()
{
	delete(parser);
	delete(shared);
	in.close();
	out.close();
}

void Assembler::run(void)
{
	cout << "\n\n" << BOLDWHITE << "----- Your code -----" << RESET << "\n\n";

	string line;
	while(getline(in, line))
	{
		parser->removeComments(line);
		int code = parser->getCode(line);
		checkError(code, line);
		checkLabel(code, line);

		// Check commands
		Command command = shared->getCommand(code);
		if(command.code != NO_CODE)
		{
			string response;
			switch(command.instructionType)
			{
				case ' ':
					cout << BOLDCYAN << line << RESET;
					break;
				case 'd':// Define
					cout << BOLDWHITE << lineCounter << " " << BLUE << line << RESET;
					response = writeDInstruction(command, line);
					break;
				case 'r':// Register
					cout << BOLDWHITE << lineCounter << " " << GREEN << line << RESET;
					response = writeRInstruction(command, line);
					break;
				case 'c':// Constant
					cout << BOLDWHITE << lineCounter << " " << YELLOW << line << RESET;
					response = writeCInstruction(command, line);
					break;
				case 'j':// Jump
					cout << BOLDWHITE << lineCounter << " " << MAGENTA << line << RESET;
					response = writeJInstruction(command, line);
					break;
				case 't':// Terminal
					cout << BOLDWHITE << lineCounter << " " << WHITE << line << RESET;
					response = writeTInstruction(command, line);
					break;
				case 'w':// Window
					cout << BOLDWHITE << lineCounter << " " << WHITE << line << RESET;
					response = writeWInstruction(command, line);
					break;
				default:
					break;
			}

			// Print binary
			int i=(50-line.length());
			while(i--)
				cout<<" ";

			cout<<response<<endl;
		}
	}
}

void Assembler::checkError(int code, string line)
{
	switch(code)
	{
		case ERROR_CODE:
			cout << BOLDRED << line << " <-- Something strange here"<< RESET << endl;	
			exit(0);
	}
}

void Assembler::checkLabel(int code, string line)
{
	if(code==LABEL_CODE)
	{
		cout << CYAN << line << RESET << endl;	
	}
}

string Assembler::writeDInstruction(Command command, string line)
{
	string response = "";
	if(command.code == BOOL_CODE || 
		command.code == CHAR_CODE || 
		command.code == INT_CODE)
	{
		string name = "";
		int value = 0;
		parser->getDefine(line, name, value);
		//constants.push_back({name, value});

		//response = "D -> Added to constants";
	}

	return response;
}

string Assembler::writeRInstruction(Command command, string line)
{
	//OpCode rs1   rs2	 rt    sa    fun
	//000000 00000 00000 00000 00000 000000
	
	int rs1_code = -1;
	int rs2_code = -1;
	int rt_code  = -1;
	parser->getRegisters(line, rs1_code, rs2_code, rt_code);

	Register rs1 = shared->getRegister(rs1_code);
	Register rs2 = shared->getRegister(rs2_code);
	Register rt  = shared->getRegister(rt_code);

	// Write no file
	out << command.binary + rs1.binary + rs2.binary + rt.binary + "00000000000\n";
	lineCounter++;


	return ("R -> " + command.binary + " " + rs1.binary + " " + rs2.binary + " " + rt.binary + " 00000 000000");
}

string Assembler::writeCInstruction(Command command, string line)
{
	//OpCode rs    rt    constant 
	//000000 00000 00000 0000000000000000
	
	int rs_code = -1;
	int rt_code  = -1;
	parser->getRegisters(line, rs_code, rt_code);

	Register rs = shared->getRegister(rs_code);
	Register rt  = shared->getRegister(rt_code);
	int constant = 0;
	bool isNumber = false;
	parser->getConstant(line, constant, isNumber);

	if(isNumber)
	{
		// Write no file
		out << command.binary + rs.binary + rt.binary + toBinary(constant)+"\n";
		lineCounter++;

		return ("C -> " + command.binary + " " + rs.binary + " " + rt.binary + " " + toBinary(constant));
	}
	return "TODO: Constant as string";
}

string Assembler::writeJInstruction(Command command, string line)
{
	return "";
}

string Assembler::writeTInstruction(Command command, string line)
{
	out << command.binary + "00000000000000000000000000\n";
	lineCounter++;
	return "T -> " + command.binary + " 00000000000000000000000000";
}

string Assembler::writeWInstruction(Command command, string line)
{
	out << command.binary + "00000000000000000000000000\n";
	lineCounter++;
	return "W -> " + command.binary + " 00000000000000000000000000";
}

string Assembler::toBinary(int value)
{
	std::string r;
	int numBits = 16;

	// Overflow
	if(value >= (1<<numBits))
		return "0000000000000000";

	int n = value;
	while(n!=0) 
	{
		r=(n%2==0 ?"0":"1")+r; 
		n/=2;
	}

	int i = 16-r.length();
    while(i--)
		r = "0"+r;
	
    return r;
}
