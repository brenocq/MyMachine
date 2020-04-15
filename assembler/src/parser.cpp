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

	if(isDefine(line))
		return DEFINE_CODE;

	if(isWrite(line))
		return WRITE_CODE;

	Command command = shared->getCommand(words[0]);

	if(command.code == NO_CODE)
		return ERROR_CODE;
	
	return command.code;
}

int Parser::getDefineCode(string line)
{
	removeComments(line);
	vector<string> words = splitLine(line);
	if(words.size()<2)
		return NO_CODE;

	if(words[1]==BOOL_STR)
		return BOOL_CODE;
	if(words[1]==CHAR_STR)
		return CHAR_CODE;
	if(words[1]==INT_STR)
		return INT_CODE;
	if(words[1]==STRING_STR)
		return STRING_CODE;
}

int Parser::getWriteCode(string line)
{
	removeComments(line);
	vector<string> words = splitLine(line);
	if(words.size()<1)
		return NO_CODE;
	
	if(words[0]==WRITEBOOL_STR)
		return WRITEBOOL_CODE;
	if(words[0]==WRITECHAR_STR)
		return WRITECHAR_CODE;
	if(words[0]==WRITEINT_STR)
		return WRITEINT_CODE;
	if(words[0]==WRITESTR_STR)
		return WRITESTR_CODE;

	return NO_CODE;
}

string Parser::getDefineName(string line)
{
	removeComments(line);
	vector<string> words = splitLine(line);
	if(words.size()==0)
		return "";

	return words[0];
}

string Parser::getLabelName(string line)
{
	removeComments(line);
	vector<string> words = splitLine(line);
	if(isLabel(line) && words.size()==1)
	{
		return words[0].substr(0,words[0].size()-1);
	}
	return "";
}
void Parser::getDefine(string line, string &str)
{
	int posInit = line.find("\"");


	for(int i=0;i<line.length();i++)
		if(line[i]=='"')
		{
			line[i]=' ';
			break;
		}
	int posEnd = line.find("\"");
	str = line.substr(posInit+1,posEnd-posInit-1);
}

void Parser::getDefine(string line, int &integer)
{
	vector<string> words = splitLine(line);
	integer = stoi(words[2]);
}

void Parser::getDefine(string line, char &character)
{
	vector<string> words = splitLine(line);

	if(words[2].size()==1)
	{
		character=' ';
		return;
	}
	character = words[2][1];
}

void Parser::getDefine(string line, bool &boolean)
{
	vector<string> words = splitLine(line);
	boolean = false;
	if(words[2]=="T")
		boolean = true;
}

void Parser::getRegisters(string line, Register &rs1, Register &rs2, Register &rt)
{
	vector<string> words = splitLine(line);
	rs1 = {"",NO_CODE,"00000"};
	rs2 = {"",NO_CODE,"00000"};
	rt = {"",NO_CODE,"00000"};

	// First register
	switch(words.size())
	{
		case 1:
			return;
		case 2:
			rt  = shared->getRegister(words[1]);
			rs1 = shared->getRegister(words[1]);
			rs2 = shared->getRegister(words[1]);
			return;

		case 3:
			rt  = shared->getRegister(words[1]);
			rs1 = shared->getRegister(words[2]);
			rs2 = shared->getRegister(words[2]);
			return;

		case 4:
			rt  = shared->getRegister(words[1]);
			rs1 = shared->getRegister(words[2]);
			rs2 = shared->getRegister(words[3]);
			return;
	}
}

void Parser::getRegisters(string line, Register &rs, Register &rt)
{
	vector<string> words = splitLine(line);

	rs = {"",NO_CODE, "00000"};
	rt = {"",NO_CODE, "00000"};

	if(words.size()==1)
		return;
	if(words.size()==2)
		return;
	if(words.size()==3)// loadc t0 1
	{
		rt = shared->getRegister(words[1]);
		rs = shared->getRegister(words[1]);
		return;
	}
	if(words.size()==4)// add t0 t1 9 || loadc t0 ' '
	{
		if(words[words.size()-1]=="\'" && words[words.size()-2]=="\'")
		{
			rt = shared->getRegister(words[1]);
			rs = shared->getRegister(words[1]);
			return;
		}
		rt = shared->getRegister(words[1]);
		rs = shared->getRegister(words[2]);
		return;
	}
	
	//return ERROR_CODE;
}

void Parser::getConstant(string line, int &value)
{
	vector<string> words = splitLine(line);
	string lastWord = words.back();

	// Char
	if(lastWord[0]=='\'')
	{
		if(lastWord=="\'")
			value = ' ';
		else
			value = lastWord[1];	

		return;
	}
	
	// Defined
	if(lastWord[0]<'0'||lastWord[0]>'9')
	{
		Define define = shared->getDefine(lastWord);
		if(define.value==-1)
			value = define.memoryPos;
		else
			value = define.value;
		return;
	}

	// Integer
	value = stoi(lastWord);
}

void Parser::getJumpArguments(string line, Register &rs1, Register &rs2, Label &label)
{
	vector<string> words = splitLine(line);

	rs1 = {"",NO_CODE,"00000"};
	rs2 = {"",NO_CODE,"00000"};
	Label rlabel = {"",-1};

	if(words.size()==1)
	{
		return;
	}
	else if(words.size()==2)
	{
		label = shared->getLabel(words[1]);
		return;
	}
	else if(words.size()==3)
	{
		label = shared->getLabel(words[2]);
		rs1 = shared->getRegister(words[1]);
		rs2 = shared->getRegister(words[1]);
	}
	else if(words.size()==4)
	{
		label = shared->getLabel(words[3]);
		rs1 = shared->getRegister(words[1]);
		rs2 = shared->getRegister(words[2]);
	}
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
	//cout<<endl<<words.size()<<" -> ";
	//for(auto word : words)
	//	cout<<word<<" ";
	//cout<<endl;

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
	size_t stringPos = line.find('"');
	string lineAux = line;

	// Remove comments inside strings
	if(commentPos != string::npos && stringPos != string::npos &&
		commentPos<line.length() && stringPos<line.length() &&
		stringPos<commentPos)
	{
		for(int i=0;i<lineAux.length();i++)
			if(lineAux[i]=='"')
			{
				lineAux[i]=' ';
				break;
			}
		stringPos = lineAux.find('"');
		string nextString = line.substr(stringPos+1,line.length()-(stringPos+1));
		commentPos = nextString.find(COMMENT_STR);
	 	if(commentPos != string::npos && commentPos<line.length())
			commentPos+=stringPos+1;
	}

	// Check comment found
	if(commentPos != string::npos && commentPos<line.length())
	{
	   line = line.substr(0, commentPos);
	}
}

bool Parser::isLabel(string line)
{
	return line.back()==':';
}

bool Parser::isDefine(string line)
{
	vector<string> words = splitLine(line);
	if(words.size()<2)
		return false;
	return words[1][0]=='.';
}

bool Parser::isWrite(string line)
{
	vector<string> words = splitLine(line);
	if(words.size()<1)
		return false;
	
	return words[0].substr(0,5)=="write";
}
