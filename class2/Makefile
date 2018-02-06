SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow
LFLAGS:=-lm

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

stats: stats.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf stats *.o

.PHONY: test
test: stats
	./stats
