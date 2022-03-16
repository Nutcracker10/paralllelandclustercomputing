#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "helpers.h"


void matriximult(int N, int P, double **ARR1, double **ARR2, double **ARR3) {
  int start, id, cutSize, end;
  cutSize = N / P;
  //#pragma omp parallel private(id, start, end)
  id = omp_get_thread_num();
  start = id * cutSize;
  end = (id+1) * cutSize;

  #pragma omp parallel for schedule(guided)
    for(int i=start; i<end; i++) {
      for(int j=0; j<N; j++) {
        for(int k=0; k<N; k++) {
          ARR3[i][j] += ARR1[i][k] * ARR2[k][j];
        }
      }
    }
  
}

double getNorm(int N, int P, double **ARR3) {
  double localNorm = 0.0;
  double Norm = 0.0;
  int cutSize, start, end, id;
  cutSize = N / P;
  id = omp_get_thread_num();
  start = id * cutSize;
  end = (id+1) * cutSize;

  #pragma omp parallel for schedule(guided) 
    for (int i=start; i<end; i++) {
      double sum = 0.0;
      for(int j=0; j<N; j++) {
        sum += ARR3[j][i];
      }
      if (sum > localNorm)
        localNorm = sum;
    }
    if (localNorm > Norm)
      Norm = localNorm;
    

  return Norm;
}

int main(int argc, char **argv) { 
  clock_t begin = clock(); 

  int N, P;
  double **ARR1, **ARR2, **ARR3;
  double NORM = 0.0;
  
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

  ARR1 = allocate_size(N);
  ARR2 = allocate_size(N);
  ARR3 = allocate_size(N);
    
  ARR1 = init(N, ARR1);
  ARR2 = init(N, ARR2);
  ARR3 = initZero(N, ARR3);


  //printArray(ARR1, N);
  //printArray(ARR2, N);

  // THREAD WORK
  omp_set_num_threads(P);
  matriximult(N, P, ARR1, ARR2, ARR3);

  //printArray(ARR3, N);
 
  //printf("\nNORM: %lf\n", getNorm(N, P, ARR3));

  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);
}
