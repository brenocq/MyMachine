#ifndef	DEFINES_H 
#define DEFINES_H

//--------------------------------------//
//--------- Assembler op code ----------//
//--------------------------------------//
#define ADD_CODE                1
#define ADDC_CODE               2
#define SUB_CODE                3
#define SUBC_CODE               4
#define MUL_CODE                5
#define MULC_CODE               6
#define DIV_CODE                7
#define DIVC_CODE               8
#define SHIFT_LEFT_CODE         9
#define SHIFT_RIGHT_CODE        10

#define LOAD_CODE               20
#define LOADC_CODE              21
#define STORE_CODE              22
#define STOREC_CODE             23

#define MOVE_CODE               30

#define AND_CODE                40
#define OR_CODE                 41
#define XOR_CODE                42
#define NOT_CODE                43

#define B_CODE                	50
#define BEQ_CODE                51
#define BNE_CODE                52
#define BEZ_CODE                53
#define BNZ_CODE                54
#define BGT_CODE                55
#define BGE_CODE                56
#define BLT_CODE                57
#define BLE_CODE                58

#define J_CODE               	70 
#define JEQ_CODE                71
#define JNE_CODE                72
#define JEZ_CODE                73
#define JNZ_CODE                74
#define JGT_CODE                75
#define JGE_CODE                76
#define JLT_CODE                77
#define JLE_CODE                78

#define PUSH_CODE               90
#define POP_CODE                91
#define POP_CODE                91
#define POP_CODE                91
#define POP_CODE                91

#define PRINTC_CODE             100
#define PRINTSTR_CODE           101
#define PRINTINT_CODE           102
#define PRINTNL_CODE            103

#define WRITE_CODE				150
#define READ_CODE				151
#define INPUT_CODE				152

//-- REGISTER CODES --//
#define T0_CODE					0
#define T1_CODE 				1
#define T2_CODE 				2
#define T3_CODE 				3
#define T4_CODE 				4
#define T5_CODE 				5
#define T6_CODE 				6
#define T7_CODE 				7

#define A0_CODE 				8
#define A1_CODE 				9
#define A2_CODE 				10
#define A3_CODE 				11

#define V0_CODE 				12
#define V1_CODE 				13
#define V2_CODE 				14
#define V3_CODE 				15

#define S0_CODE					16
#define S1_CODE 				17
#define S2_CODE 				18
#define S3_CODE 				19
#define S4_CODE 				20
#define S5_CODE 				21
#define S6_CODE 				22
#define S7_CODE 				23

#define ZERO_CODE				24
#define RA_CODE					25

//------------------------------------------------// 
//---------- Assembly op codes (binary) ----------// 
//------------------------------------------------// 

//----- Data Manipulation Instructions -----//
#define LOAD            "110000"
#define LOADC           "110010"
#define STORE           "110011"
#define STOREC          "110100"
#define MOVE            "110101"

//----- Peripheric Instructions -----//
//--- FUNCTIONS ---//
//-- Flow Instructions (Begin with "000")--//
#define BRA             "000001"
#define JMP             "000010"
#define PUSH            "000101"
#define POP             "000110"

//-- Logic Instructions (Begin with "001") --//
#define AND            	"001000"
#define OR             	"001001"
#define XOR            	"001010"
#define NOT            	"001011"
#define SHIFTL          "001100"
#define SHIFTR          "001101"

//-- Aritmethic Instructions (Begin with "010") --//
#define ADD             "010000"
#define SUB             "010001"
#define MUL             "010010"
#define DIV             "010011"

//-- Control Instructions (Begin with "011") --//
#define NOP             "011000"
#define HALT            "011001"
#define BREAKP			"011010"

//-- Terminal Instructions (Begin with "100") --//
#define PRINTBOOL       "100000"
#define PRINTC          "100001"
#define PRINTINT        "100010"
#define PRINTSTR        "100011"

//-- Display Instructions (Begin with "101") --//
#define WRITE	        "101000"
#define READ          	"101001"
#define INPUT          	"101010"

//--- REGISTERS ---//
//-- Temporary (Begin with 00) --//
#define T0 				"00000"
#define T1 				"00001"
#define T2 				"00010"
#define T3 				"00011"
#define T4 				"00100"
#define T5 				"00101"
#define T6 				"00110"
#define T7 				"00111"

//-- Arguments (Begin with 01) --//
#define A0 				"01000"
#define A1 				"01001"
#define A2 				"01010"
#define A3 				"01011"

