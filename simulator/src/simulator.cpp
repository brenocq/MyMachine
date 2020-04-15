#include "simulator.h"

Simulator::Simulator(string inName):
	maxX(0), maxY(0)
{
	registers = vector<int>(32);
	mode = "automatic";
	close = false;
	finished = false;
	startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	// Init rand
	srand(time(0));

	// Initialize screen
	initscr();
	//raw();
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
	initMemory();
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

		// Update input
		timeout(0);
		int value = getch();
		if(value!=ERR)
		{
			if(value==27)// ESQ
				close = true;
			if(value==9)// TAB
			{
				mode = mode=="manual"?"automatic":"manual";
				topbar->display();
			}
			registers[INPUT_REG_CODE]=value;
		}
		// Next command

		if(mode=="manual" || finished == true)
		{
			timeout(-1);
			int value = getch();
			if(value==27)// ESQ
				close = true;
			if(value==9)// TAB
			{
				mode = mode=="manual"?"automatic":"manual";
				topbar->display();
			}
			registers[INPUT_REG_CODE]=value;
		}
		
		// Update random
		registers[RAND_CODE]=rand()%65535;

		// Update time (1=100ms)
		unsigned long currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		registers[TIME_CODE]=int(currTime-startTime)/150;
		if(registers[TIME_CODE]>65535)
			registers[TIME_CODE]=0;

		// Check close
		if(close)
			break;
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
	int barHeight = QTY_REG*12/maxX+2;
	int winHeight = 40;
	int winWidth = 150;
	int termHeight = maxY-barHeight-winHeight;

	WINDOW *topbarWin  = newwin(barHeight, maxX, 0, 0);
	WINDOW *windowWin  = newwin(winHeight,winWidth,barHeight+1,0);
	WINDOW *terminalWin  = newwin(termHeight, maxX, maxY-termHeight+1, 0);
	WINDOW *codeWin  = newwin(winHeight, maxX-winWidth, barHeight+1, winWidth);

	refresh();
	topbar->setWindow(topbarWin);
	topbar->setRegisters(&registers);
	topbar->setMode(&mode);

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

void Simulator::initMemory()
{
	for(auto lineBin : lines)
	{
		string opCode = lineBin.substr(0, 6);
		Command command = shared->getCommandByOpCode(opCode);
		if(command.code == PUSHD_CODE)
		{
			string number = lineBin.substr(16, 16);
			memoryDef.push_back(stoi(number, nullptr, 2));
		}
	}
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
		case MOD_CODE:
			registers[rt.code] = registers[rs1.code] % registers[rs2.code];
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
			registers[rt.code] = registers[rs1.code]*2;
			break;
		case SHIFT_RIGHT_CODE:
			registers[rt.code] = registers[rs1.code]/2;
			break;
		case PUSH_CODE:
			memory.push(registers[rs1.code]);
			break;
		case POP_CODE:
			if(memory.size()>0)
			{
				registers[rt.code] = memory.top();
				memory.pop();
			}
			break;
	}
}

void Simulator::CInstruction(Command command, string line)
{
	Register rs, rt;
	int constant;
	bool isNumber;
	shared->getConstantByBin(line, rs, rt, constant, isNumber);

	int factor;
	switch(command.code)
	{
		case LOADC_CODE:
			if(isNumber)
				registers[rt.code] = constant; 
			break;
		case ADDC_CODE:
			if(isNumber)
				registers[rt.code] = registers[rs.code]+constant;
			break;
		case SUBC_CODE:
			if(isNumber)
				registers[rt.code] = registers[rs.code]-constant;
			break;
		case MULC_CODE:
			if(isNumber)
				registers[rt.code] = registers[rs.code]*constant;
			break;
		case DIVC_CODE:
			if(isNumber)
				registers[rt.code] = registers[rs.code]/constant;
			break;
		case MODC_CODE:
			if(isNumber)
				registers[rt.code] = registers[rs.code]%constant;
			break;
		case SHIFT_LEFTC_CODE:
			if(isNumber)
			{
				factor=1;
				while(constant--)factor*=2;
				registers[rt.code] = registers[rs.code]*factor;
			}
			break;
		case SHIFT_RIGHTC_CODE:
			if(isNumber)
			{
				factor=1;
				while(constant--)factor*=2;
				registers[rt.code] = registers[rs.code]/factor;
			}
			break;
	}
}

