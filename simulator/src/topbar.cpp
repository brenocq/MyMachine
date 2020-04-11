#include "topbar.h"

Topbar::Topbar():
	win(NULL), maxX(0), maxY(0)
{
	cm = new ColorManager();
}

Topbar::~Topbar()
{
}

void Topbar::display(void)
{
	if(win==NULL)
		return;

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

	// Registers

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
