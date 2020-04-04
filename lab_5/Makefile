CCOMP = gcc
LOADER = gcc

OPT = -g -DDEBUG

LIB = -pthread

all: step2.out step3.out

step2.out: step2.o 
	$(LOADER) $(OPT) step2.o -o step2.out $(LIB)

step2.o: step2.c
	$(CCOMP) -c $(OPT) step2.c

step3.out: step3.o 
	$(LOADER) $(OPT) step3.o -o step3.out $(LIB)

step3.o: step3.c
	$(CCOMP) -c $(OPT) step3.c

clean:
	rm -f *.o
