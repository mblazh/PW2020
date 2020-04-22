#include <stdio.h>
#include <omp.h>
#include <math.h>

void fillMatrix(size_t n, size_t m, int matrix[n][m], short number) {
	for (short i = 0; i < n; ++i) {
		for (short j = 0; j < m; ++j) {
			matrix[i][j] = number;
		}
	}
}

void multiplyMatrices(size_t n, size_t m, size_t p, int matrix1[n][m], int matrix2[m][p], int result[n][p]) {
	for (short i = 0; i < n; ++i) {
		for (short j = 0; j < p; ++j) {
			for (short k = 0; k < m; ++k) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

// void printMatrix(size_t n, size_t m, int matrix[n][m]) {
// 	for (short i = 0; i < n; ++i) {
// 		for (short j = 0; j < m; ++j)
// 			printf("%d\t", matrix[i][j]);

// 		printf("\n");
// 	}
// }

int main() { 
	for (short i = 0; i < 3; ++i) {
		double start, end;
		short n = 2 * pow(10, i);
		short m = 3 * pow(10, i);
		short p = 4 * pow(10, i); 
		int matrix1[n][m], matrix2[m][p], matrix3[n][p];
	
		printf("Multiplying %dx%d & %dx%d matrices\n", n, m, m, p);

		fillMatrix(n, m, matrix1, 2);
		fillMatrix(m, p, matrix2, 2);
		fillMatrix(n, p, matrix3, 0);

		start = omp_get_wtime();
		multiplyMatrices(n, m, p, matrix1, matrix2, matrix3);
		end = omp_get_wtime();

		printf("Time taken:\t%f\n", end - start);

		// printMatrix(n, p, matrix3);
	}

	return 0;
}