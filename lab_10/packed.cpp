#include <iostream>
#include <mpi.h>
#include <cstring>

#define TESTS 100

int main(int argc, char *argv[]) {
	int npes;
	int myrank;
	double start, end;

	MPI_Init(&argc, &argv);
	
	start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	for (unsigned short i = 0; i < TESTS; ++i) {
		char buffer[42];
		int position = 0;

		if (myrank == 0) {
			int n = i;
			double d = 3.14;
			char s[30]; strcpy(s, "sample string");

			MPI_Pack(&n, 1, MPI_INT, buffer, 42, &position, MPI_COMM_WORLD);
			MPI_Pack(&d, 1, MPI_DOUBLE, buffer, 42, &position, MPI_COMM_WORLD);
			MPI_Pack(s, 30, MPI_CHAR, buffer, 42, &position, MPI_COMM_WORLD);
			MPI_Send(buffer, position, MPI_PACKED, 1, 13, MPI_COMM_WORLD);
		} else if (myrank == 1) {
			MPI_Status status;
			int n;
			double d;
			char s[30];

			MPI_Recv(buffer, 42, MPI_PACKED, 0, 13, MPI_COMM_WORLD, &status);
			MPI_Unpack(buffer, 42, &position, &n, 1, MPI_INT, MPI_COMM_WORLD);
			MPI_Unpack(buffer, 42, &position, &d, 1, MPI_DOUBLE, MPI_COMM_WORLD);
			MPI_Unpack(buffer, 42, &position, s, 30, MPI_CHAR, MPI_COMM_WORLD);

			std::cout << "process 1 received packed data [" << n << ", " << d << ", \"" << s << "\"] from process 0" << std::endl;
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
