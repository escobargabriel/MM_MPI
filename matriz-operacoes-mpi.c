#include "matriz-operacoes-mpi.h"

void multiplicarMPI(int *A, int *B, int *C, int N, int L, int M, int argc, char *argv[], int MPI_size, int MPI_rank, int chunk_lines_A, int size) {

	int i, j, k;
	//for(int aux = 0; aux < 5; aux++){
		
		
		MPI_Scatter(A, chunk_lines_A * size, MPI_INT, A, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

		MPI_Bcast(B, size * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

		/* Regular multiply inside the tiles */
		for(i = 0; i < chunk_lines_A; i++)
			for(j = 0; j < size; j++)
				for(k = 0; k < size; k++)
					C[i * size + j] += A[i * size + k] * B[k * size + j];

		MPI_Gather(C, chunk_lines_A * size, MPI_INT, C, chunk_lines_A * size, MPI_INT, MPI_MASTER, MPI_COMM_WORLD);

	//}
	
    /*if(MPI_rank == MPI_MASTER){
	

		int is_ok = 1;
		for(i = 0; i < size; i++)
			for(j = 0; j < size; j++)
				if(C[i * size + j] != (double) size){
					is_ok = 0;
					i = size;
					j = size;
				}
		if(is_ok)
			printf("result is ok\n");
		else
			printf("result is wrong\n");
	}*/


}

void multiplicaBlocoOMP(int size, int n, int **A, int **B, int **C, int TILE){
	int i, j, k, x, y, z;
//#pragma omp parallel for schedule(guided) private(i,j,k,x,y,z) shared(A,B,C)
	for(i = 0; i < size; i += TILE){
	    for(j = 0; j < size; j += TILE){
	        for(k = 0; k < size; k += TILE){
	            for(x = i; x < i + TILE; x++){
		            for(y = j; y < j + TILE; y++){
		                for(z = k; z < k + TILE; z++){
		                    C[x][y] += A[x][z] * B[z][y];
                        }
                    }
                }
            }
        }
    }
}