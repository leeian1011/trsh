#!/bin/zsh 

shelldir=src/

all ${shelldir}shell.c:
	clang -c ${shelldir}parser.c
	clang -c ${shelldir}operands_t.c
	clang -o shell ${shelldir}shell.c parser.o operands_t.o

clean:
	rm -rf shell
