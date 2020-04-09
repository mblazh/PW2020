#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	int i, a;
	a = 7;

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(static, 3)
	for(i = 0; i < 15; i++) {
		printf("Thread %d a=%d\n", omp_get_thread_num(), a);
		a++;
	}

	printf("\n");

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(static)
	for(i = 0; i < 15; i++) {
		printf("Thread %d a=%d\n", omp_get_thread_num(), a);
		a++;
	}

	printf("\n");

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(dynamic, 3)
	for(i = 0; i < 15; i++) {
		printf("Thread %d a=%d\n", omp_get_thread_num(), a);
		a++;
	}

	printf("\n");

	#pragma omp parallel for firstprivate(a) num_threads(4) schedule(dynamic)
	for(i = 0; i < 15; i++) {
		printf("Thread %d a=%d\n", omp_get_thread_num(), a);
		a++;
	}

	printf("\n");

	return 0;
}
