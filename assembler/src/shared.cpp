#include "shared.h"

vector<Command> Shared::commands;	
vector<Register> Shared::registers;	
vector<Label> Shared::labels;	
vector<Constant> Shared::constants;	
vector<Define> Shared::defines;	

Shared::Shared()
{
	initCommands();
	initRegisters();
}

Shared::~Shared()
{
}

void Shared::initRegisters(void)
{
	if(registers.size()>0)
		return;

	registers.push_back({T0_STR,T0_CODE,T0});
	registers.push_back({T1_STR,T1_CODE,T1});
	registers.push_back({T2_STR,T2_CODE,T2});
	registers.push_back({T3_STR,T3_CODE,T3});
	registers.push_back({T4_STR,T4_CODE,T4});
	registers.push_back({T5_STR,T5_CODE,T5});
	registers.push_back({T6_STR,T6_CODE,T6});
	registers.push_back({T7_STR,T7_CODE,T7});

	registers.push_back({A0_STR,A0_CODE,A0});
	registers.push_back({A1_STR,A1_CODE,A1});
	registers.push_back({A2_STR,A2_CODE,A2});
	registers.push_back({A3_STR,A3_CODE,A3});

	registers.push_back({V0_STR,V0_CODE,V0});
	registers.push_back({V1_STR,V1_CODE,V1});
	registers.push_back({V2_STR,V2_CODE,V2});
	registers.push_back({V3_STR,V3_CODE,V3});

	registers.push_back({S0_STR,S0_CODE,S0});
	registers.push_back({S1_STR,S1_CODE,S1});
	registers.push_back({S2_STR,S2_CODE,S2});
	registers.push_back({S3_STR,S3_CODE,S3});
	registers.push_back({S4_STR,S4_CODE,S4});
	registers.push_back({S5_STR,S5_CODE,S5});
	registers.push_back({S6_STR,S6_CODE,S6});
	registers.push_back({S7_STR,S7_CODE,S7});

	registers.push_back({PC_STR,PC_CODE,PC});
	registers.push_back({RA_STR,RA_CODE,RA});
	registers.push_back({ZERO_STR,ZERO_CODE,ZERO});
	registers.push_back({TIME_STR,TIME_CODE,TIME});
	registers.push_back({RAND_STR,RAND_CODE,RAND});
}

