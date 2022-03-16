#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "helpers.h"

double **ARR1, **ARR2, **ARR3;
int N;
int P=1; // THREAD COUNT
double NORM = 0.0;
pthread_mutex_t * mutex;

void* matrixMult(void* arg) {
  int start, id, cutSize, end;
  
  id = *(int *)(arg);
  cutSize = N / P;
  start = id * cutSize;
  end = (id+1) * cutSize;

  for(int i=start; i<end; i++) {
    for(int j=0; j<N; j++) {
      for(int k=0; k<N; k++) {
        ARR3[i][j] += ARR1[i][k] * ARR2[k][j];
      }
    }
  }
  pthread_exit(NULL);
}

void* getNorm(void* arg) {
  double localNorm = 0.0;
  int cutSize, start, end, id;

  id = *(int *)(arg);
  cutSize = N / P;
  start = id * cutSize;
  end = (id+1) * cutSize;

  for (int i=start; i<end; i++) {
    double sum = 0.0;
    for(int j=0; j<N; j++) {
      sum += ARR3[j][i];
    }
    if (sum > localNorm) 
      localNorm = sum;
  }
  pthread_mutex_lock(mutex);
  if (localNorm > NORM)
    NORM = localNorm;

  pthread_mutex_unlock(mutex);
  pthread_exit(NULL);
} 

int main(int argc, char **argv) {
 
  clock_t begin = clock(); 
  
  if (argc <2) {
    N = 10;
    P = 5;
  } else {
    N = atoi(argv[1]);
    P = atoi(argv[2]);
  }

  if ( N%P != 0) {
    printf("Invalid ratio of threads to matrix size, exiting...\n");
    return -1;
  }

  ARR1 = allocate_size(N) ;
  ARR2 = allocate_size(N);
  ARR3 = allocate_size(N);
    
  ARR1 = init(N, ARR1);
  ARR2 = init(N, ARR2);
  
 // printArray(ARR1, N);
 // printArray(ARR2, N);

  // THREAD WORK
  pthread_t * workers;
  workers = (pthread_t *) malloc (P * sizeof(pthread_t));
  
  mutex = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mutex, NULL);

  for(int i=0; i<P; ++i) { 
    int *id;
    id = (int *) malloc ( sizeof(int) );
    *id = i;
    pthread_create(&workers[i], NULL, matrixMult,(void*)id );
  }

  for (int i=0; i < P; i++ ) {
    pthread_join(workers[i], NULL);
  }
  
  for(int i=0; i<P; ++i) { 
    int *id;
    id = (int *) malloc ( sizeof(int) );
    *id = i;
    pthread_create(&workers[i], NULL, getNorm,(void*)id );
  }

  for (int i=0; i < P; i++ ) {
    pthread_join(workers[i], NULL);
  }
  
  // printArray(ARR3, N);
 
  // printf("\nNORM: %lf\n", NORM);

  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);
}
