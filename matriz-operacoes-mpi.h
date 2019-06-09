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
int **mat_cmpiBloco;


void multiplicarMPI (int *A, int *B, int *C, int MPI_size, int MPI_rank, int chunk_lines_A, int size);
void multiplicaBlocoMPI(int *A, int *B, int *C, int TILE, int MPI_size, int MPI_rank, int chunk_lines_A, int size, int N);
