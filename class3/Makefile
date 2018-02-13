SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow -Wno-unused-parameter
LFLAGS:=
PROGRAM:=program.exe

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

${PROGRAM}: pool_list.o test_pool_list.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf ${PROGRAM} *.o

.PHONY: test
test: ${PROGRAM}
	./${PROGRAM} input_data.txt