//-- Return (Begin with 01) --//
#define V0 				"01100"
#define V1 				"01101"
#define V2 				"01110"
#define V3 				"01111"

//-- Saved Temporary (Begin with 10) --//
#define S0 				"10000"
#define S1 				"10001"
#define S2 				"10010"
#define S3 				"10011"
#define S4 				"10100"
#define S5 				"10101"
#define S6 				"10110"
#define S7 				"10111"

//-- System (Begin with 11) --//
#define ZERO 			"11000"
#define RA 				"11001"



//---------------------------------------------//
//--------------- Basm strings ----------------//
//---------------------------------------------//

//----- Data Manipulation Instructions -----//
//-- LOAD --//
#define LOAD_STR                "load"
#define LOADC_STR            	"loadc"
//-- STORE --//
#define STORE_STR               "store"
#define STOREC_STR              "storec"

//-- EXTRAS --//
#define MOVE_STR                "move"

//-- ADD --//
#define ADD_STR                 "add"
#define ADDC_STR                "addc"

//-- SUB --//
#define SUB_STR                 "sub"
#define SUBC_STR                "subc"

//-- MUL --//
#define MUL_STR                 "mul"
#define MULC_STR                "mulc"

//-- DIV --//
#define DIV_STR                 "div"
#define DIVC_STR                "divc"

//-- LOGICAL --//
#define AND_STR                 "and"
#define OR_STR                  "or"
#define XOR_STR                 "xor"
#define NOT_STR                 "not"
    
//-- SHIFT --//
#define SHIFT_LEFT_STR       	"shiftl"
#define SHIFT_RIGHT_STR 		"shiftr"

//-- BRANCH --//
#define BRA_STR                 "b"
#define BEQ_STR                 "beq"
#define BNE_STR                 "bne"
#define BZ_STR                  "bez"
#define BNZ_STR                 "bnz"
#define BGT_STR                 "bgt"
#define BGE_STR                 "bge"
#define BLT_STR                 "blt"
#define BLE_STR                 "ble"

//-- JUMP --//
#define JRA_STR                 "j"
#define JEQ_STR                 "jeq"
#define JNE_STR                 "jne"
#define JZ_STR                  "jez"
#define JNZ_STR                 "jnz"
#define JGT_STR                 "jgt"
#define JGE_STR                 "jge"
#define JLT_STR                 "jlt"
#define JLE_STR                 "jle"

//-- PUSH & POP --//
#define PUSH_STR                "push"
#define POP_STR                 "pop"

//-- EXTRAS --//
#define NOP_STR                 "nop"
#define HALT_STR                "halt"
#define BREAKP_STR              "breakp"

//-- TERMINAL --//
#define PRINTC_STR 				"printc"
#define PRINTINT_STR            "printint"
#define PRINTSTR_STR            "printstr"
#define PRINTNL_STR             "printnl"

//-- WINDOW --//
#define WRITE_STR            	"white"
#define READ_STR             	"read"
#define INPUT_STR             	"input"


//-- REGISTERS STRINGS --//
#define T0_STR 					"t0"
#define T1_STR 					"t1"
#define T2_STR 					"t2"
#define T3_STR 					"t3"
#define T4_STR 					"t4"
#define T5_STR 					"t5"
#define T6_STR 					"t6"
#define T7_STR 					"t7"

#define A0_STR  				"a0"
#define A1_STR  				"a1"
#define A2_STR  				"a2"
#define A3_STR  				"a3"

#define V0_STR  				"v0"
#define V1_STR  				"v1"
#define V2_STR  				"v2"
#define V3_STR  				"v3"

#define S0_STR 					"s0"
#define S1_STR 					"s1"
#define S2_STR 					"s2"
#define S3_STR 					"s3"
#define S4_STR 					"s4"
#define S5_STR 					"s5"
#define S6_STR 					"s6"
#define S7_STR 					"s7"

#define ZERO_STR 				"zero"
#define RA_STR  				"ra"

/*  Modelo de memoria

  Obs.: Este modelo nao precisa ser seguido, mas a
  pseudo-instrucao 'alloc' nao devera ser usada
  neste caso.

  [00000 - 16384] : Programa e variaveis (16kw 32kb)
  [16385 - 24576] : Dados estaticos (8kw 16kb)
  [24577 - 30681] : Dados dinamicos (6kw 12kb)
  [30682]         : System call
  [30683 - 30689] : Folga
  [30690 - 32738] : Stack (2kw 4kb)
  [32739 - 32745] : Folga
  [32746]         : Rx
  [32747]         : Tx
  [32748]         : Timer
  [32749 - 32758] : Argumentos
  [32759]	  : Retorno
  [32760 - 32767] : Interrupcoes

*/