void Shared::initCommands(void)
{
	if(commands.size()>0)
		return;

	commands.push_back({DEFINE_STR, 	DEFINE_CODE,	"", ' '});
	commands.push_back({CODE_STR, 		CODE_CODE,		"", ' '});
	commands.push_back({BOOL_STR, 		BOOL_CODE, 		"", 'd'});
	commands.push_back({CHAR_STR, 		CHAR_CODE, 		"", 'd'});
	commands.push_back({INT_STR, 		INT_CODE, 		"", 'd'});
	commands.push_back({STRING_STR, 	STRING_CODE, 	"", 'd'});

	commands.push_back({LOAD_STR, 		LOAD_CODE,		LOAD,	'r'});
	commands.push_back({LOADC_STR, 		LOADC_CODE,		LOADC,	'c'});
	commands.push_back({STORE_STR, 		STORE_CODE,		STORE,	'r'});
	commands.push_back({STOREC_STR,		STOREC_CODE,	STOREC,	'c'});

	commands.push_back({MOVE_STR, 		MOVE_CODE,		MOVE,	'r'});

	commands.push_back({ADD_STR, 		ADD_CODE,		ADD,	'r'});
	commands.push_back({ADDC_STR,		ADDC_CODE,		ADDC,	'c'});
	commands.push_back({SUB_STR, 		SUB_CODE,		SUB,	'r'});
	commands.push_back({SUBC_STR,		SUBC_CODE,		SUBC,	'c'});
	commands.push_back({MUL_STR, 		MUL_CODE,		MUL,	'r'});
	commands.push_back({MULC_STR,		MULC_CODE,		MULC,	'c'});
	commands.push_back({DIV_STR, 		DIV_CODE,		DIV,	'r'});
	commands.push_back({DIVC_STR,		DIVC_CODE,		DIVC,	'c'});
	commands.push_back({MOD_STR, 		MOD_CODE,		MOD,	'r'});
	commands.push_back({MODC_STR,		MODC_CODE,		MODC,	'c'});

	commands.push_back({AND_STR,		AND_CODE,		AND,	'r'});
	commands.push_back({OR_STR, 		OR_CODE,		OR,		'r'});
	commands.push_back({XOR_STR,		XOR_CODE,		XOR,	'r'});
	commands.push_back({NOT_STR,		NOT_CODE,		NOT,	'r'});

	commands.push_back({SHIFT_LEFT_STR, SHIFT_LEFT_CODE,	SHIFTL, 'r'});
	commands.push_back({SHIFT_LEFTC_STR, SHIFT_LEFTC_CODE,	SHIFTLC,'c'});
	commands.push_back({SHIFT_RIGHT_STR,SHIFT_RIGHT_CODE,	SHIFTR,	'r'});
	commands.push_back({SHIFT_RIGHTC_STR,SHIFT_RIGHTC_CODE,	SHIFTRC,'c'});

	commands.push_back({J_STR,   		J_CODE,			J,		'j'});
	commands.push_back({JEQ_STR, 		JEQ_CODE,		JEQ,	'j'});
	commands.push_back({JNE_STR, 		JNE_CODE,		JNE,	'j'});
	commands.push_back({JEZ_STR, 		JEZ_CODE,		JEZ,	'j'});
	commands.push_back({JNZ_STR, 		JNZ_CODE,		JNZ,	'j'});
	commands.push_back({JGT_STR, 		JGT_CODE,		JGT,	'j'});
	commands.push_back({JGE_STR, 		JGE_CODE,		JGE,	'j'});
	commands.push_back({JLT_STR, 		JLT_CODE,		JLT,	'j'});
    commands.push_back({JLE_STR, 		JLE_CODE,		JLE,	'j'});

	commands.push_back({JL_STR,   		JL_CODE,		JL,		'j'});
	commands.push_back({JEQL_STR, 		JEQL_CODE,		JEQL,	'j'});
	commands.push_back({JNEL_STR, 		JNEL_CODE,		JNEL,	'j'});
	commands.push_back({JEZL_STR, 		JEZL_CODE,		JEZL,	'j'});
	commands.push_back({JNZL_STR, 		JNZL_CODE,		JNZL,	'j'});
	commands.push_back({JGTL_STR, 		JGTL_CODE,		JGTL,	'j'});
	commands.push_back({JGEL_STR, 		JGEL_CODE,		JGEL,	'j'});
	commands.push_back({JLTL_STR, 		JLTL_CODE,		JLTL,	'j'});
    commands.push_back({JLEL_STR, 		JLEL_CODE,		JLEL,	'j'});

	commands.push_back({PUSH_STR, 		PUSH_CODE,		PUSH,	'r'});
	commands.push_back({POP_STR, 		POP_CODE,		POP,	'r'});

	commands.push_back({PRINTBOOL_STR, 	PRINTBOOL_CODE,	PRINTBOOL,	't'});
	commands.push_back({PRINTCHAR_STR, 	PRINTCHAR_CODE,	PRINTCHAR,	't'});
    commands.push_back({PRINTINT_STR, 	PRINTINT_CODE,	PRINTINT,	't'});
	commands.push_back({PRINTSTR_STR, 	PRINTSTR_CODE,	PRINTSTR,	't'});
    commands.push_back({PRINTNL_STR, 	PRINTNL_CODE,	PRINTNL,	't'});

    commands.push_back({WRITE_STR, 		WRITE_CODE,		WRITE,		'w'});
	commands.push_back({READ_STR, 		READ_CODE,		READ,		'w'});
    commands.push_back({INPUT_STR, 		INPUT_CODE,		INPUT,		'w'});

	commands.push_back({FINISH_STR,		FINISH_CODE,	FINISH,		'j'});
    commands.push_back({BREAKP_STR, 	BREAKP_CODE,	BREAKP,		'j'});
}

