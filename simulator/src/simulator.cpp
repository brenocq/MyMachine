#include "simulator.h"

Simulator::Simulator(string inName):
	maxX(0), maxY(0)
{
	registers = vector<int>(32);

	// Initialize screen
	initscr();
	raw();
	noecho();
	checkTerminalSupport();

	// Create objects
	window = new Window();	
	terminal = new Terminal();
	topbar = new Topbar();
	code = new Code();
	cm = new ColorManager(); 
	shared = new Shared(); 

	// Update maxX maxY
	getmaxyx(stdscr, maxY, maxX);

	// Create windows
	createWindows();

	// Process input file
	in.open(inName);
	processInputFile();
	in.close();
}

Simulator::~Simulator()
{
	endwin();

	delete(window);
	delete(terminal);
	delete(topbar);
	delete(code);
}

void Simulator::run(void)
{
	// TODO finish command
	while(registers[PC_CODE]<int(lines.size()))
	{
		topbar->display();
		window->display();
		code->display();
		terminal->display();
		getch();
		runCommand();
	}
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
	//TODO 10 is hardcoded (register string size)
	int barHeight = QTY_REG*10/maxX+2;
	int winHeight = 40;
	int winWidth = 150;
	int termHeight = maxY-barHeight-winHeight;

	WINDOW *topbarWin  = newwin(barHeight, maxX, 0, 0);
	WINDOW *windowWin  = newwin(winHeight,winWidth,barHeight+1,0);
	WINDOW *terminalWin  = newwin(termHeight, maxX, maxY-termHeight, 0);
	WINDOW *codeWin  = newwin(winHeight, maxX-winWidth, barHeight+1, winWidth);

	refresh();
	topbar->setWindow(topbarWin);
	topbar->setRegisters(&registers);

	window->setWindow(windowWin);
	terminal->setWindow(terminalWin);
	code->setWindow(codeWin);
	code->setRegisters(&registers);
	code->setLines(&lines);
}

void Simulator::processInputFile()
{
	string line = "";
	while (!in.eof())
    {
      	getline(in,line);
		lines.push_back(line);
    }
}

void Simulator::runCommand()
{
	int *pc = &registers[PC_CODE];
	
	string lineBin = lines[*pc];
	string opCode = lineBin.substr(0, 6);
	Command command = shared->getCommandByOpCode(opCode);

	if(command.code != NO_CODE)
	{
		switch(command.instructionType)
		{
			case ' ':
				break;
			case 'd':// Define
				DInstruction(command, lineBin);
				break;
			case 'r':// Register
				RInstruction(command, lineBin);
				break;
			case 'c':// Constant
				CInstruction(command, lineBin);
				break;
			case 'j':// Jump
				JInstruction(command, lineBin);
				break;
			case 't':// Terminal
				TInstruction(command, lineBin);
				break;
			case 'w':// Window
				WInstruction(command, lineBin);
				break;
			default:
				break;
		}
	}
	(*pc)++;
}

void Simulator::DInstruction(Command command, string line)
{

}

void Simulator::RInstruction(Command command, string line)
{
	Register rs1, rs2, rt;
	shared->getRegistersByBin(line, rs1, rs2, rt);
	//move(0,0);
	//printw(to_string(rs1.code).c_str());
	//printw((rs1.binary).c_str());
	switch(command.code)
	{
		case LOAD_CODE:
		case MOVE_CODE:
			registers[rt.code] = registers[rs1.code];
			break;
		case STORE_CODE://!!
			break;
		case ADD_CODE:
			registers[rt.code] = registers[rs1.code] + registers[rs2.code];
			break;
		case SUB_CODE:
			registers[rt.code] = registers[rs1.code] - registers[rs2.code];
			break;
		case MUL_CODE:
			registers[rt.code] = registers[rs1.code] * registers[rs2.code];
			break;
		case DIV_CODE:
			registers[rt.code] = registers[rs1.code] / registers[rs2.code];
			break;
		case AND_CODE:
			registers[rt.code] = registers[rs1.code] && registers[rs2.code];
			break;
		case OR_CODE:
			registers[rt.code] = registers[rs1.code] || registers[rs2.code];
			break;
		case XOR_CODE:
			registers[rt.code] = registers[rs1.code] != registers[rs2.code];
			break;
		case NOT_CODE:
			registers[rt.code] = registers[rs1.code];
			break;
		case SHIFT_LEFT_CODE:
			break;
		case SHIFT_RIGHT_CODE:
			break;
		case PUSH_CODE:
			break;
		case POP_CODE:
			break;
	}
}

void Simulator::CInstruction(Command command, string line)
{
	Register rs, rt;
	int constant;
	bool isNumber;
	shared->getConstantByBin(line, rs, rt, constant, isNumber);

	switch(command.code)
	{
		case LOADC_CODE:
			registers[rt.code] = constant; 
			break;
		case ADDC_CODE:
			registers[rt.code] = registers[rs.code]+constant;
			break;
		case SUBC_CODE:
			registers[rt.code] = registers[rs.code]-constant;
			break;
		case MULC_CODE:
			registers[rt.code] = registers[rs.code]*constant;
			break;
		case DIVC_CODE:
			registers[rt.code] = registers[rs.code]/constant;
			break;
	}
}

void Simulator::JInstruction(Command command, string line)
{

}

void Simulator::TInstruction(Command command, string line)
{
	int constant = 0;
	switch(command.code)
	{
		case PRINTINT_CODE:
			constant = registers[A0_CODE];
			terminal->printint(constant);
			break;
		case PRINTNL_CODE:
			terminal->printnl();
			break;
	}
}

void Simulator::WInstruction(Command command, string line)
{
	switch(command.code)
	{
		case WRITE_CODE:
			int ch, pos, fg, bg;
			pos = registers[A0_CODE];
			ch = registers[A1_CODE];
			fg = registers[A2_CODE];
			bg = registers[A3_CODE];
			window->write(pos, ch, fg, bg);
			break;
		case READ_CODE:
			break;
		case INPUT_CODE:
			break;
	}
}
