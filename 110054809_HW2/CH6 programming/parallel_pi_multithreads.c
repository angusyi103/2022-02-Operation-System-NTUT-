#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define SEED 7

unsigned int seed = 7;
pthread_mutex_t mutex;
// defining the total number of points from which random points are selected
int N = 800000000;
//global variable for number of points inside unit circle
int totalPts = 0;

//Random number generator with linear congruential generator
double RandUint (long i) {
  seed = seed * 1103515245 + 123456;
  return seed / (double)UINT_MAX;
}

//function to estimate pi using pthreads
void *EstimateParallel (void *param) {
    int len = *(int *) param;
    for (int i = 0; i < len; i++) {
      double x = (double)RandUint (i);
      double y = (double)RandUint (i);

      pthread_mutex_lock(&mutex);
      if (((x * x) + (y * y)) <= 1) {
          totalPts++;
      }
      pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

int main () {
  int threads = 10;
  int pointsPerThread = N/threads;
  double pi = 0;
  // calculating the time taken by the function estimate()
  clock_t t;
  t = clock ();

  pthread_t runners[threads];
  pthread_mutex_init(&mutex, NULL);

  for (size_t i = 0; i < threads; i++) {
    pthread_create(&runners[i], 0, &EstimateParallel, &pointsPerThread);
  }

  for (size_t i = 0; i < threads; i++) {
    pthread_join(runners[i], NULL);
  }

  t = clock () - t;

  // printf("%f")
  pi = (4.0 * totalPts) / N;
  printf("points: %d\n", totalPts);

  double timeTaken = ((double)t) / CLOCKS_PER_SEC;     // in seconds
  printf("pi = %lf\n", pi);
  printf("EstimateParallel() took %f seconds to execute \n", timeTaken);

  return 0;
}
