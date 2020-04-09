#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	double start, end;
	int i, a;
	a = 7;

	start = omp_get_wtime();

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(static, 3)
	for(i = 0; i < 150; i++) {
		a++;
	}

	end = omp_get_wtime();
	printf("Static 3:\t%f\n", end - start);

	start = omp_get_wtime();

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(static)
	for(i = 0; i < 150; i++) {
		a++;
	}

	end = omp_get_wtime();
	printf("Static auto:\t%f\n", end - start);

	start = omp_get_wtime();

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(dynamic, 3)
	for(i = 0; i < 150; i++) {
		a++;
	}

	end = omp_get_wtime();
	printf("Dynamic 3:\t%f\n", end - start);

	start = omp_get_wtime();

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(dynamic)
	for(i = 0; i < 150; i++) {
		a++;
	}

	end = omp_get_wtime();
	printf("Dynamic auto:\t%f\n", end - start);

	return 0;
}
