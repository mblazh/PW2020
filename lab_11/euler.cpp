#include <iostream>
#include <mpi.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int npes;
	int myrank;
	double start, end;

	int root = 0, n = 0;

	MPI_Init(&argc, &argv);
	
	start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	double localSum = 0;
	double globalSum = 0;
	
	if(!myrank) {
		std::cout << "n: ";
		std::cin >> n;
	}
	
	MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

	if(myrank) {
		int portion = n / (npes - 1);
		int extra = n % (npes - 1);
		int start = (myrank - 1) * portion + std::min(myrank - 1, extra);

		for(int i = start; i < start + portion + (myrank <= extra ? 1 : 0); ++i) {
			localSum += 1. / (i + 1);
		}
	}

	MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	globalSum -= log(n);

	end = MPI_Wtime();

	if(!myrank) {
		std::cout << "Calculated gamma is " << globalSum << std::endl; 
		std::cout << "End of process " << end - start << std::endl;
	}
	
	MPI_Finalize();
	return 0;
}