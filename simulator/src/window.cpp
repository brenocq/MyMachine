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

void Window::writebool(int position, int character, int fgColor, int bgColor)
{
	string fgStr = getColor(fgColor);
	string bgStr = getColor(bgColor);

	int pairFgBg = cm->getPair(fgStr+"-"+bgStr);
	if(character==false)
		pixels[position] = {'F', pairFgBg};
	else
		pixels[position] = {'T', pairFgBg};

}

void Window::writechar(int position, int character, int fgColor, int bgColor)
{
	string fgStr = getColor(fgColor);
	string bgStr = getColor(bgColor);

	int pairFgBg = cm->getPair(fgStr+"-"+bgStr);
	pixels[position] = {char(character), pairFgBg};

}

void Window::writeint(int position, int character, int fgColor, int bgColor)
{
	string fgStr = getColor(fgColor);
	string bgStr = getColor(bgColor);
	string integer = to_string(character);
	int pairFgBg = cm->getPair(fgStr+"-"+bgStr);

	for(auto ch : integer)
		pixels[position++] = {ch, pairFgBg};
}

string Window::getColor(int color)
{
	switch(color)
	{
		case 'k':
			return "black";
		case 'r':
			return "red";
		case 'p':
			return "pink";
		case 'g':
			return "green";
		case 'G':
			return "dgreen";
		case 'y':
			return "yellow";
		case 'b':
			return "blue";
		case 'm':
			return "magenta";
		case 'c':
			return "cyan";
		case 'w':	
			return "white";
		default:
			return "black";
	}

}

void Window::read(int position, int &character, int &fgColor, int &bgColor)
{
	Pixel pixel;
	if(position<int(pixels.size()))
		pixel = pixels[position];

	character = pixel.ch;
	cm->getFgBg(pixel.pairFgBg, fgColor, bgColor);
}
