#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

int main(int argc, char **argv) {
  clock_t begin = clock();
  int n;
  int b;

  if (argc != 3) {
    n = 10;
    b = 2;
  } else {
    n = atoi(argv[1]);
    b = atoi(argv[2]);
  }

  if ( (n%b) != 0 || n<b) 
    return 0;

  double arr1[n][n], arr2[n][n], arr3[n][n];
 
  // POPULATE MATRICES 
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      arr1[i][j] = 7;
      arr2[i][j] = 7;
    }
  }
  
  for (int i=0; i<n; i+=b) {
    for (int j=0; j<n; j+=b) {
      for (int k=0; k<n; k+=b) {
        
        for (int x=i; x<min(i+b, n); x++) {
          for (int y=k; y<min(k+b, n); y++) {
            double item = arr1[x][y];
            for (int z=j; z<min(j+b, n); z++) {
                arr3[x][z] += item * arr2[y][z];
            }
          }
        }
      }
    }
  }
  clock_t end = clock();
  double time_spent = 0.0;
  time_spent += (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f,\n", time_spent);
}
