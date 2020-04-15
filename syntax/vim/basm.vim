" Vim syntax file
" Language: Basm
" Author:  Breno Cunha Queiroz 
" Date:  28 mar 2020 

if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

setlocal iskeyword+=-
syntax case ignore

syntax match basmComment /--.*/
syntax region basmString start=/"/ skip=/\\"/ end=/"/
syntax region basmChar start=/'/ end=/'/
syntax match basmLabelColon /:/ contained
syntax match basmLabel /\w\+:/ contains=icmcLabelColon
syntax match basmNumber /\<[-]\?\d\+\>/ " Decimal numbers

syntax match basmMainLabel "\.define"
syntax match basmMainLabel "\.code"

" Registers
syntax keyword basmRegister zero
syntax keyword basmRegister ra
syntax keyword basmRegister pc
syntax keyword basmRegister time
syntax keyword basmRegister rand
syntax keyword basmRegister input

syntax keyword basmRegister t0
syntax keyword basmRegister t1
syntax keyword basmRegister t2
syntax keyword basmRegister t3
syntax keyword basmRegister t4
syntax keyword basmRegister t5
syntax keyword basmRegister t6
syntax keyword basmRegister t7

syntax keyword basmRegister a0
syntax keyword basmRegister a1
syntax keyword basmRegister a2
syntax keyword basmRegister a3

syntax keyword basmRegister v0
syntax keyword basmRegister v1
syntax keyword basmRegister v2
syntax keyword basmRegister v3

syntax keyword basmRegister s0
syntax keyword basmRegister s1
syntax keyword basmRegister s2
syntax keyword basmRegister s3
syntax keyword basmRegister s4
syntax keyword basmRegister s5
syntax keyword basmRegister s6
syntax keyword basmRegister s7

" Directives
syntax match basmDirective "\.int"
syntax match basmDirective "\.char"
syntax match basmDirective "\.bool"
syntax match basmDirective "\.string"

" Arithmetic Instructions
syntax keyword basmInstruction add addc
syntax keyword basmInstruction sub subc
syntax keyword basmInstruction mul mulc
syntax keyword basmInstruction div divc
syntax keyword basmInstruction mod modc
syntax keyword basmInstruction shiftl shiftlc
syntax keyword basmInstruction shiftr shiftrc

" Logical Instructions
syntax keyword basmInstruction and
syntax keyword basmInstruction or
syntax keyword basmInstruction xor
syntax keyword basmInstruction not

" Jump Instructions
syntax keyword basmInstructionJ j
syntax keyword basmInstructionJ jeq
syntax keyword basmInstructionJ jne
syntax keyword basmInstructionJ jez
syntax keyword basmInstructionJ jnz
syntax keyword basmInstructionJ jgt
syntax keyword basmInstructionJ jge
syntax keyword basmInstructionJ jlt
syntax keyword basmInstructionJ jle

" Jump Instructions
syntax keyword basmInstructionJ jl
syntax keyword basmInstructionJ jr
syntax keyword basmInstructionJ jeql
syntax keyword basmInstructionJ jnel
syntax keyword basmInstructionJ jezl
syntax keyword basmInstructionJ jnzl
syntax keyword basmInstructionJ jgtl
syntax keyword basmInstructionJ jgel
syntax keyword basmInstructionJ jltl
syntax keyword basmInstructionJ jlel

" Memory Access Instructions
syntax keyword basmInstruction load loadc
syntax keyword basmInstruction store storec

" Data Movement Instructions
syntax keyword basmInstruction move

" Stack Instructions
syntax keyword basmInstruction push
syntax keyword basmInstruction pop

" Exception and Interrupt Instructions
syntax keyword basmInstructionM finish
syntax keyword basmInstructionM breakp

" Terminal Instructions
syntax keyword basmInstructionT printbool
syntax keyword basmInstructionT printchar
syntax keyword basmInstructionT printint
syntax keyword basmInstructionT printstr
syntax keyword basmInstructionT printnl

" Window Instructions
syntax keyword basmInstructionW writebool
syntax keyword basmInstructionW writechar
syntax keyword basmInstructionW writeint
syntax keyword basmInstructionW writestr
syntax keyword basmInstructionW read
syntax keyword basmInstructionW inputw

hi def link basmComment        Comment
hi def link basmNumber         Number
hi def link basmString         String
hi def link basmChar           Char
hi def link basmLabel          Label
hi def link basmMainLabel      MainLabel
hi def link basmRegister       Identifier
hi def link basmDirective      Type
hi def link basmInstruction    Statement
hi def link basmInstructionT   StatementT
hi def link basmInstructionW   StatementW
hi def link basmInstructionJ   StatementJ
hi def link basmInstructionM   StatementM

hi Comment ctermfg    = Gray
hi Label ctermfg      = LightCyan 
hi MainLabel ctermfg  = Cyan 
hi Identifier ctermfg = Green  
hi Number ctermfg     = White
hi Char ctermfg       = White
hi Statement ctermfg  = Magenta
hi StatementT ctermfg = LightMagenta
hi StatementW ctermfg =	LightMagenta 
hi StatementJ ctermfg =	Blue 
hi StatementM ctermfg =	Blue 

let b:current_syntax = "basm"

