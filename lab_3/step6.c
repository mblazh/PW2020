#define _GNU_SOURCE
#define WYMIAR 1000
#define ROZMIAR WYMIAR * WYMIAR

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int zmienna_wspolna = 0;
double a[ROZMIAR], b[ROZMIAR], c[ROZMIAR];
pthread_t tid[10];
pthread_attr_t attr;

void *zadanie_watku (void *arg_wsk) { 
	pthread_attr_t attr;

	pthread_getattr_np(pthread_self(), &attr);

	int s;
	size_t stack_size;
	void *stack_addr;

	pthread_attr_getdetachstate(&attr, &s);
	printf("Detach state\t%d\n", s);

	pthread_attr_getstack(&attr, &stack_addr, &stack_size);
	printf("Stack size is\t%ld\n\n", stack_size);

	pthread_self();
	pthread_attr_destroy(&attr);

	return(NULL);
}

int main() {
	for(short i = 0; i < 10; ++i) {
		pthread_attr_init(&attr);

		pthread_attr_setdetachstate(&attr, rand() % 2);

		pthread_attr_setstacksize(&attr, (int) (rand() / 5));

		pthread_create(&tid[i], &attr, zadanie_watku, NULL);

		pthread_attr_destroy(&attr);

		sleep(1);  
	}

	pthread_exit(NULL);
}
