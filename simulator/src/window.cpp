#include "window.h"

Window::Window():
	win(NULL), maxX(0), maxY(0)
{
	cm = new ColorManager();
}

Window::~Window()
{

}

void Window::display(void)
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
		string title = "Window";
		wmove(win, 0, maxX/2-title.length()/2);
		wprintw(win, "%s", title.c_str());
	wattr_off(win, COLOR_PAIR(pairId), NULL);

	// Draw window
	for(int y=0;y<maxY-1;y++)
	{
		for(int x=0;x<maxX;x++)
		{
			int pairId = pixels[y*maxX+x].pairFgBg;
			wattr_on(win, COLOR_PAIR(pairId), NULL);
			wmove(win, y+1, x);
			wprintw(win, "%c", pixels[y*maxX+x].ch);
			wattr_off(win, COLOR_PAIR(pairId), NULL);
		}
	}

	wrefresh(win);
}

void Window::setWindow(WINDOW* _win)
{
	win = _win;
	getmaxyx(win, maxY, maxX);
	for(int i=0;i<maxX*(maxY-1);i++)
	{
		int pairId = cm->getPair("white-black");
		pixels.push_back({' ',pairId});
	}
}

void Window::write(int position, int character, int fgColor, int bgColor)
{
	string fgStr = "";
	string bgStr = "";

	switch(fgColor)
	{
		case 'k':
			fgStr="black";
			break;
		case 'r':
			fgStr="red";
			break;
		case 'p':
			fgStr="pink";
			break;
		case 'g':
			fgStr="green";
			break;
		case 'y':
			fgStr="yellow";
			break;
		case 'b':
			fgStr="blue";
			break;
		case 'm':
			fgStr="magenta";
			break;
		case 'c':
			fgStr="cyan";
			break;
		case 'w':	
			fgStr="white";
			break;
		default:
			fgStr="white";
	}
	switch(bgColor)
	{
		case 'k':
			bgStr="black";
			break;
		case 'r':
			bgStr="red";
			break;
		case 'p':
			bgStr="pink";
			break;
		case 'g':
			bgStr="green";
			break;
		case 'y':
			bgStr="yellow";
			break;
		case 'b':
			bgStr="blue";
			break;
		case 'm':
			bgStr="magenta";
			break;
		case 'c':
			bgStr="cyan";
			break;
		case 'w':	
			bgStr="white";
			break;
		default:
			fgStr="black";
	}

	int pairFgBg = cm->getPair(fgStr+"-"+bgStr);
	pixels[position] = {char(character), pairFgBg};
}
