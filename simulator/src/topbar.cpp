#include "topbar.h"

Topbar::Topbar():
	win(NULL), maxX(0), maxY(0)
{
	shared = new Shared();
	cm = new ColorManager();
}

Topbar::~Topbar()
{
}

void Topbar::display(void)
{
	if(win==NULL)
		return;
	cleanTopBar();

	// TOP TITLE
	int pairId = cm->getPair("green-dgray");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		for(int i=0;i<maxX;i++)
		{
			wmove(win, 0, i);
			wprintw(win, " ");
		}
		string title = "BRENOCQ Simulator";
		wmove(win, 0, maxX/2-title.length()/2);
		wprintw(win, "%s", title.c_str());
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// ESC
	pairId = cm->getPair("white-dgray");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		string esq = "<ESQ> X";
		wmove(win, 0, maxX-esq.size()-1);
		wprintw(win, "%s", esq.c_str());
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// Mode
	if(*mode=="automatic")
	{
		pairId = cm->getPair("black-green");
		wattr_on(win, COLOR_PAIR(pairId), NULL);
			string modeStr = "<TAB> Auto";
			wmove(win, 0, 1);
			wprintw(win, "%s", modeStr.c_str());
		wattr_off(win, COLOR_PAIR(pairId), NULL);
	}
	else if(*mode=="manual")
	{
		pairId = cm->getPair("white-dgray");
		wattr_on(win, COLOR_PAIR(pairId), NULL);
			string modeStr= "<TAB> Manual";
			wmove(win, 0, 1);
			wprintw(win, "%s", modeStr.c_str());
		wattr_off(win, COLOR_PAIR(pairId), NULL);
	}

	// Registers
	int sizeTextReg = 12;
	int regPerLine = maxX/sizeTextReg;
	for(int i=0;i<QTY_REG;i++)
	{
		int posX = i%regPerLine*sizeTextReg;
		int posY = i/regPerLine+1;
		wmove(win, posY, posX);
		string regName = shared->getRegister(i).str;
		string regStr = regName+":"+to_string((*registers)[i]);

		if(regName.size()>2)
			pairId = cm->getPair("white-black");
		else
			switch(regName[0])
			{
				case 't'://t0
					pairId = cm->getPair("green-black");
					break;
				case 'a'://a0
					pairId = cm->getPair("red-black");
					break;
				case 'v'://v0
					pairId = cm->getPair("cyan-black");
					break;
				case 's'://s0
					pairId = cm->getPair("pink-black");
					break;
				case 'r'://ra
					pairId = cm->getPair("orange-black");
					break;
				case 'p'://pc
					pairId = cm->getPair("orange-black");
					break;
				default:
					pairId = cm->getPair("white-black");
			}
		
		wattr_on(win, COLOR_PAIR(pairId), NULL);
		wprintw(win, regStr.c_str());
		wattr_off(win, COLOR_PAIR(pairId), NULL);
	}

	wrefresh(win);
}

void Topbar::setWindow(WINDOW* _win)
{
	win = _win;
	getmaxyx(win, maxY, maxX);
}

void Topbar::setRegisters(vector<int> *_registers)
{
	registers = _registers;
}

void Topbar::setMode(string *_mode)
{
	mode = _mode;
}
void Topbar::cleanTopBar()
{
	// Clean window
	for(int i=0;i<maxY;i++)
	{
		string blank = "";
		for(int j=0;j<maxX;j++)
			blank+=" ";

		wmove(win, i, 0);
		wprintw(win, blank.c_str());
	}
}
