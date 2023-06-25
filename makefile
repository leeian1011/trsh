#!/bin/zsh 

shelldir=src/

all ${shelldir}shell.c:
	clang -c ${shelldir}parser.c
	clang -c ${shelldir}operands_t.c
	clang -c ${shelldir}user_interface.c
	clang -c ${shelldir}builtin_cd.c
	clang -o shell ${shelldir}shell.c parser.o operands_t.o user_interface.o builtin_cd.o

clean:
	rm -rf shell
