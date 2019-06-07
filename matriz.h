#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H
typedef struct {
  int lin_inicio;
  int lin_fim;
  int col_inicio;
  int col_fim;
} bloco_t;

typedef struct {
  int **matriz;
  bloco_t *bloco;
} matriz_bloco_t;
#endif

int gerar_matriz(int **matriz, int linha, int coluna,int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);

// submatriz
int gerar_submatriz (int **mat_origem, int **submatriz, bloco_t *bloco);
//int imprimir_submatriz (matriz_bloco_t *submatriz);
matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int cortes);
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz,int cortes);
//int imprimir_bloco (matriz_bloco_t *submatriz);
matriz_bloco_t **constroi_submatriz (int mat_lin, int mat_col, int divisor);

