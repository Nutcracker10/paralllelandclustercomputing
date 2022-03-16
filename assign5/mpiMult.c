#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "helpers.h"


int main(int argc, char **argv) { 
  clock_t begin = clock(); 

  int N, P; // MATRIX SIZE AND THREAD COUNT
  int rank, sender, rows, numWorkers, offset;
  
  if (argc <2) {
    N = 4;
  } else {
    N = atoi(argv[1]);
  }
  
  double ARR1[N][N], ARR2[N][N], ARR3[N][N];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if ( N%P != 0) {
    printf("Invalid ratio of threads to matrix size, exiting...\n");
    return -1;
  }

  offset = 0;
  numWorkers = P-1;

  if (rank == 0) { //master begins
    for (int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        ARR1[i][j] = 7.0;
        ARR2[i][j] = 7.0;
        ARR3[i][j] = 0.0;
      }
    }

    //printArray(ARR1, N);
    //printArray(ARR2, N);
    rows = N / numWorkers;
    for(int i=1; i<=numWorkers; i++){
      MPI_Send(&offset, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      MPI_Send(&ARR1, N*N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
      MPI_Send(&ARR2[0][0], N*N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
      offset = offset + rows;
    }

    for (int i=1; i<=numWorkers; i++) { //receive results from workers
      sender = i;
      MPI_Recv(&offset, 1, MPI_INT, sender, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, sender, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&ARR3[offset][0], rows*N, MPI_DOUBLE, sender, 2, MPI_COMM_WORLD, &status);
    }

    clock_t end = clock();
    double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("%f,\n", time_spent);
  } // end of master

 
if (rank > 0) { // workers begin;
     
    MPI_Recv(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&ARR1, N*N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&ARR2, N*N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
    for(int i=0; i<N; i++) {
      for(int j=0; j<rows; j++) {
        for(int k=0; k<N; k++) {
          ARR3[j][i] += ARR1[j][k] * ARR2[k][i];
        }
      }
    }

    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&ARR3, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);

  }

  MPI_Finalize();

}
