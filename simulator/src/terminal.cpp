#include "terminal.h"

Terminal::Terminal():
	win(NULL), maxX(0), maxY(0)
{
	cm = new ColorManager();
}

Terminal::~Terminal()
{
}

void Terminal::display(void)
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
		string title = "Terminal";
		wmove(win, 0, maxX/2-title.length()/2);
		wprintw(win, "%s", title.c_str());
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// Write terminal
	cleanTerminal();

	pairId = cm->getPair("white-black");
	wattr_on(win, COLOR_PAIR(pairId), NULL);
		for(int i=0;i<maxY-1;i++)
		{
			wmove(win, i+1, 0);
			if(int(buffer.size())>i)
				wprintw(win, "%s", buffer[i].c_str());
		}
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	wrefresh(win);
}

void Terminal::setWindow(WINDOW* _win)
{
	win = _win;
	getmaxyx(win, maxY, maxX);
}

void Terminal::printbool(bool constant)
{
	string boolean = "F";
	if(constant)
		boolean = "T";
	if(buffer.size()==0)
		buffer.push_back(boolean);
	else
		buffer.back()+=boolean;

	if(int(buffer.size())>maxY-1)
		buffer.pop_front();
}

void Terminal::printchar(char constant)
{
	if(buffer.size()==0)
		buffer.push_back(to_string(constant));
	else
		buffer.back()+=constant;

	if(int(buffer.size())>maxY-1)
		buffer.pop_front();
}


void Terminal::printint(int constant)
{
	if(buffer.size()==0)
		buffer.push_back(to_string(constant));
	else
		buffer.back()+=to_string(constant);

	if(int(buffer.size())>maxY-1)
		buffer.pop_front();
}

void Terminal::printnl()
{
	buffer.push_back("");

	if(int(buffer.size())>maxY-1)
		buffer.pop_front();
}

void Terminal::cleanTerminal()
{
	// Clean window
	for(int i=1;i<maxY;i++)
	{
		string blank = "";
		for(int j=0;j<maxX;j++)
			blank+=" ";

		wmove(win, i, 0);
		wprintw(win, blank.c_str());
	}
}
