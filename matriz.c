 #include "matriz.h"
#include <time.h>
#include <sys/time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int gerar_matriz(int **matriz, int linha, int coluna, int valor){
    srand( (unsigned)time(NULL) );  

    if(matriz == NULL){
    printf("\nMatriz nao alocada!!!\n");
    exit(1);    
    }
     
    for(int i = 0; i < linha; ++i){
        for(int j = 0; j < coluna; ++j){
            if(valor == -9999){           
            matriz[i][j] = rand() % 10;
            }
            if(valor == -8888){
            matriz[i][j] = i + j;
            }
            if(valor == -7777){
            matriz[i][j] = linha - i;            
            }
            if(valor == 0){
            matriz[i][j] = 0;
            }
        }
  }
return 0;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int zerar_matriz (int **matriz, int linha, int coluna){
    if(matriz == NULL){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);    
    }
        for(int i = 0; i < linha; ++i){
            for(int j = 0; j < coluna; ++j){
                matriz[i][j] = 0;
            }
        }
return 0;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int imprimir_matriz (int **matriz, int linha, int coluna){
        if(matriz == NULL){
            printf("\nMatriz nao alocada!!!\n");
            exit(1);    
        }
     
        for (int j =0; j < coluna; j++)
            printf("\t(%d)", j);
        	printf("\n");
        for (int i=0; i < linha; i++) {
                printf("(%d)", i);
          for (int j=0; j < coluna; j++){
                        printf("\t%d", matriz[i][j]);
                }
                printf("\n");
        }
        return 0;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna){
        if(matriza == NULL){
            printf("\nMatriz nao alocada!!!\n");
            exit(1);    
        }
        if(matrizb == NULL){
            printf("\nMatriz nao alocada!!!\n");
            exit(1);    
        }
     
     

        for (int j =0; j < coluna; j++)
            for (int i=0; i < linha; i++) {
                 for (int j=0; j < coluna; j++){
                        if (matriza[i][j] != matrizb[i][j]) {
                                printf("O elemento [%d,%d] é diferente nas matrizes analisadas!", i,j);
                                return 1;
                        }
                }

        }
        printf("VERIFICADO: Matrizes identicas\n");
        return 0;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **liberar_matriz (int **matriz, int linha, int coluna) {
        for(int i = 0; i < linha; i++){
            free(matriz[i]);
        }  
        return NULL;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **alocar_matriz (int linha, int coluna) {
  
  	int **A = NULL;
    A = (int **) malloc(linha*sizeof(int *));
    
  	for (int i =0; i < linha; i++) {
            A[i] = (int *) malloc(sizeof(int)*coluna);
  	}
    return A;
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//int imprimir_submatriz (matriz_bloco_t *submatriz){
//        #TODO
//        return 0;
//}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//int imprimir_bloco (matriz_bloco_t *submatriz) {
        
//        return 0;
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//}

// orientacao, 0 corte horizontal, 1 para corte vertical
int gerar_submatriz (int **mat_origem, int **submatriz, bloco_t *bloco) {
  
	int aux1 = 0;
	int aux2 = 0;

	for (int i=bloco->lin_inicio;i<bloco->lin_fim;i++)
		{
		for (int j=bloco->col_inicio;j<bloco->col_fim;j++)
			{
				submatriz[aux2][aux1] = mat_origem[i][j];
				aux1 += 1;
			}
			aux2 += 1;
			aux1 = 0;
	}
  	return 0;
}

matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int cortes) {
	
	matriz_bloco_t **subM = malloc( cortes * sizeof(matriz_bloco_t *));

	int lim = orientacao == 1? mat_col : mat_lin;
    int tam = 1;
	int resto = 0;
	int useResto = 0;
	int final = 0;

	while ((tam * cortes) <= lim) {
		tam += 1;
	}

	tam -= 1;

	if ( tam * cortes < lim){
		resto = lim - ( tam * cortes );
	}

	
	if (tam == 0) {
		printf("Erro.\n");
		exit(1);
	}else{
		for(int i=0; i<cortes; i++){


			if ( resto != 0 ){
				useResto = 1;
				resto -= 1;
			}else{
				useResto = 0;
			}

			bloco_t *baux = malloc(sizeof(bloco_t));
			baux->col_inicio = 0;
			baux->col_fim = mat_col;
			baux->lin_inicio = 0;
			baux->lin_fim = mat_lin;
			if (orientacao == 1){
				baux->col_inicio = final;
				baux->col_fim = final + tam + useResto;
			}else{
				baux->lin_inicio = final;
				baux->lin_fim = final + tam + useResto;
			}
			final += tam + useResto;

			int **mx;
			if (orientacao ==1){
				mx = alocar_matriz(mat_lin, tam + useResto);
				zerar_matriz(mx, mat_lin, tam + useResto);
			}else{
				mx = alocar_matriz(tam + useResto, mat_col);
				zerar_matriz(mx, tam + useResto, mat_col);
			}
			
			gerar_submatriz(matriz,mx,baux);
			baux->col_inicio = 0;
			baux->col_fim = mat_col;
			baux->lin_inicio = 0;
			baux->lin_fim = mat_lin;
			if (orientacao ==1){
				baux->col_fim = tam + useResto;
			}else{
				baux->lin_fim = tam + useResto;
			}
			
			
			subM[i] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
			subM[i]->bloco = baux;
			subM[i]->matriz = mx;
		}
	}

  return subM;
    }


matriz_bloco_t **constroi_submatriz(int mat_lin, int mat_col, int divisor) {

	matriz_bloco_t **sm = malloc( divisor * sizeof(matriz_bloco_t *));

	for(int i=0;i<divisor;i++){
		bloco_t *bx = malloc(sizeof(bloco_t));
		bx->col_inicio = 0;
		bx->col_fim = mat_col;
		bx->lin_inicio = 0;
		bx->lin_fim = mat_lin;
		
		int **maux = alocar_matriz(mat_lin,mat_col);
		zerar_matriz(maux,mat_lin,mat_col);
		sm[i] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
		sm[i]->bloco = bx;
		sm[i]->matriz = maux;
	}

	return sm;
}

matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz, int cortes) {

  for(int i=0;i<cortes;i++){
	  liberar_matriz(submatriz[i]->matriz,submatriz[i]->bloco->lin_fim,submatriz[i]->bloco->col_fim);
	  free(submatriz[i]->bloco);
	  free(submatriz[i]);
  }
  
  free(submatriz);

  return NULL;
}
