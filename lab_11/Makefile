LOADER = mpic++

OPT = -g -DDEBUG

all: leibniz.out euler.out

leibniz.out: leibniz.cpp
	$(LOADER) $(OPT) leibniz.cpp -o leibniz.out

testLeibniz:
	mpirun -np 7 ./leibniz.out 

euler.out: euler.cpp
	$(LOADER) $(OPT) euler.cpp -o euler.out

testEuler:
	mpirun -np 7 ./euler.out 

clean:
	rm -f *.out