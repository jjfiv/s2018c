SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow
LFLAGS:=-lm

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

program.exe: pool_list.o test_pool_list.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf program.exe *.o

.PHONY: test
test: program
	./program.exe input_data.txt
