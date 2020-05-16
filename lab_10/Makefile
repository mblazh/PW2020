LOADER = mpic++

OPT = -g -DDEBUG

all: dataType.out packed.out dataTypeBuffered.out packedBuffered.out dataTypeSynchronous.out packedSynchronous.out

dataType.out: dataType.cpp
	$(LOADER) $(OPT) dataType.cpp -o dataType.out

testDataType:
	mpirun -np 4 ./dataType.out

packed.out: packed.cpp
	$(LOADER) $(OPT) packed.cpp -o packed.out

testPacked:
	mpirun -np 4 ./packed.out

dataTypeBuffered.out: dataTypeBuffered.cpp
	$(LOADER) $(OPT) dataTypeBuffered.cpp -o dataTypeBuffered.out

testDataTypeBuffered:
	mpirun -np 4 ./dataTypeBuffered.out

packedBuffered.out: packedBuffered.cpp
	$(LOADER) $(OPT) packedBuffered.cpp -o packedBuffered.out

testPackedBuffered:
	mpirun -np 4 ./packedBuffered.out

dataTypeSynchronous.out: dataTypeSynchronous.cpp
	$(LOADER) $(OPT) dataTypeSynchronous.cpp -o dataTypeSynchronous.out

testDataTypeSynchronous:
	mpirun -np 4 ./dataTypeSynchronous.out

packedSynchronous.out: packedSynchronous.cpp
	$(LOADER) $(OPT) packedSynchronous.cpp -o packedSynchronous.out

testPackedSynchronous:
	mpirun -np 4 ./packedSynchronous.out

clean:
	rm -f *.out