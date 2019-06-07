#include "toolsv2.h"
#include <time.h>
#include <sys/time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FERRAMENTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
double wtime() {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec + (double) t.tv_usec / 1000000;
}

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  char **split(const char *str, char sep, int nro_line) {
        int conta_palavras;
        unsigned int start = 0, stop;
        char **retStr;

    //printf("SPLIT: \n\tConteúdo da linha (%s)\n\tSeparador (%c)\n\tNro de caracteres na Linha(%d)\n", str, sep, nro_line);

        retStr = (char **) malloc (nro_line*sizeof(char *));
        conta_palavras = 0;
    //printf("\t\t\t\t\tstr[stop] = %p %d\n", str, stop);
        for (stop = 0; str[stop]; stop++) {
    //for (stop = 0; stop < (nro_line-1); stop++) {
                //printf("**{(%d=(%s)[(%d)]=(%d))}**\n", stop, str, str[stop],nro_line);
                if (str[stop] == sep) {
        //printf("conta_palavras (%d) nro_line (%d) stop (%d)\n", conta_palavras, nro_line, stop);
                        if ( conta_palavras < nro_line ) {
          //printf("%d %d\n", conta_palavras, nro_line);
                                retStr[conta_palavras] = (char *) malloc (((stop - start)+1)*sizeof(char));
                                if (retStr == NULL)
                                    printf("ERROR: Out of memory\n");
                                strncpy (retStr[conta_palavras], str + start, stop - start);
                                memcpy (retStr[conta_palavras], str + start, stop - start);
                                retStr[conta_palavras][(stop-start)] = '\0';
                                //printf("[%s/%d]\n", retStr[conta_palavras], conta_palavras);
                                conta_palavras++;
                                start = stop + 1;
                        } else {
                                printf("Error: Ultrapassou o número máximo de palavras (%d)\n",conta_palavras);
                                exit (0);
                        }
                }
        }

        //retStr[conta_palavras] = (char *) malloc ((nro_letras)*sizeof(char));
        if (retStr == NULL)
            printf("ERROR: Out of memory\n");
        strncpy (retStr[conta_palavras], str + start, stop - start);
        //printf("[%s/%d]\n", retStr[conta_palavras], conta_palavras);
        return (retStr);
  }

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int fileout_matriz (int **matriz, int linha, int coluna, FILE *infile){
        fprintf(infile,"#Linha#Coluna#\n");
        fprintf(infile,"%d#%d#\n", linha, coluna);
        for (int i=0; i < linha; i++) {
                for (int j=0; j < coluna; j++){
                        fprintf(infile,"%d,", matriz[i][j]);
                }
                fprintf(infile,"\n");
        }
        return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int extrai_parametros_matriz ( FILE *const fin, int* linha,
        int *coluna, int **vet_line, int *nr_line ) {
                char *getLine = NULL;
                char **strSplit = NULL;

                *nr_line = 1;
                *vet_line = (int *) malloc ((*nr_line+2)*sizeof(int));

                *nr_line = conta_line_file (fin, 2, *nr_line, *vet_line);
                free (*vet_line);
                *vet_line = (int *) malloc ((*nr_line+2)*sizeof(int));

                *nr_line = contabiliza_file (fin, *vet_line);
                getLine = get_line_file (fin, 2, *nr_line, *vet_line);
                strSplit = split(getLine, '#', *nr_line);
                *linha = atoi(strSplit[0]);
                *coluna = atoi(strSplit[1]);
                return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int contabiliza_file( FILE *const fin, int* line_length ) {
        int c, count, line = 0, vet_ind = 0;

        count = 0;
        line = 0;
        fseek( fin, 0, SEEK_SET );
        for( ;; ) {
                c = fgetc( fin );
                //printf ("(%d):%c\n",count, c);
                if ( c == '\n' ) {
                        //printf ("Line Length = %d\n",count);
                        line_length[vet_ind] = count;
                        vet_ind++;
                        count = 0;
                        line++;
// if ((vet_ind % 10) == 0) {
                        //      printf("vet_ind %d\n", vet_ind);
                        //      line_length = (int *) realloc(line_length, (vet_ind+10)*sizeof(int));
                        // }
                }
                if( c == EOF )
                break;
                ++count;
        }
        return line;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int conta_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line ) {
        char *getLine = NULL;
        char **strSplit = NULL;
        int c, count;

        fseek( fin, 15, SEEK_SET );
        count = 0;
        getLine = (char *) malloc (10*sizeof(char));
        for( ;; ) {
                c = fgetc( fin );
                //printf ("(%d):%c\n",count, c);
                getLine[count] = c;
                if ( c == '\n' ) {
                        getLine[count] = '\x0';
                        //printf ("Line Length = [%d] (%s)\n",count, getLine);
                        break;
                }
                count++;
        }

        //printf("{[%c/%c]}\n", getLine[0], getLine[2]);
        strSplit = split(getLine, '#', count);
        //printf("(%s)(%s)\n", strSplit[0],strSplit[1]);
        return atoi(strSplit[0]);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int nr_line_file ( FILE *const fin, int *vet_line ) {
        int nr_line;

        nr_line = 1;
        vet_line = (int *) malloc ((nr_line+2)*sizeof(int));
        nr_line = conta_line_file (fin, 2, nr_line, vet_line);
        free (vet_line);
        vet_line = (int *) malloc ((nr_line+2)*sizeof(int));
        return nr_line;
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
char *get_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line ) {
        int c, count, vet_ind = 0, posicao = 0;
        char *retStr = NULL;

        //printf("[%d/%d/%d]\n", nro_line, get_line, vet_line[get_line-2]);
        count = 0;
        for (int i=0; i < (get_line-1); i++) {
                //printf("(%d)=%d{%d}\n", i, vet_line[i], posicao);
                posicao += vet_line[i];
        }

        fseek( fin, posicao+1, SEEK_SET );
        //printf("posicao[%d/%d/%d/%d]\n", posicao, nro_line, get_line,vet_line[get_line-1]);
        retStr = (char *) malloc (vet_line[get_line-1] * sizeof(char));
        //printf("posicao[%d/%d/%d/%d]\n", posicao, nro_line, get_line,vet_line[get_line-1]);
        //exit (1);
        for( ;; ) {
                c = fgetc( fin );
                //printf ("(%d):%c\n",count, c);
                retStr[count] = c;
                if ( c == '\n' ) {
                        retStr[count] = '\x0';
                        //printf ("Line Length = %d (%s)\n",count, retStr);
                        count = -1;
                        vet_ind++;
                        //printf("{[%s]}\n", retStr);
                        return (retStr);
                }
                if( c == EOF )
                        break;
                ++count;
        }
        return NULL;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int filein_matriz (int **matriz, int linha, int coluna, FILE *file, int *vet_ind, int nr_line){
        char *getLine = NULL;
        char **strSplit= NULL;


        //printf ("Matriz (linha/coluna) = %d/%d\n", linha, coluna);
        //printf("{##########################}\n");

        if (linha != (nr_line -2)) {
                printf("ERRO: Numero de linha da matriz nao esta correta!\n");
                exit (1);
        }
 for (int i=0; i < linha; i++) {
                //printf("PAREI EM tools = linha 203: (%d)(%d)(%d)\n", i, nr_line, vet_ind[i+3]);
                getLine = get_line_file (file, i+3, nr_line, vet_ind);
                //getLine = get_line_filev1 (file, i+3, vet_ind[i+2]);
                strSplit = split(getLine, ',', vet_ind[i+2]);
                //printf("{%s}\n", getLine);
                //printf("(%d){%d}{%d}{%d}\n", i, atoi(strSplit[0]),atoi(strSplit[1]),atoi(strSplit[2]));
                for (int j=0; j < coluna; j++){
                        //printf("(i[%d],j[%d])%d\n", i , j, atoi(strSplit[j]));
                        matriz[i][j] = atoi(strSplit[j]);
                }
        }
        return 0;
}



