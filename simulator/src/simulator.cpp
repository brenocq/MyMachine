#include "simulator.h"

Simulator::Simulator(string inName):
	lineCounter(0), maxX(0), maxY(0)
{
	in.open(inName);

	// Create registers
	registers = new vector<int>(32);

	// Initialize screen
	initscr();
	raw();
	noecho();
	checkTerminalSupport();

	// Create objects
	window = new Window();	
	terminal = new Terminal();
	topbar = new Topbar();
	cm = new ColorManager(); 

	// Update maxX maxY
	getmaxyx(stdscr, maxY, maxX);

	// Create windows
	createWindows();
}

Simulator::~Simulator()
{
	endwin();

	delete(window);
	delete(terminal);
	delete(topbar);
	in.close();
}

void Simulator::run(void)
{
	topbar->display();


//	wmove(windowWin,1,0);
//
//
//	box(windowWin, 0, 0);
//	wrefresh(windowWin);
//
//	wborder(terminalWin, (int)'l', (int)'r', (int)'t', (int)'b', (int)'a', (int)'b', (int)'c', (int)'d');
//
//	init_pair(1, COLOR_CYAN, COLOR_WHITE);
//	wattron(terminalWin, COLOR_PAIR(1));
//	mvwprintw(terminalWin,5,5,"Hello World!");
//	wattroff(terminalWin, COLOR_PAIR(1));
//
//	int maxX, maxY;
//	wprintw(terminalWin, "%d %d", maxX, maxY);
//
//	


	getch();
}

void Simulator::checkTerminalSupport()
{

	if(!has_colors())
	{
		printw("Terminal does not support color");
		getch();
		exit(0);
	}
	if(!can_change_color())
	{
		printw("Terminal does not support change color");
		getch();
		exit(0);
	}
	start_color();
}

void Simulator::createWindows()
{
	// Create windows (numLines, numCols, startY, startX) 
	WINDOW *topbarWin  = newwin(3, maxX, 0, 0);
	//WINDOW *windowWin  = newwin(10,10,10,10);
	//WINDOW *terminalWin  = newwin(10,10,20,20);
	refresh();
	topbar->setWindow(topbarWin);
	topbar->setRegisters(registers);
}
