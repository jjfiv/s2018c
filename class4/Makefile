SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow -Wno-unused-parameter -g
LFLAGS:=
PROGRAM:=program.exe

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

${PROGRAM}: main.o maze.o
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
