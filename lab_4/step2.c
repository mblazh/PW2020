#include <stdio.h>
#include <pthread.h>

struct Counter {
	int licznik;
	pthread_mutex_t lock;
};

struct Counter c;

void *incrementCounter() {
	pthread_mutex_lock(&c.lock);

	for (int i = 0; i < 1e5; ++i) {
		++c.licznik;
	}

	pthread_mutex_unlock(&c.lock);

	return NULL;
}

void *decrementCounter() {
	pthread_mutex_lock(&c.lock);

	for (int i = 0; i < 1e5; ++i) {
		--c.licznik;
	}

	pthread_mutex_unlock(&c.lock);

	return NULL;
}

int main() {
	pthread_t tid[2];

	pthread_mutex_init(&c.lock, NULL);

	pthread_create(&tid[0], NULL, incrementCounter, NULL);
	pthread_create(&tid[1], NULL, decrementCounter, NULL);

	for (short i = 0; i < 2; ++i) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&c.lock);

	printf("Final result is %d\n", c.licznik);
	return 0;
}
