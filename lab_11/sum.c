#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	int npes;
	int myrank;
	double start, end;

	int root = 0;
	int j,k,S[10],n=10,p;

	MPI_Init(&argc, &argv);
	
	start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	MPI_Bcast( &n, n, MPI_INT,root, MPI_COMM_WORLD );

	int localsum = 0;
	int globalsum = 0;

	for (int i = myrank; i < n; i += npes ) {
	    S[i] = i;
	    localsum += S[i];
		printf("Rank %d", S[i]);
	}

	printf("Localsum %d", localsum);

	MPI_Reduce( &localsum, &globalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

	end = MPI_Wtime();

	if(!myrank){
		printf("Globalsum %d", globalsum);
		printf("end of process %lf", end-start);
	}
	
	MPI_Finalize();
	return 0;
}
