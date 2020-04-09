#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	int i, a, sum;
	a = 7;
	sum = 0;

	#pragma omp parallel for schedule(static) num_threads(4) shared(a, sum)
	for(i = 0; i < 500; i++) {
		#pragma omp critical
		{
			sum += a * a;
		}
	}

	printf("Sum is %d\n", sum);

	return 0;
}
