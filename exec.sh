#!/bin/bash

#Para executar com dimensões diferentes é necessário alterar ou adicionar
#os parâmetros do executável ./gera_matriz2 N N
#É necessário alterar ou adicionar também os parâmetros do executável ./main_matriz NxN-mat.map NxN-mat.map
#O comando Resultados/resultado-NumeroProcessos-N.txt corresponde ao diretório (Resultados)
#E o arquivo que será salvo neste diretório com os resultados

#Limpando executaveis do diretorio
echo "---------------------------------------------------------------------"
echo "Limpando executáveis"
make clean
echo "---------------------------------------------------------------------"
#Compilado executaveis
echo "---------------------------------------------------------------------"
echo "Compilando arquivos"
make
echo "---------------------------------------------------------------------" 

#criando diretorio para salvar resultados
echo "---------------------------------------------------------------------"
echo "Criando diretório para armazenar resultados"
mkdir Resultados
echo "---------------------------------------------------------------------"

#Gerando arquivos de entrada
echo "---------------------------------------------------------------------"
echo "Gerando arquivos de entrada"
./gera_matriz2 512 512

./gera_matriz2 1000 1000
echo "---------------------------------------------------------------------"

#Executando com entrada 512 e 2 processos

echo "---------------------------------------------------------------------"
echo "Iniciando execução 512x512 com 2 processos"
echo "Aguarde"
echo "---------------------------------------------------------------------"
#definindo numero de repeticoes de cada caso
for i in `seq 1 5`
#executando
do
	mpirun -np 2 main_matriz 512x512-mat.map 512x512-mat.map >> Resultados/resultado-2Processos-512.txt
done
echo "---------------------------------------------------------------------"
echo "Fim da execução"
echo "---------------------------------------------------------------------"
echo "Os resultados estão no arquivo resultado-2Processos-512.txt"
echo "---------------------------------------------------------------------"

#Executando com entrada 512 e 4 processos
echo "---------------------------------------------------------------------"
echo "Iniciando execução 512x512 com 4 processos"
echo "Aguarde"
echo "---------------------------------------------------------------------"
#definindo numero de repeticoes de cada caso
for i in `seq 1 5`
#executando
do
	mpirun -np 4 main_matriz 512x512-mat.map 512x512-mat.map >> Resultados/resultado-4Processos-512.txt
done
echo "---------------------------------------------------------------------"
echo "Fim da execução"
echo "---------------------------------------------------------------------"
echo "Os resultados estão no arquivo resultado-4Processos-512.txt"
echo "---------------------------------------------------------------------"

echo "---------------------------------------------------------------------"
echo "Iniciando execução 1000x1000 com 2 processos"
echo "Aguarde"
echo "---------------------------------------------------------------------"
#definindo numero de repeticoes de cada caso
for i in `seq 1 5`
#executando
do
	mpirun -np 2 main_matriz 1000x1000-mat.map 1000x1000-mat.map >> Resultados/resultado-2Processos-1000.txt
done
echo "---------------------------------------------------------------------"
echo "Fim da execução"
echo "---------------------------------------------------------------------"
echo "Os resultados estão no arquivo resultado-2Processos-1000.txt"
echo "---------------------------------------------------------------------"
echo "---------------------------------------------------------------------"
echo "Iniciando execução 1000x1000 com 4 processos"
echo "Aguarde"
echo "---------------------------------------------------------------------"
#definindo numero de repeticoes de cada caso
for i in `seq 1 5`
#executando
do
	mpirun -np 4 main_matriz 1000x1000-mat.map 1000x1000-mat.map >> Resultados/resultado-4Processos-1000.txt
done
echo "---------------------------------------------------------------------"
echo "Fim da execução"
echo "---------------------------------------------------------------------"
echo "Os resultados estão no arquivo resultado-4Processos-1000.txt"
echo "---------------------------------------------------------------------"
