#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

int main(int argc, char **argv) {
 
  clock_t begin = clock(); 
  int n;
  
  if (argc <2) {
    n = 5;
  } else {
    n = atoi(argv[1]);
  }

  double arr1[n][n], arr2[n][n], arr3[n][n];
 
  // POPULATE MATRICES 
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      arr1[i][j] = 7.0;
      arr2[i][j] = 7.0;
    }
  }
  // NON BLOCKED IJK MATRIX MULT
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      for (int k=0; k<n; k++) {
        arr3[i][j] += arr1[i][k] * arr2[k][j];
      }
    }
  }

  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);
}
