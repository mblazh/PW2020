#include <iostream>
#include <mpi.h>

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
		for(int denominator = myrank * 2 - 1; denominator < n * 2; denominator += (npes - 1) * 2) {
			localSum += 4. / denominator * (myrank % 2 ? 1 : -1);
		}
	}

	MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	end = MPI_Wtime();

	if(!myrank) {
		std::cout << "Calculated PI is " << globalSum << std::endl; 
		std::cout << "End of process " << end - start << std::endl;
	}
	
	MPI_Finalize();
	return 0;
}