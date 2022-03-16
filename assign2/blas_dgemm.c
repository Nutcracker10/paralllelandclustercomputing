#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>
#include "helpers.h"

int main (int argc, char **argv) {
  
  clock_t begin = clock();
  int  n;
  if (argc < 2) {
    n = 10;
  } else {
    n = atoi(argv[1]);
  }

	double *arr1, *arr2, *arr3;
  arr1 = malloc(n*n*sizeof(double));
  arr2 = malloc(n*n*sizeof(double));
  arr3 = malloc(n*n*sizeof(double));

  //POPULATE MATRICES
  for (int i=0; i<n; i++) {
      arr1[i] = 7.0;
      arr2[i] = 7.0;
  }

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, arr1, n, arr2, n, 1.0, arr3, n);

  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);

}
