#include "assembler.h"


Assembler::Assembler(string _inName, string _outName):
	lineCounter(0)
{
	inName = _inName;
	outName = _outName;

	parser = new Parser();	
	shared = new Shared();
}

Assembler::~Assembler()
{
	delete(parser);
	delete(shared);
}

void Assembler::run(void)
{
	cout << "\n\n" << BOLDWHITE << "----- Your code -----" << RESET << "\n\n";

	createLabels();
	createDefines();

	in.open(inName);
	out.open(outName);

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
	in.close();
	out.close();
}


void Assembler::createLabels()
{
	// TODO ignore inside .define
	in.open(inName);
	out.open(outName);

	string line;
	int lineNumber = 0;
	while(getline(in, line))
	{
		parser->removeComments(line);
		int code = parser->getCode(line);
		// Check commands
		Command command = shared->getCommand(code);

		string labelName = "";
		Label label = {"",-1};
		switch(code)
		{
			case NO_CODE:
				break;
			case LABEL_CODE:
				labelName = parser->getLabelName(line);
				if(labelName!="")
				{
					label = {labelName,lineNumber};
					shared->insertLabel(label);
				}
				break;
			default:
				if(command.instructionType!=' ')
				{
					lineNumber++;
				}
				break;
		}
	}
	in.close();
	out.close();
}

void Assembler::createDefines()
{
	// TODO ignore inside .code
	in.open(inName);
	out.open(outName);

	string line;
	int memoryNumber = 0;
	while(getline(in, line))
	{
		parser->removeComments(line);
		int code = parser->getCode(line);

		if(code==DEFINE_CODE)
		{
			int defineCode = parser->getDefineCode(line);
			string defineName = parser->getDefineName(line);
			switch(defineCode)
			{
				case BOOL_CODE:
					shared->insertDefine({defineName, memoryNumber});
					memoryNumber++;
					break;
				case CHAR_CODE:
					shared->insertDefine({defineName, memoryNumber});
					memoryNumber++;
					break;
				case INT_CODE:
					shared->insertDefine({defineName, memoryNumber});
					memoryNumber++;
					break;
				case STRING_CODE:
					shared->insertDefine({defineName, memoryNumber});
					string s;
					parser->getDefine(line, s);
					memoryNumber+=s.size()+1;
					break;
			}
		}
	}
	in.close();
	out.close();
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
		//parser->getDefine(line, name, value);
		//constants.push_back({name, value});

		//response = "D -> Added to constants";
	}

	return response;
}

string Assembler::writeRInstruction(Command command, string line)
{
	//OpCode rs1   rs2	 rt    sa    fun
	//000000 00000 00000 00000 00000 000000
	
	Register rs1;
	Register rs2;
	Register rt;
	parser->getRegisters(line, rs1, rs2, rt);

	// Write no file
	out << command.binary + rs1.binary + rs2.binary + rt.binary + "00000000000\n";
	lineCounter++;


	return ("R -> " + command.binary + " " + rs1.binary + " " + rs2.binary + " " + rt.binary + " 00000 000000");
}

string Assembler::writeCInstruction(Command command, string line)
{
	//OpCode rs    rt    constant 
	//000000 00000 00000 0000000000000000
	
	Register rs;
	Register rt;
	parser->getRegisters(line, rs, rt);

	int constant = 0;
	parser->getConstant(line, constant);

	// Write no file
	out << command.binary + rs.binary + rt.binary + toBinary(constant)+"\n";
	lineCounter++;

	return ("C -> " + command.binary + " " + rs.binary + " " + rt.binary + " " + toBinary(constant));
}

string Assembler::writeJInstruction(Command command, string line)
{
	lineCounter++;

	Label label {"", -1};
	Register rs1 = {"", NO_CODE, ""};
	Register rs2 = {"", NO_CODE, ""};
	parser->getJumpArguments(line, rs1, rs2, label);
	if(label.lineNumber!=-1)
	{
		out << command.binary + rs1.binary + rs2.binary + toBinary(label.lineNumber)+"\n";
		return "J -> " + command.binary + " " + rs1.binary + " " + rs2.binary + " " + toBinary(label.lineNumber);
	}
	else
	{
		out << command.binary + "00000000000000000000000000\n";
		return "J -> " + command.binary + " 00000000000000000000000000";
	}
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
