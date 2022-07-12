#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

#define threads 10

int north = 1, south = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void bridge(char from[], int index) {
    srand(time(NULL));
    int crossTime = rand() % 3 + 1;
    printf("%d %s farmer crossing the bridge for %d sec\n", index, from, crossTime);
    sleep(crossTime);
}

void *northFarmer() {
    pthread_mutex_lock(&mutex);
    printf("%dth north farmer pass bridge\n", north);
    bridge("north", north);
    printf("%dth north farmer left bridge\n", north);
    north++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *southFarmer() {
    pthread_mutex_lock(&mutex);
    printf("%dth south farmer pass bridge\n", south);
    bridge("south", south);
    printf("%dth south farmer left bridge\n", south);
    south++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main() {
    pthread_t north[threads], south[threads];
    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0; i < threads; i++) {
        pthread_create(&north[i], NULL, northFarmer, NULL);
        pthread_create(&south[i], NULL, southFarmer, NULL);
    }

    for (size_t i = 0; i < threads; i++) {
        pthread_join(north[i], NULL);
        pthread_join(south[i], NULL); 
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
