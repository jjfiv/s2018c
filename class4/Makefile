SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow -Wno-unused-parameter -Wno-unused-variable -g
LFLAGS:=-lncurses
PROGRAM:=program.exe

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

${PROGRAM}: main.o maze.o point.o game.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf ${PROGRAM} *.o

.PHONY: test
test: ${PROGRAM}
	./${PROGRAM} maze.txt

.PHONY: debug
debug: test
	gdb ${PROGRAM} -ex 'run maze.txt'
