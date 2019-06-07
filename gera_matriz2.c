#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes.h"


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char **argv) {
        int **mat0 = NULL;
  	    int **mat1 = NULL;
        FILE *fmat0;
        FILE *fmat1;
        int linha, coluna;
        char filename [100];
        int *vet_line = NULL;
        int nr_line;

        if (argc != 3){
                //printf("\n\naqui\n\n");
                printf ("ERRO: Numero de parametros %s <nr_linhas> <nr_colunas>", argv[0]);
                //printf("\n\naqui\n\n");
                exit (1);
        }

        linha =  atoi(argv[1]);
        coluna = atoi(argv[2]);

        sprintf (filename, "%dx%d-mat.map", linha, coluna);

        fmat0 = fopen(filename,"w");
            if (fmat0 == NULL) {
                printf("Error: Na abertura dos arquivos.");
                exit(1);
        }

        mat0 = alocar_matriz(linha,coluna);
        gerar_matriz(mat0, linha, coluna,-9999);
        if (mat0 == NULL) {
                printf("ERROR: Out of memory\n");
        }

        printf("\t\t**** PRINT mat_c NxM(%d,%d) **** \n", linha, coluna);
        //imprimir_matriz(mat0, linha, coluna);
        fileout_matriz(mat0, linha, coluna, fmat0);

        liberar_matriz(mat0, linha, coluna);
        //printf("#####\n Arquivo com a matriz gerada (%dx%d-mat.map).\n#####\n", linha, coluna);

        fclose(fmat0);

        fmat1 = fopen(filename,"r");
        if (fmat1 == NULL) {
                printf("Error: Na abertura dos arquivos.");
                exit(1);
        }
        extrai_parametros_matriz(fmat1, &linha, &coluna, &vet_line, &nr_line);
        mat1 = alocar_matriz(linha, coluna);
        filein_matriz(mat1, linha, coluna, fmat1, vet_line, nr_line);
        //imprimir_matriz(mat1, linha, coluna);
        liberar_matriz(mat1, linha, coluna);
        fclose(fmat1);

        printf("##### Arquivo %dx%d-mat.map: VERIFICADO! #####\n", linha, coluna);
  return 0;
}




// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//#include <time.h>
/*int main(int argc, char **argv) {
        int **mat0 = NULL;
  	    int **mat1 = NULL;
        FILE *fmat0;
        FILE *fmat1;
        int linha, coluna;
        char filename [100];
        int *vet_line = NULL;
        int nr_line;

        if (argc != 3){
                //printf("\n\naqui\n\n");
                printf ("ERRO: Numero de parametros %s <nr_linhas> <nr_colunas>", argv[0]);
                //printf("\n\naqui\n\n");
                exit (1);
        }

        linha =  atoi(argv[1]);
        coluna = atoi(argv[2]);
        
        srand( (unsigned)time(NULL) );
        int version = rand() % 10;

        sprintf (filename, "matriz%d.txt", version);

        fmat0 = fopen(filename,"w");
            if (fmat0 == NULL) {
                printf("Error: Na abertura dos arquivos.");
                exit(1);
        }

        mat0 = alocar_matriz(linha,coluna);
        gerar_matriz(mat0, linha, coluna,-9999);
        if (mat0 == NULL) {
                printf("ERROR: Out of memory\n");
        }

        //printf("\t\t**** PRINT mat_c NxM(%d,%d) **** \n", linha, coluna);
        //imprimir_matriz(mat0, linha, coluna);
        fileout_matriz(mat0, linha, coluna, fmat0);

        liberar_matriz(mat0, linha, coluna);
        //printf("#####\n Arquivo com a matriz gerada (%dx%d-mat.map).\n#####\n", linha, coluna);

        fclose(fmat0);

        fmat1 = fopen(filename,"r");
        if (fmat1 == NULL) {
                printf("Error: Na abertura dos arquivos.");
                exit(1);
        }
        extrai_parametros_matriz(fmat1, &linha, &coluna, &vet_line, &nr_line);
        mat1 = alocar_matriz(linha, coluna);
        filein_matriz(mat1, linha, coluna, fmat1, vet_line, nr_line);
        //imprimir_matriz(mat1, linha, coluna);
        liberar_matriz(mat1, linha, coluna);
        fclose(fmat1);
        
        printf("##### Arquivo matriz%d.txt: VERIFICADO! #####\n",version);
  return 0;
}*/