void Simulator::JInstruction(Command command, string line)
{
	Register rs1, rs2;
	int jumpLine;
	shared->getJumpByBin(line, rs1, rs2, jumpLine);

	switch(command.code)
	{
		case J_CODE:
			registers[PC_CODE] = jumpLine-1;
			break;
		case JEQ_CODE:
			if(registers[rs1.code]==registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JNE_CODE:
			if(registers[rs1.code]!=registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JEZ_CODE:
			if(registers[rs1.code]==0)
				registers[PC_CODE] = jumpLine-1;
			break;
		case JNZ_CODE:
			if(registers[rs1.code]!=0)
				registers[PC_CODE] = jumpLine-1;
			break;
		case JGT_CODE:
			if(registers[rs1.code]>registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JGE_CODE:
			if(registers[rs1.code]>=registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JLT_CODE:
			if(registers[rs1.code]<registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JLE_CODE:
			if(registers[rs1.code]<=registers[rs2.code])
				registers[PC_CODE] = jumpLine-1;
			break;
		case JL_CODE:
			registers[RA_CODE] = registers[PC_CODE]+1;
			registers[PC_CODE] = jumpLine-1;
			break;
		case JEQL_CODE:
			if(registers[rs1.code]==registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JNEL_CODE:
			if(registers[rs1.code]!=registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JEZL_CODE:
			if(registers[rs1.code]==0)
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JNZL_CODE:
			if(registers[rs1.code]!=0)
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JGTL_CODE:
			if(registers[rs1.code]>registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JGEL_CODE:
			if(registers[rs1.code]>=registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JLTL_CODE:
			if(registers[rs1.code]<registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JLEL_CODE:
			if(registers[rs1.code]<=registers[rs2.code])
			{
				registers[RA_CODE] = registers[PC_CODE]+1;
				registers[PC_CODE] = jumpLine-1;
			}
			break;
		case JR_CODE:
			registers[PC_CODE] = registers[RA_CODE]-1;
			break;
		case FINISH_CODE:
			finished = true;
			registers[PC_CODE]--;
			break;
	}
}

void Simulator::TInstruction(Command command, string line)
{
	int constant = 0, mempos=0;
	char ch;
	switch(command.code)
	{
		case PRINTBOOL_CODE:
			constant = registers[A0_CODE];
			terminal->printbool((bool)constant);
			break;
		case PRINTCHAR_CODE:
			constant = registers[A0_CODE];
			terminal->printchar((char)constant);
			break;
		case PRINTINT_CODE:
			constant = registers[A0_CODE];
			terminal->printint(constant);
			break;
		case PRINTSTR_CODE:
			mempos = registers[A0_CODE];
			if(int(memoryDef.size())<=mempos+1)
				break;

			ch = memoryDef[mempos++];
			while(ch!='\0')
			{
				terminal->printchar(ch);

				if(int(memoryDef.size())<=mempos+1)
					break;
				ch = memoryDef[mempos++];
			}
			break;
		case PRINTNL_CODE:
			terminal->printnl();
			break;
	}
}

void Simulator::WInstruction(Command command, string line)
{
	int pos, ch, fg, bg, input;
	int mempos, writeCode;
	switch(command.code)
	{
		case WRITE_CODE:
			writeCode = stoi(line.substr(30,2), nullptr, 2);
			switch(writeCode)
			{
				case 0://bool
					pos = registers[A0_CODE];
					ch = registers[A1_CODE];
					fg = registers[A2_CODE];
					bg = registers[A3_CODE];
					window->writebool(pos, ch, fg, bg);
					break;
				case 1://char
					pos = registers[A0_CODE];
					ch = registers[A1_CODE];
					fg = registers[A2_CODE];
					bg = registers[A3_CODE];
					window->writechar(pos, ch, fg, bg);
					break;
				case 2://int
					pos = registers[A0_CODE];
					ch = registers[A1_CODE];
					fg = registers[A2_CODE];
					bg = registers[A3_CODE];
					window->writeint(pos, ch, fg, bg);
					break;
				case 3://str
					pos = registers[A0_CODE];
					mempos = registers[A1_CODE];
					fg = registers[A2_CODE];
					bg = registers[A3_CODE];
					if(int(memoryDef.size())<=mempos+1)
						break;

					ch = memoryDef[mempos++];
					while(ch!='\0')
					{
						window->writechar(pos++, ch, fg, bg);

						if(int(memoryDef.size())<=mempos+1)
							break;
						ch = memoryDef[mempos++];
					}
					break;
			}
			break;
		case READ_CODE:
			pos = registers[A0_CODE];
			window->read(pos, ch, fg, bg);
			registers[V0_CODE] = ch;
			registers[V1_CODE] = fg;
			registers[V2_CODE] = bg;
			break;
		case INPUT_CODE:
			timeout(-1);
			input = getch();
			if(input==27)// ESQ
				close = true;
			if(input==9)// TAB
			{
				mode = mode=="manual"?"automatic":"manual";
				topbar->display();
			}

			registers[V0_CODE] = input;
			break;
	}
}
