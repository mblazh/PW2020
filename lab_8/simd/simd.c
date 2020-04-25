#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void fillVector(size_t n, double vector[n]) {
	// srand(time(NULL));

	for (; n > 0; --n) {
		vector[n - 1] = (double)rand() / RAND_MAX * 2.0 - 1.0;
	}
}

void scalarMultiplyVectors(size_t n, double vector1[n], double vector2[n], double *result) {
	for (; n > 0; --n) {
		*result += vector1[n - 1] * vector2[n - 1];
	}
}

void scalarMultiplyVectorsOmp(size_t n, double vector1[n], double vector2[n], double *result) {
	#pragma omp parallel for shared(vector1, vector2, result) num_threads(8) schedule(static)
	for (int i = n; i > 0; --i) {
		double tmp = vector1[i - 1] * vector2[i - 1];

		#pragma omp critical
		{
			*result += tmp;
		}
	}
}

void scalarMultiplyVectorsSimd(size_t n, double vector1[n], double vector2[n], double *result) {
	#pragma omp simd
	for (int i = n; i > 0; --i) {
		*result += vector1[i - 1] * vector2[i - 1];
	}
}

int main() { 
	int n = 100000;
	double start, end;
	double vector1[n], vector2[n], result;
	
	fillVector(n, vector1);
	fillVector(n, vector2);

	result = 0;
	start = omp_get_wtime();
	scalarMultiplyVectors(n, vector1, vector2, &result);
	end = omp_get_wtime();
	printf("Vector multiplication result is:\t\t\t%lf\nTime taken:\t%f\n", result, end - start);

	result = 0;
	start = omp_get_wtime();
	scalarMultiplyVectorsOmp(n, vector1, vector2, &result);
	end = omp_get_wtime();
	printf("Vector multiplication with the use of omp result is:\t%lf\nTime taken:\t%f\n", result, end - start);

	result = 0;
	start = omp_get_wtime();
	scalarMultiplyVectorsSimd(n, vector1, vector2, &result);
	end = omp_get_wtime();
	printf("Vector multiplication with the use of simd result is:\t%lf\nTime taken:\t%f\n", result, end - start);

	return 0;
}