GCC = gcc

all: 

compile:
	${GCC} main.c time_manager.h time_manager.c choice.h choice.c input.h input.c

test:
	${GCC} tchoice.c choice.h choice.c

run:
	./a.out

clean:
	rm -rf *.out

