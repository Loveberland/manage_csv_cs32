GCC = gcc

all: 

compile:
	${GCC} main.c choice.h choice.c input.h input.c

test:
	${GCC} tchoice.c choice.h choice.c

run:
	./a.out

clean:
	rm -rf *.out

