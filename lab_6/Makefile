LOADER = gcc

OPT = -g -DDEBUG

LIB = -fopenmp

all: step2.out step3.out step4.out step5.out step6.out

step2.out:
	$(LOADER) $(OPT) step2.c -o step2.out $(LIB)

step3.out:
	$(LOADER) $(OPT) step3.c -o step3.out $(LIB)

step4.out:
	$(LOADER) $(OPT) step4.c -o step4.out $(LIB)

step5.out:
	$(LOADER) $(OPT) step5.c -o step5.out $(LIB)

step6.out:
	$(LOADER) $(OPT) step6.c -o step6.out $(LIB)

clean:
	rm -f *.o
	rm -f *.out
