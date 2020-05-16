#include <iostream>
#include <mpi.h>
#include <cstring>

#define TESTS 100

struct Data {
	int n;
	double d;
	char s[30];
};

std::ostream& operator<<(std::ostream& os, const Data& dt) {
	os << "{n: " << dt.n << ", d: " << dt.d << ", s: \"" << dt.s << "\"}";

	return os;
}

int main(int argc, char *argv[]) {
	int npes;
	int myrank;
	double start, end;

	MPI_Init(&argc, &argv);
	
	start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	MPI_Datatype dtData;
	MPI_Type_contiguous(1, MPI_INT, &dtData);
	MPI_Type_contiguous(1, MPI_DOUBLE, &dtData);
	MPI_Type_contiguous(30, MPI_CHAR, &dtData);
	MPI_Type_commit(&dtData);

	for (unsigned short i = 0; i < TESTS; ++i) {
		if (myrank == 0) {
			Data x;
			x.n = i;
			x.d = 3.14;
			strcpy(x.s, "sample string");

			MPI_Send(&x, 1, dtData, 1, 13, MPI_COMM_WORLD);
		} else if (myrank == 1) {
			MPI_Status status;
			Data y;

			MPI_Recv(&y, 1, dtData, 0, 13, MPI_COMM_WORLD, &status);
			std::cout << "process 1 received data " << y << " from process 0" << std::endl;
		}
	}

	end = MPI_Wtime();
	MPI_Finalize();

	if (myrank == 0) {
		std::cout << "end of process " << end - start << std::endl;
		std::cout << "average time per struct sent is " << (end - start) / TESTS << std::endl;
	}

	return 0;
}
