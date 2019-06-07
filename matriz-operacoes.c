#include "matriz-operacoes.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int A) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }	
    /*testar*/
    if(N != M || N != L || M !=L){
        printf("\nMatrizes imcompativeis!\n");
        exit(1);
    }
	for(int i = 0; i < N; i++)
		for(int j=0; j < M; j++)
		mat_c[i][j] = mat_a[i][j] + mat_b[i][j];
		
  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int A) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }	
    /*testar*/
    if(N != M || N != L || M !=L){
        printf("\nMatrizes imcompativeis!\n");
        exit(1);
    }
	for(int j = 0; j < M; j++){
		for(int i = 0; i < N; i++){
		mat_c[j][i] = mat_a[j][i] + mat_b[j][i];		
		}	
	}
  return 0;
}

int multiplicarIJK2 (int **mat_a, int **mat_b, int **mat_c, int LA, int CA, int CB, int LB){
  
    for (int i = 0 ; i < LA; i++ )
        for (int j = 0; j < CB; j++ ){
          mat_c[i][j] = 0;
              for (int k = 0; k < CA; k++ )
                 mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
        }

  return 0;
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarIJK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++){
			mat_c[i][j] = 0;
			for(int k = 0; k < L; k++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			}
	
        return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarIKJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
	/*testar*/		
		for(int i = 0; i < N; i++)
			for(int k = 0; k < L; k++){
				//mat_c[i][j] = 0;
				for(int j = 0; j < M; j++)			
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			
			}
	
        return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarKIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }    
  /*testar*/	
	for(int k = 0; k < L; k++){	
		for(int i = 0; i < N; i++){
			//mat_c[i][j] = 0;
			for(int j = 0; j < M; j++){				
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			}   
		}
	}
  return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarJIK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
	/*testar*/	
	for(int j = 0; j < M; j++){	
			for(int i = 0; i < N; i++){
				for(int k = 0; k < L; k++){	
					mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			}
		}
	}
  return 0;
}



int multiplicarJKI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
	/*testar*/	
	for(int j = 0; j < M; j++){	
		for(int k = 0; k < L; k++){
			for(int i = 0; i < N; i++){	
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			}
		}
	}
  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarKJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
	/*testar*/
	for(int k = 0; k < L; k++){	
		for(int j = 0; j < M; j++){	
			for(int i = 0; i < N; i++){
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];			
			}
		}
	}
  return 0;
}
void multiplicaBloco(int size, int n, int **A, int **B, int **C, int TILE){
	int i, j, k, x, y, z;

    if(size % TILE != 0){
       TILE = 4;
    }
    if(size == 10){
        TILE = 2;
    }

	for(i = 0; i < size; i += TILE)
        for(k = 0; k < size; k += TILE)	    
            for(j = 0; j < size; j += TILE)
	            for(x = i; x < i + TILE; x++)		            
                    for(y = j; y < j + TILE; y++)
                        for(z = k; z < k + TILE; z++)		                
		                    C[x][y] += A[x][z] * B[z][y];
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
   multiplicarIJK2(mat_suba->matriz,mat_subb->matriz,mat_subc->matriz,mat_suba->bloco->lin_fim,mat_suba->bloco->col_fim,mat_subb->bloco->col_fim,mat_subb->bloco->lin_fim);
return 0;

}

