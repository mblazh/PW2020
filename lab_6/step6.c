#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	double start, end;
	int i, a, sum;
	omp_lock_t writelock;
	omp_init_lock(&writelock);
	a = 7;
	sum = 0;

	start = omp_get_wtime();

	#pragma omp parallel for schedule(static) num_threads(4) shared(a) reduction(+:sum)
	for(i = 0; i < 500; i++) {
		short square = a * a;
		sum += square;
	}

	end = omp_get_wtime();
	printf("Reduction:\t%f\n", end - start);

	sum = 0;

	start = omp_get_wtime();

	#pragma omp parallel for schedule(static) num_threads(4) shared(a, sum)
	for(i = 0; i < 500; i++) {
		short square = a * a;

		#pragma omp critical
		{
			sum += square;
		}
	}

	end = omp_get_wtime();
	printf("Critical:\t%f\n", end - start);

	sum = 0;

	start = omp_get_wtime();

	#pragma omp parallel for schedule(static) num_threads(4) shared(a, sum)
	for(i = 0; i < 500; i++) {
		short square = a * a;
		omp_set_lock(&writelock);
		sum += square;
		omp_unset_lock(&writelock);
	}

	end = omp_get_wtime();
	printf("Lock:\t\t%f\n", end - start);

	return 0;
}
