# GNU Makefile

CC = mpicc	
CCFLAGS = -Wall -O3 #-llikwid #-funroll-all-loops
LDFLAGS = #-pg
TARGET = main_matriz gera_matriz2 help
EXE = ./gera_matriz2

all: $(TARGET)

%.o: %.c
		$(CC) $(CCFLAGS) -c $<

%: %.o
		$(CC) $(LDFLAGS) $^ -o $@

main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o matriz-operacoes-mpi.o
		$(CC) $(CCFLAGS) matriz-operacoes-mpi.o matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
		$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

help:
		@echo "\nMultiplicação de matrizes sequencial, sequencial em blocos e paralela distribuída MPI convencional e em blocos.\n"
		@echo "\nPara executar a aplicação execute o script exec.sh no terminal através do comando: bash exec.sh\n\nEste script está configurado para executar 5 vezes cada caso de teste\nPara executar com tamanho de entrada diferente basta alterar no script os parâmetros logo após os executáveis\n\nExemplo: ./gera_matriz2 N N e os parâmetros após ./main_matriz NxN-mat.map NxN-mat.map utilizando em ambos os mesmos arquivos de entrada\n"
		@echo "\n####### Exemplo de Execução isolada #######\nApós gerar os arquivos manualmente através da aplicação ./gera_matriz2 128 128"
		@echo "\nmpirun -np 2 ./main_matriz 128x128-mat.map 128x128-mat1.map\n"

clean:
		rm -f *.o *~ $(TARGET)

