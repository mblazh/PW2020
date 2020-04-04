CCOMP = gcc
LOADER = gcc

OPT = -g -DDEBUG

LIB = -pthread

all: watki.out step2.out step4.out step6.out

watki.out: watki.o 
	$(LOADER) $(OPT) watki.o -o watki.out $(LIB)

watki.o: watki.c
	$(CCOMP) -c $(OPT) watki.c

step2.out: step2.o 
	$(LOADER) $(OPT) step2.o -o step2.out $(LIB)

step2.o: step2.c
	$(CCOMP) -c $(OPT) step2.c

step4.out: step4.o 
	$(LOADER) $(OPT) step4.o -o step4.out $(LIB)

step4.o: step4.c
	$(CCOMP) -c $(OPT) step4.c

step6.out: step6.o 
	$(LOADER) $(OPT) step6.o -o step6.out $(LIB)

step6.o: step6.c
	$(CCOMP) -c $(OPT) step6.c

clean:
	rm -f *.o
