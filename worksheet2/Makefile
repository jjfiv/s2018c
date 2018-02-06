SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow
LFLAGS:=-lm

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

fizzbuzz: fizzbuzz.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf fizzbuzz *.o

.PHONY: test
test: fizzbuzz
	rm -f fizzbuzz.txt
	./fizzbuzz
	cat fizzbuzz.txt
