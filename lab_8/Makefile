LOADER = gcc

OPT = -g -DDEBUG

LIB = -fopenmp -lm

all: simd.out fib.out test_search_max_openmp

simd.out:
	$(LOADER) $(OPT) simd/simd.c -o simd/simd.out $(LIB)

fib.out:
	$(LOADER) $(OPT) fib/fib.c -o fib/fib.out $(LIB)

test_search_max_openmp:
	cd search_max && $(MAKE)

clean:
	rm -f *.o
	rm -f *.out
