SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

operations: operations.o main.o

.PHONY: clean
clean:
	@rm -rf operations *.o

.PHONY: test
test: operations
	./operations
