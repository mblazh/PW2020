CCOMP = gcc
LOADER = gcc

OPT = -g -DDEBUG

LIB = -pthread

all: step2.out pub.out

step2.out: step2.o 
	$(LOADER) $(OPT) step2.o -o step2.out $(LIB)

step2.o: step2.c
	$(CCOMP) -c $(OPT) step2.c

pub.out: pub.o 
	$(LOADER) $(OPT) pub.o -o pub.out $(LIB)

pub.o: pub.c
	$(CCOMP) -c $(OPT) pub.c

clean:
	rm -f *.o
