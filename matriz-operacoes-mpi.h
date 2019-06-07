#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include <mpi.h>
#define MPI_MASTER 0


int **mat_a;
int **mat_b;
int **mat_cmpi; 

//#define MPI_MASTER 0
void multiplicarMPI (int *A, int *B, int *C, int N, int L, int M, int argc, char *argv[], int MPI_size, int MPI_rank, int chunk_lines_A, int size);
void multiplicaBlocoMPI(int size, int n, int **A, int **B, int **C, int TILE);