/* Definicoes da memoria */
/* Final do espaco de programa */
#define END_PROGRAM_END                 16384
/* Inicio do espaco de dados estativos (alloc) */
#define END_STATIC_DATA_START           16385
/* Final do espaco de dados estaticos */
#define END_STATIC_DATA_END             24576
/* Inicio do espaco de dados dinamicos */
#define END_DYN_DATA_START              24577
/* Final do espaco de dados dinamicos */
#define END_DYN_DATA_END                30681
/* Final do especo para programas e dados */
#define END_PROGRAM_DATA_END            30681
/* Se escrever neste endereco entao causa interrupcao de sistema */
#define END_SYSTEM_CALL                 30682
/* Pilha (folga de 8 palavras) */
#define END_STACK_END                   30690
#define END_STACK_START                 32738
/* Mapeamento em memoria dos registradores de serial e timer */
#define END_SERIAL_RX                   32746
#define END_SERIAL_TX                   32747
#define END_TIMER_REG                   32748
/* Enderecos de posicoes para passagem de argumentos (ate 10 argumentos) */
#define END_ARG(X)                      ((X) + (32749))
/* Endereco de posicao para retorno de funcoes */
#define END_RET                         32759
/* Enderecos das interrupcoes */
#define END_INTP_TIMER                  32760
#define END_INTP_KEYB                   32761
#define END_INTP_SYST                   32762
#define END_INTP_STACK_OVER             32763
#define END_INTP_STACK_UNDER            32764
#define END_INTP_DIV_BY_ZERO            32765
#define END_INTP_SERIAL                 32766
#define END_INTP_RESET                  32767

/* Strings para labels fixos */
/* Inicio da memoria dinamica */
#define L_DYN_DATA_START_STR            "Dynamic_data_start"
#define L_DYN_DATA_END_STR              "Dynamic_data_end"
/* Chamada do sistema */
#define L_SYSTEM_CALL_STR               "System_call"
/* Pilha */
#define L_STACK_END_STR                 "Stack_end"
#define L_STACK_START_STR               "Stack_start"
/* Registradores mapeados em memoria */
#define L_SERIAL_RX_STR                 "Serial_RX"
#define L_SERIAL_TX_STR                 "Serial_TX"
#define L_TIMER_REG_STR                 "Timer"
/* Argumentos */
#define L_ARG0_STR                      "Arg0"
#define L_ARG1_STR                      "Arg1"
#define L_ARG2_STR                      "Arg2"
#define L_ARG3_STR                      "Arg3"
#define L_ARG4_STR                      "Arg4"
#define L_ARG5_STR                      "Arg5"
#define L_ARG6_STR                      "Arg6"
#define L_ARG7_STR                      "Arg7"
#define L_ARG8_STR                      "Arg8"
#define L_ARG9_STR                      "Arg9"
/* Retorno */
#define L_RET_STR                       "Ret"
/* Interrupcoes */
#define L_INTP_TIMER_STR                "Interrupt_Timer"
#define L_INTP_KEYB_STR                 "Interrupt_Keyboard"
#define L_INTP_SYST_STR                 "Interrupt_System"
#define L_INTP_STACK_OVER_STR           "Interrupt_Stack_Overflow"
#define L_INTP_STACK_UNDER_STR          "Interrupt_Stack_Underflow"
#define L_INTP_DIV_BY_ZERO_STR          "Interrupt_Division_by_zero"
#define L_INTP_SERIAL_STR               "Interrupt_Serial_Ready"
#define L_INTP_RESET_STR                "Interrupt_Reset"

/* Tamanho da memoria */
#define MEM_SIZE 32768

//---------------------------------//
//------ Terminal Color Code ------//
//---------------------------------//
// https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
// UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   	"\033[0m"
#define BLACK   	"\033[30m"      /* Black */
#define RED     	"\033[31m"      /* Red */
#define GREEN   	"\033[32m"      /* Green */
#define YELLOW  	"\033[33m"      /* Yellow */
#define BLUE    	"\033[34m"      /* Blue */
#define MAGENTA 	"\033[35m"      /* Magenta */
#define CYAN    	"\033[36m"      /* Cyan */
#define WHITE   	"\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif
