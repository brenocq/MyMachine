#include "parser.h"

Parser::Parser()
{
	shared = new Shared();
}

Parser::~Parser()
{

}

int Parser::getCode(string line)
{
	removeComments(line);
	vector<string> words = splitLine(line);

	if(words.size()==0)
		return NO_CODE;

	if(isLabel(line))
		return LABEL_CODE;

	Command command = shared->getCommand(words[0]);

	if(command.code == NO_CODE)
		return ERROR_CODE;

	return command.code;
}

void Parser::getDefine(string line, string &name, int &value)
{
	vector<string> words = splitLine(line);
	name = words[1];

	string constant = words[2];	
	if(constant[0]=='\'')
	{
		value = int(constant[1]);
		return;
	}
	if(constant[0]=='\"')
	{
		value = -1;
		return;// TODO
	}
	
	value = stoi(constant);
}

void Parser::getRegisters(string line, int &rs1, int &rs2, int &rt)
{
	vector<string> words = splitLine(line);

	vector<pair<string, int> > registers;
	registers.push_back({T0_STR,T0_CODE});
	registers.push_back({T1_STR,T1_CODE});
	registers.push_back({T2_STR,T2_CODE});
	registers.push_back({T3_STR,T3_CODE});
	registers.push_back({T4_STR,T4_CODE});
	registers.push_back({T5_STR,T5_CODE});
	registers.push_back({T6_STR,T6_CODE});
	registers.push_back({T7_STR,T7_CODE});

	registers.push_back({A0_STR,A0_CODE});
	registers.push_back({A1_STR,A1_CODE});
	registers.push_back({A2_STR,A2_CODE});
	registers.push_back({A3_STR,A3_CODE});

	registers.push_back({V0_STR,V0_CODE});
	registers.push_back({V1_STR,V1_CODE});
	registers.push_back({V2_STR,V2_CODE});
	registers.push_back({V3_STR,V3_CODE});

	registers.push_back({S0_STR,S0_CODE});
	registers.push_back({S1_STR,S1_CODE});
	registers.push_back({S2_STR,S2_CODE});
	registers.push_back({S3_STR,S3_CODE});
	registers.push_back({S4_STR,S4_CODE});
	registers.push_back({S5_STR,S5_CODE});
	registers.push_back({S6_STR,S6_CODE});
	registers.push_back({S7_STR,S7_CODE});

	registers.push_back({ZERO_STR,ZERO_CODE});
	registers.push_back({RA_STR,RA_CODE});

	// First register
	if(words.size()>=2)
		for(auto reg : registers)
			if(words[1] == reg.first)
			{
				rt = reg.second;
			}

	// Second register
	if(words.size()>=3)
		for(auto reg : registers)
			if(words[2] == reg.first)
			{
				if(words.size()==3)
				{
					rs1 = reg.second;
					rs2 = reg.second;
				}
				if(words.size()==4)
					rs1 = reg.second;
			}

	// Third register
	if(words.size()==4)
		for(auto reg : registers)
			if(words[3] == reg.first)
					rs2 = reg.second;
}

void Parser::getRegisters(string line, int &rs, int &rt)
{
	vector<string> words = splitLine(line);

	vector<pair<string, int> > registers;
	registers.push_back({T0_STR,T0_CODE});
	registers.push_back({T1_STR,T1_CODE});
	registers.push_back({T2_STR,T2_CODE});
	registers.push_back({T3_STR,T3_CODE});
	registers.push_back({T4_STR,T4_CODE});
	registers.push_back({T5_STR,T5_CODE});
	registers.push_back({T6_STR,T6_CODE});
	registers.push_back({T7_STR,T7_CODE});

	registers.push_back({A0_STR,A0_CODE});
	registers.push_back({A1_STR,A1_CODE});
	registers.push_back({A2_STR,A2_CODE});
	registers.push_back({A3_STR,A3_CODE});

	registers.push_back({V0_STR,V0_CODE});
	registers.push_back({V1_STR,V1_CODE});
	registers.push_back({V2_STR,V2_CODE});
	registers.push_back({V3_STR,V3_CODE});

	registers.push_back({S0_STR,S0_CODE});
	registers.push_back({S1_STR,S1_CODE});
	registers.push_back({S2_STR,S2_CODE});
	registers.push_back({S3_STR,S3_CODE});
	registers.push_back({S4_STR,S4_CODE});
	registers.push_back({S5_STR,S5_CODE});
	registers.push_back({S6_STR,S6_CODE});
	registers.push_back({S7_STR,S7_CODE});

	registers.push_back({ZERO_STR,ZERO_CODE});
	registers.push_back({RA_STR,RA_CODE});

	// First register
	if(words.size()>=3)
		for(auto reg : registers)
			if(words[1] == reg.first)
			{
				rt = reg.second;
				if(words.size()==3)
					rs = reg.second;
			}

	// Second register
	if(words.size()==4)
		for(auto reg : registers)
			if(words[2] == reg.first)
			{
				rs = reg.second;
			}
}

void Parser::getConstant(string line, int &value, bool &isNumber)
{
	vector<string> words = splitLine(line);
	string lastWord = words.back();

	// Char
	if(lastWord[0]=='\'')
	{
		value = lastWord[1];	
		isNumber = true;
		return;
	}
	
	// String
	if(lastWord[0]=='\"')
	{
		value = 0;
		isNumber = false;
		return;
	}

	// Integer
	value = stoi(lastWord);
	isNumber = true;
}

vector<string> Parser::splitLine(string line)
{
	vector<string> words;
	size_t prev = 0, pos = 0;
	do
    {
        pos = line.find(" ", prev);

		// Check no more spaces
        if (pos == string::npos) 
			pos = line.length();

		// Create next word
        string word = line.substr(prev, pos-prev);
		// Remove \t \n \r spaces
		trimWord(word);

		// Add word to vector
        if (!word.empty()) 
			words.push_back(word);

        prev = pos + 1;
    }
    while (pos < line.length() && prev < line.length());

	return words;
}

void Parser::trimWord(string &word)
{
	string chars = "\t\n\r ";
	word.erase(0, word.find_first_not_of(chars));
	word.erase(word.find_last_not_of(chars) + 1);
}

void Parser::removeComments(string &line)
{
	 size_t commentPos = line.find(COMMENT_STR);

	 if(commentPos != string::npos && commentPos<line.length())
	 {
		line = line.substr(0, commentPos);
	 }
}

bool Parser::isLabel(string line)
{
	return line.back()==':';
}
