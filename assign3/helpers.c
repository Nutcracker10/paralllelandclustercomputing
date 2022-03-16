#include <stdio.h>
#include <stdlib.h>

int min(int x, int y) {
 if (x < y ) { return x; } else { return y; }  
}

double ** allocate_size (int N) {
  double *  vals= (double *) malloc( N * N * sizeof(double) );
  double ** pointers = (double **) malloc (N * sizeof(double*));

  for (int i=0; i<N; i++) {
    pointers[i] = &vals[i * N];
  }

  return pointers;
}

double ** init(int N, double ** arr) {
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      arr[i][j] = 7.0;
    }
  }
  return arr;
}

void printArray( double ** arr, int N) {

  for (int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      printf("%lf ", arr[i][j]);
    }
    printf("\n");
  }
  printf("\n-------------------------\n");
}
