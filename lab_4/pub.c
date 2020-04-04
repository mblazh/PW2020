#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 3 // Number of mugs
#define K 4 // Number of clients
#define GULP 2 // Maximum time needed to drink 

struct Pub {
	pthread_mutex_t mugs[N];
};

struct ClientAttrs {
	struct Pub *pub;
	short id;
};

void *booze(void *attrs){
	struct ClientAttrs *clientAttrs = attrs;
	struct Pub *pub = clientAttrs->pub;
	short *clientId = &clientAttrs->id;

	for(int i = 0; i < 2; ++i) {
		short t = (rand() % (GULP + 1));
		short mugId = -1;

		// Find and take free mug
		while(mugId == -1) {
			for(short j = 0; j < N; ++j) { 
				if(pthread_mutex_trylock(&pub->mugs[j]) == 0) {
					mugId = j;
					break;
				}

				if (j == N - 1) {
					j = -1;
				}
			}
		}
		
		printf("Klient nr %d zamawia piwo w kuflu nr %d\n", *clientId, mugId);
		fflush(stdout);

		sleep(t); // Drink
		
		printf("Klient nr %d oddaje kufel nr %d po czasie %d\n", *clientId, mugId, t);
		fflush(stdout);
		
		// Return mug
		pthread_mutex_unlock(&pub->mugs[mugId]);
	}

	return(NULL);
}

int main() {
	srand(time(0));
	struct Pub pub;
	pthread_t client[K];
	struct ClientAttrs clientAttrs[K];
	for (short i = 0; i < N; ++i) {
		pthread_mutex_init(&pub.mugs[i], NULL);
	}
	
	// Spawn clients
	for(short i = 0; i < K; ++i) {
		clientAttrs[i].id = i;
		clientAttrs[i].pub = &pub;

		pthread_create(&client[i], NULL, booze, &clientAttrs[i]);
	}
	
	// Wait for clients to get drunk
	for(short i =  0; i < K; ++i) {
		pthread_join(client[i], NULL);
	}
	
	for (short i = 0; i < N; ++i) {
		pthread_mutex_destroy(&pub.mugs[i]);
	}

	return 0;
}
