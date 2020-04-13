#include "code.h"

Code::Code():
	win(NULL), maxX(0), maxY(0), lines(NULL)
{
	cm = new ColorManager();
	shared = new Shared();
}

Code::~Code()
{
}

void Code::display(void)
{
	if(win==NULL)
		return;

	// TOP BAR
	int pairId = cm->getPair("white-dgray");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		for(int i=0;i<maxX;i++)
		{
			wmove(win, 0, i);
			wprintw(win, " ");
		}
		string title = "Code";
		wmove(win, 0, maxX/2-title.length()/2);
		wprintw(win, "%s", title.c_str());
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// Side divisor
	pairId = cm->getPair("lgray-black");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		for(int i=1;i<maxY;i++)
		{
			wmove(win, i, 0);
			wprintw(win, "|");
		}
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// Clean window
	for(int i=1;i<maxY;i++)
	{
		string blank = "";
		for(int j=1;j<maxX-1;j++)
			blank+=" ";

		wmove(win, i, 1);
		wprintw(win, blank.c_str());
	}

	// Print code
	pairId = cm->getPair("lgray-black");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		int currLine = (*registers)[PC_CODE];
		for(int i=1;i<maxY;i++,currLine++)
		{
			if(currLine<int((*lines).size()-1))
			{
				string lineBin = (*lines)[currLine];
				string opCode = lineBin.substr(0, 6);
				Command command = shared->getCommandByOpCode(opCode);
				string arg1, arg2, arg3;
				getLineArgs(command, lineBin, arg1, arg2, arg3);
				wmove(win, i, 1);
				wprintw(win, (to_string(currLine)).c_str());
				wmove(win, i, 5);

				string fullCommand = command.str+" "+arg1+" "+arg2+" "+arg3;
				wprintw(win, fullCommand.c_str());
			}
		}
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	wrefresh(win);
}

void Code::setWindow(WINDOW* _win)
{
	win = _win;
	getmaxyx(win, maxY, maxX);
}

void Code::setRegisters(vector<int> *_registers)
{
	registers = _registers;
}

void Code::setLines(vector<string> *_lines)
{
	lines = _lines;
}

void Code::getLineArgs(Command command, string lineBin, string &arg1, string &arg2, string &arg3)
{
	arg1 = "";
	arg2 = "";
	arg3 = "";

	Register rs, rs1, rs2, rt;
	if(command.code != NO_CODE)
	{
		switch(command.instructionType)
		{
			case 'd':// Define
				break;
			case 'r':// Register
				shared->getRegistersByBin(lineBin, rs1, rs2, rt);
				arg1 = rt.str;
				arg2 = rs1.str;
				arg3 = rs2.str;
				break;
			case 'c':// Constant
				int constant;
				bool isNumber;
				shared->getConstantByBin(lineBin, rs, rt, constant, isNumber);
				arg1 = rt.str;
				arg2 = rs.str;
				arg3 = to_string(constant);
				break;
			case 'j':// Jump
				break;

			case ' ':
			case 't':// Terminal
			case 'w':// Window
			default:
				break;
		}
	}
}