Command Shared::getCommand(int code)
{
	for(auto command : commands)
	{
		if(command.code == code)
			return command;
	}
	return {"", NO_CODE, "", ' '};
}

Command Shared::getCommand(string str)
{
	for(auto command : commands)
	{
		if(command.str == str)
			return command;
	}
	return {"", NO_CODE, "", ' '};
}

Command Shared::getCommandByOpCode(string opCode)
{
	for(auto command : commands)
	{
		if(command.binary == opCode)
			return command;
	}
	return {"", NO_CODE, "", ' '};
}


Register Shared::getRegister(int code)
{
	for(auto reg : registers)
	{
		if(reg.code == code)
			return reg;
	}
	return {"", NO_CODE, ""};
}

Register Shared::getRegister(string str)
{
	for(auto reg : registers)
	{
		if(reg.str == str)
			return reg;
	}
	return {"", NO_CODE, ""};
}

Label Shared::getLabel(string name)
{
	for(auto label : labels)
	{
		if(label.name == name)
			return label;
	}

	return {"", -1};
}

Constant Shared::getConstant(string name)
{
	for(auto constant : constants)
	{
		if(constant.name == name)
			return constant;
	}
	return {"", -1};
}

void Shared::insertLabel(Label label)
{
	cout<<"insertLabel -> "<<label.name<<endl;
	labels.push_back(label);
}

void Shared::getRegistersByBin(string lineBin, Register &rs1, Register &rs2, Register &rt)
{
	string rs1Bin = lineBin.substr(6,5);
	string rs2Bin = lineBin.substr(11,5);
	string rtBin = lineBin.substr(16,5);

	rs1 = {"", NO_CODE, ""};
	rs2 = {"", NO_CODE, ""};
	rt = {"", NO_CODE, ""};
	for(auto reg : registers)
	{
		if(rs1Bin == reg.binary)
			rs1 = reg;
		if(rs2Bin == reg.binary)
			rs2 = reg;
		if(rtBin == reg.binary)
			rt = reg;
	}
}

void Shared::getConstantByBin(string lineBin, Register &rs, Register &rt, int &constant, bool &isNumber)
{
	string rsBin = lineBin.substr(6,5);
	string rtBin = lineBin.substr(11,5);
	string constantBin = lineBin.substr(16,16);

	rs = {"", NO_CODE, ""};
	rt = {"", NO_CODE, ""};

	for(auto reg : registers)
	{
		if(rsBin == reg.binary)
			rs = reg;
		if(rtBin == reg.binary)
			rt = reg;
	}

	constant = stoi(constantBin, nullptr, 2);
	isNumber = true;
}

void Shared::getJumpByBin(string lineBin, Register &rs1, Register &rs2, int &jumpLine)
{
	string rs1Bin = lineBin.substr(6,5);
	string rs2Bin = lineBin.substr(11,5);
	string jumpBin = lineBin.substr(16,16);

	rs1 = {"", NO_CODE, ""};
	rs2 = {"", NO_CODE, ""};

	for(auto reg : registers)
	{
		if(rs1Bin == reg.binary)
			rs1 = reg;
		if(rs2Bin == reg.binary)
			rs2 = reg;
	}

	jumpLine = stoi(jumpBin, nullptr, 2);
}

void Shared::insertDefine(Define define)
{
	cout<<"insertDefine -> "<<define.name<<endl;
	defines.push_back(define);
}

Define Shared::getDefine(string name)
{
	for(auto define : defines)
	{
		if(define.name == name)
			return define;
	}
	return {"", -1};
}
