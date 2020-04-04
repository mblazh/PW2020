#define _GNU_SOURCE
#define WYMIAR 1000
#define ROZMIAR WYMIAR * WYMIAR

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

double a[ROZMIAR], b[ROZMIAR], c[ROZMIAR];
pthread_t tid[8];
pthread_attr_t attr[8];
cpu_set_t cpuset[8];
struct sched_param params[8];

double czasozajmowacz() {
	int i, j, k;
	int n = WYMIAR;
	
	for(i = 0; i < ROZMIAR; i++) {
		a[i] = 1.0 * i;
	}

	for(i = 0; i < ROZMIAR; i++) {
		b[i]=1.0*(ROZMIAR-i);
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++){
			c[i + n * j] = 0.0;

			for(k = 0; k < n; k++){
				c[i + n * j] += a[i + n * k] * b[k + n * j];
			}
		}
	}

	return(c[ROZMIAR - 1]);
}

void *zadanie_watku(void *arg_wsk) {
	czasozajmowacz();
}

int main() {
	for(short i = 0; i < 8; ++i) {
		printf("Starting thread #%d\n", i);
		pthread_attr_setstacksize(&attr[i], 1024 *  1024 * 10 * (i + 1)); // Set stack size to 1-8MiB
		CPU_ZERO(&cpuset[i]);
		CPU_SET(i, &cpuset[i]); // Unmask CPU 0-7
		params[i].sched_priority = i % 2 ? sched_get_priority_max(SCHED_FIFO) : sched_get_priority_min(SCHED_FIFO); // Set priority to min or max

		pthread_create(&tid[i], &attr[i], zadanie_watku, NULL);

		pthread_setaffinity_np(tid[i], sizeof(cpu_set_t), &cpuset[i]); // Apply CPU mask
		pthread_setschedparam(tid[i], SCHED_FIFO, &params[i]); // Apply priority params

		sleep(1);
	}

	pthread_exit(NULL);
}