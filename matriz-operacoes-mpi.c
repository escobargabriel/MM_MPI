#include "matriz-operacoes-mpi.h"

void multiplicarMPI(int *A, int *B, int *C, int MPI_size, int MPI_rank, int chunk_lines_A, int size) {

	int i, j, k;
		
		
		MPI_Scatter(A, chunk_lines_A * size, MPI_INT, A, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

		MPI_Bcast(B, size * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

		/* Regular multiply inside the tiles */
		for(i = 0; i < chunk_lines_A; i++)
			for(j = 0; j < size; j++)
				for(k = 0; k < size; k++)
					C[i * size + j] += A[i * size + k] * B[k * size + j];

		MPI_Gather(C, chunk_lines_A * size, MPI_INT, C, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

}

void multiplicaBlocoMPI(int *A, int *B, int *C, int TILE,int MPI_size, int MPI_rank, int chunk_lines_A, int size, int N){
	int i, j, k, x, y, z;
	 
	MPI_Scatter(A, chunk_lines_A * size, MPI_INT, A, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

	MPI_Bcast(B, size * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

	for(i = 0; i < chunk_lines_A; i += TILE){
	    for(j = 0; j < size; j += TILE){
	        for(k = 0; k < size; k += TILE){
	            for(x = i; x < i + TILE; x++){
		            for(y = j; y < j + TILE; y++){
		                for(z = k; z < k + TILE; z++){
		                    C[x * size + y] += A[x * size + z] * B[z * size + y];
                        }
                    }
                }
            }
        }
    }

   MPI_Gather(C, chunk_lines_A * size, MPI_INT, C, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD); 
}