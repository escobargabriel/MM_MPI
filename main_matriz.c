/*Matrizes Globais*/
int **mat_a;
int **mat_b;
int **mat_c;
int **mat_cBloco;
int **mat_cmpi; 
int *A, *B, *C;
int *A1, *B1, *C1;
    
#define MPI_MASTER 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include <mpi.h>
#include "matriz-operacoes-mpi.h"
#include "matriz-operacoes.h"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]){

	int MPI_rank, MPI_size;

	MPI_Init(&argc, &argv);
    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &MPI_size);

    /* Get the rank of the process */
    MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);


	FILE *fmat_a, *fmat_b, *fmat_c, *fmat_cBloco, *fmatMPI_c, *fmatMPI_cBloco;
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb;
	int TILE = 2;
	
	

	float mediaSeq = 0.0, mediaMPI = 0.0, mediaSeqBloco = 0.0, mediaMPIBlock = 0.0;
	double start_time, end_time; //total = 0.0;

	mat_a = NULL;
    mat_b = NULL;
    mat_c = NULL;
    mat_cBloco = NULL;
    mat_cmpi = NULL; 
    mat_cmpiBloco = NULL; 
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"r");
	
	
	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}
	
	if ((fmat_a == NULL) || (fmat_b == NULL)) {
		printf("Error: Na abertura dos arquivos.\n");
		exit(1);
	}

  	// matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, La);
	filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

	// matriz_b Lb (linha) x M (coluna)
	extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
	mat_b = alocar_matriz(Lb, M);
	filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);


		/*VERSAO SEQUENCIAL*/

	if(MPI_rank == MPI_MASTER){
   		mat_c = alocar_matriz(N, M);
   		zerar_matriz(mat_c, N, M);
       	start_time = wtime();
    	multiplicarIJK(mat_a,mat_b,mat_c, N, N, N);
    	end_time = wtime();
       	mediaSeq += (end_time - start_time);     
 		fmat_c= fopen("outIJK.map-result","w");
		fileout_matriz(mat_c, N, M, fmat_c);
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%


	/*Versao sequencial em blocos*/
	if(MPI_rank == MPI_MASTER){
   		mat_cBloco = alocar_matriz(N, M);
   		zerar_matriz(mat_cBloco, N, M);
       	start_time = wtime();
       	multiplicaBloco(N, 0, mat_a, mat_b,  mat_cBloco, TILE);
	   	end_time = wtime();
    	mediaSeqBloco += (end_time - start_time);     
    	fmat_cBloco= fopen("outIJK.map-result","w");
		fileout_matriz(mat_cBloco, N, M, fmat_cBloco);
		comparar_matriz (mat_c, mat_cBloco, N, M);
	}
	
	/* versao paralela com MPI  */

	int size = N;

	size = size % MPI_size == 0 ? size : size + (MPI_size - size % MPI_size);

	int chunk_lines_A = (int) (size / MPI_size);


	if(MPI_rank == MPI_MASTER){
		A = calloc(size * size, sizeof(int));
		B = calloc(size * size, sizeof(int));
		C = calloc(size * size, sizeof(int));

		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
					A[i * size + j] = mat_a[i][j];
					B[i * size + j] = mat_b[i][j];
				
			}
		}
	}else{
		A = malloc(chunk_lines_A * size * sizeof(int));
		B = malloc(size * size * sizeof(int));
		C = calloc(chunk_lines_A * size, sizeof(int));
	}
	
	mat_cmpi = alocar_matriz(N, M);		
	zerar_matriz(mat_cmpi, N, M);
	start_time = wtime();
	multiplicarMPI (A, B, C, MPI_size, MPI_rank, chunk_lines_A, size);		
	end_time = wtime();
	mediaMPI += (end_time - start_time);
		
	
	if(MPI_rank == MPI_MASTER){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				mat_cmpi[i][j] = C[i * size + j];
			}
		}

		fmatMPI_c = fopen("outMPI.map-result","w");
		fileout_matriz(mat_cmpi, N, M, fmatMPI_c);
		comparar_matriz (mat_c, mat_cmpi, N, M);
		//zerar_matriz(mat_cmpi, N, M);
	}
	/*       Fim MPI convencional   */


	/*     Execuçao MPI em blocos      */
	if(MPI_rank == MPI_MASTER){
		A1 = calloc(size * size, sizeof(int));
		B1 = calloc(size * size, sizeof(int));
		C1 = calloc(size * size, sizeof(int));

		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
					A1[i * size + j] = mat_a[i][j];
					B1[i * size + j] = mat_b[i][j];
				
			}
		}
	}else{
		A1 = malloc(chunk_lines_A * size * sizeof(int));
		B1 = malloc(size * size * sizeof(int));
		C1 = calloc(chunk_lines_A * size, sizeof(int));
	}
	
	

	mat_cmpiBloco = alocar_matriz(N, M);
	zerar_matriz(mat_cmpiBloco, N, M);
	start_time = wtime();
	multiplicaBlocoMPI (A1,B1,C1, TILE, MPI_size, MPI_rank, chunk_lines_A, size, N);		
	end_time = wtime();
	mediaMPIBlock += (end_time - start_time);
	
	if(MPI_rank == MPI_MASTER){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				mat_cmpiBloco[i][j] = C1[i * size + j];
			}
		}				
		fmatMPI_cBloco = fopen("outMPIBloco.map-result","w");
		fileout_matriz(mat_cmpiBloco, N, M, fmatMPI_cBloco);
		comparar_matriz (mat_c, mat_cmpiBloco, N, M);
		zerar_matriz(mat_cmpiBloco, N, M);
	}
	/*Fim MPI em blocos*/

    if(MPI_rank == MPI_MASTER){
		float speedupMPI = mediaSeq / mediaMPI;
		float speedupBlock = mediaSeqBloco / mediaMPIBlock;
   	
    	printf("\n----------------------------------------------------------------------------\n");
    	printf("\n-   Sequencial:                                   %f                 -", mediaSeq);
    	printf("\n-   Sequencial em blocos:                         %f                 -", mediaSeqBloco);
    	printf("\n----------------------------------------------------------------------------\n");
    	printf("\n-   Paralelos:                                                             -");
    	printf("\n-   MPI:                                          %f                 -", mediaMPI);
    	printf("\n-   Media MPI Blocos:                             %f                 -", mediaMPIBlock);    
    	printf("\n-   Speedup:                                      %f                 -", speedupMPI);
    	printf("\n-   Speedup blocos:                               %f                 -", speedupBlock);
    	printf("\n----------------------------------------------------------------------------\n");
 	
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// LIBERAR MEMÓRIA
		liberar_matriz(mat_a,N,La);
		liberar_matriz(mat_b,Lb,M);
		liberar_matriz(mat_c,N,N);
		liberar_matriz(mat_cBloco,N,N);
		liberar_matriz(mat_cmpi,N,M);
	
		fclose(fmat_a);
		fclose(fmat_b);
    	
    	free(A);
		free(B);	
		free(C);

    	free(A1);
		free(B1);	
		free(C1);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
    }

MPI_Finalize();	    
return 0;
}
