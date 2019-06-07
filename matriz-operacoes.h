#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matriz.h"


int somarIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int A);
int somarJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int A);

int multiplicarIJK2 (int **mat_a, int **mat_b, int **mat_c, int LA, int CA, int CB, int LB);
int multiplicarIJK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
int multiplicarIKJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);

int multiplicarKIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
int multiplicarJIK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);

int multiplicarJKI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
int multiplicarKJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);

int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);


void multiplicaBloco(int size, int n, int **A, int **B, int **C, int TILE);
