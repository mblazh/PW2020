#include <stdio.h> 
#include <pthread.h>

short arr[] = {5, 6, 1, 4, 9, 2, 7, 8, 3, 0};

struct Attrs {
	short l;
	short m;
	short r;
};

void *merge(void *a) { 
	struct Attrs *args = a;

	int i, j, k; 
	int n1 = args->m - args->l + 1; 
	int n2 = args->r - args->m; 

	int L[n1], R[n2]; 

	for (i = 0; i < n1; ++i) {
		L[i] = arr[args->l + i]; 
	}

	for (j = 0; j < n2; ++j) {
		R[j] = arr[args->m + 1 + j]; 
	}

	i = 0;
	j = 0;
	k = args->l;
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			arr[k] = L[i]; 
			i++; 
		} else { 
			arr[k] = R[j]; 
			j++; 
		}

		k++; 
	} 

	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 

	return NULL;
} 

void *mergeSort(void *a) {
	struct Attrs *args = a;

	if (args->l < args->r) { 
		pthread_t pid[3];
		struct Attrs attrs[3];

		int m = (args->l + args->r) / 2;

		attrs[0].l = args->l;
		attrs[0].r = m;
		pthread_create(&pid[0], NULL, mergeSort, &attrs[0]);

		attrs[1].l = m + 1;
		attrs[1].r = args->r;
		pthread_create(&pid[1], NULL, mergeSort, &attrs[1]);

		pthread_join(pid[0], NULL);
		pthread_join(pid[1], NULL);

		attrs[2].l = args->l;
		attrs[2].m = m;
		attrs[2].r = args->r;
		pthread_create(&pid[2], NULL, merge, &attrs[2]);
		
		pthread_join(pid[2], NULL);
	} 

	return NULL;
} 

void printArray(short A[], short length) { 
	printf("Array:\n");

	for (short i = 0; i < length; ++i) {
		printf("%d ", A[i]); 
	}

	printf("\n"); 
} 

int main() { 
	short length = sizeof(arr) / sizeof(short);
	struct Attrs attrs;

	printArray(arr, length); 

	attrs.l = 0;
	attrs.r = length - 1;
	mergeSort(&attrs); 

	printArray(arr, length); 

	return 0; 
}