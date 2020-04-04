#include <stdio.h>
#include <pthread.h>

void * writeTID() {
	printf("This thread ID is %ld\n", pthread_self());
	pthread_exit(NULL);

	return NULL;
}

int main() {
	pthread_t tid;

	for (short i = 0; i < 10; ++i) {
		pthread_create(&tid, NULL, writeTID, NULL);
	}
}
