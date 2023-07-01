#!/bin/zsh 

shelldir=src/

all ${shelldir}shell.c:
	clang -c ${shelldir}execute_parser.c
	clang -c ${shelldir}type_parser.c
	clang -c ${shelldir}operands_t.c
	clang -c ${shelldir}user_interface.c
	clang -c ${shelldir}builtin_cd.c
	clang -c ${shelldir}pipe_parser.c
	clang -c ${shelldir}pipe_execute.c
	clang -c ${shelldir}redirect_parser.c
	clang -o shell ${shelldir}shell.c execute_parser.o type_parser.o operands_t.o user_interface.o builtin_cd.o pipe_parser.o pipe_execute.o redirect_parser.o

clean:
	rm -rf shell
