#include <stdio.h> 
#include <pthread.h>

#define LENGTH 100

short arr[LENGTH];

struct Attrs {
	short i;
};

void *sieve(void *a) {
	struct Attrs *args = a; 

	for (short i = 0; i < LENGTH; ++i) {
		if (arr[args->i] >= 2 && arr[i] != arr[args->i] && arr[i] % arr[args->i] == 0) {
			arr[i] = -1;
		}
	}
}

void printArray(short A[], short length) { 
	printf("Array:\n");

	for (short i = 0; i < length; ++i) {
		if (A[i] >= 0) {
			printf("%d ", A[i]); 
		}
	}

	printf("\n"); 
} 

int main() { 
	pthread_t pid[LENGTH];
	struct Attrs attrs[LENGTH];

	for (short i = 0; i < LENGTH; ++i) {
		arr[i] = i;
	}

	printArray(arr, LENGTH); 

	for (short i = 1; i < LENGTH; ++i) {
		attrs[i].i = i;
		pthread_create(&pid[i], NULL, sieve, &attrs[i]);
	}

	for (short i = 1; i < LENGTH; ++i) {
		pthread_join(pid[i], NULL);
	}

	printArray(arr, LENGTH); 

	return 0; 
}