#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>
#include "helpers.h"

int main (int argc, char **argv) {
  
  clock_t begin = clock();
  int b, n;
  if (argc < 2) {
    n = 10;
    b = 2;
  } else {
    n = atoi(argv[1]);
    b = atoi(argv[2]);
  }


  if ( b>n || n%b != 0 )
    return 1;

	double *arr1, *arr2, *arr3;
  arr1 = malloc(n*n*sizeof(double));
  arr2 = malloc(n*n*sizeof(double));
  arr3 = malloc(n*n*sizeof(double));

  //POPULATE MATRICES
  for (int i=0; i<n; i++) {
      arr1[i] = 7.0;
      arr2[i] = 7.0;
  }

  for (int k=0; k<n; k+=b) {
    for (int i=0; i<n; i+=b) {
      for (int j=0; j<n; j+=b) {
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, b, b, b, 1.0, arr1+k*n+j, n, arr2+i*n+k, n, 1.0, arr3+i*n+j, n);
      }
    }
  }
  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);

}
