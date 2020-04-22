LOADER = gcc

OPT = -g -DDEBUG

LIB = -fopenmp -lm

all: step2.out step4.out

step2.out:
	$(LOADER) $(OPT) step2.c -o step2.out $(LIB)

step4.out:
	$(LOADER) $(OPT) step4.c -o step4.out $(LIB)

clean:
	rm -f *.o
	rm -f *.out
