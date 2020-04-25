#include <stdio.h>
#include <omp.h>

int fibbonacci(int n) {
	if (0 == n || 1 == n) {
		return n;
	} else {
		return fibbonacci(n - 1) + fibbonacci(n - 2);
	}
}

int fibbonacciTask(int n) {
	if (0 == n || 1 == n) {
		return n;
	} else {
		int tmp[2];
		
		#pragma omp task shared(n, tmp) if(n < 20)
		tmp[0] = fibbonacci(n - 1);

		#pragma omp task shared(n, tmp) if(n < 20)
		tmp[1] = fibbonacci(n - 2);
		
		#pragma omp taskwait
		return tmp[0] + tmp[1];
	}
}

int main() {
	for(int i = 0; i < 15; ++i) {
		printf("%d ", fibbonacci(i));
	}

	printf("\n");

	for(int i = 0; i < 15; ++i) {
		printf("%d ", fibbonacciTask(i));
	}

	printf("\n");

	return 0;
}