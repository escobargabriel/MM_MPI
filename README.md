# Descrição

Este programa em sua execução realiza operacoes basicas e a multiplicao de estruturas matriciais de quatro diferentes maneiras: convencional, em blocos, multi-thread convencional e multi-thread em blocos. 

Estão presentes nos códigos funções para alocação de memória, geração e preenchimento de todas as posições das matrizes, liberação da memória, etc.


## Compilação

__IMPORTANTE__

__Este código e demais arquivos auxiliares foram desenvolvidos e executados em sistema operacional linux__

Para compilar os códigos é necessário executar o arquivo "Makefile", neste arquivo estão todas as flags e comandos necessários para a compilação da aplicação e bibliotecas auxiliares. Para executar este arquivo é necessário navegar através do terminal no sistema operacional linux até o diretório onde se encontram os arquivos ".c", ".h", além do "Makefile" (exemplo: $ cd /home/MM_MPI).

 Estando dentro do diretório correto basta executar o *Makefile*.

> $ make

Após execução deste comando os códigos seram compilados e gerados os executáveis e binarios.

	
## Execução
O arquivo *Makefile* é responsável pela compilação e geração dos executáveis da aplicação.

Após compilação para gerar os arquivos de entrada basta executar o comando abaixo:

> $./geraMatriz2 128 128

O primeiro parâmetro corresponde ao executável gerado na compilação, ja o segundo e o terceiro parâmetros correspondem as dimensões da matriz N x N (128 x 128).

São necessários dois arquivos de entrada para execução da aplicação principal *main_matriz.c*.

O arquivo gerado pela aplicação *geraMatriz2.c* possui por padrão o nome 128x128-mat.map, onde 128x128 são as dimensões NxN.

Para executar a aplicação principal é preciso gerar um arquivo com as dimensões NxN (matriz quadradas), renomear o arquivo manualmente, e gerar novo arquivo com as mesmas dimensões do primeiro para garantir a compatibilidade dos arquivos de entrada. Outra possibilidade é gerar um único arquivo de entrada com uma matriz quadrada e utilizar o mesmo nos dois parâmetros de arquivos de entrada.


### Execução Isolada
Para executar localmente em ambiente de memória compartilhada basta navegar até o diretório onde os arquivos estão presentes e executar o comando abaixo

> $ mpirun -np 4 main_matriz 128x128-mat.map 128x128-mat1.map 

> O primeiro parâmetro para execução é mpirun, logo após -np 4 (número de processos = 4) seguido do executável e seus respectivos parâmetros (main_matriz NxN-mat.map NxN-mat.map)

### Execução distribuída
O MPI apesar de funcionar em ambientes de memória compartilhada é voltado para ambientes de memória distribuída. Para executar de maneira distribuída são necessários alguns cuidados.

Os executáveis e demais códigos devem estar em diretórios com os mesmos caminhos em todos os *hosts* para que todos sejam executados corretamente.

É necessário passar como parâmetro a lista de *hosts* e a interface de rede pela qual a comunicação irá acontecer.

Para executar a aplicação basta executar no terminal linux o comando abaixo:

> mpirun --mca btl ^openib --mca btl_tcp_if_include ens3 -np 4 --map-by node --hostfile /home/aluno10/mpi/hostfile /home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map

> o primeiro parâmetro é mpirun seguido pelos parâmetros de rede (--mca btl ^openib --mca btl_tcp_if_include ens3), modo de mapeamento dos processos (--map-by node), arquivo de hosts (--hostfile /home/aluno10/mpi/hostfile). Os últimos parâmetros são o executável seguido dos arquivos de entrada (/home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map)

__Importante!__

__Ao executar matenha os arquivos e executáveis em diretórios com caminhos idênticos e ao passar como parâmetros o executável e os arquivos passa o caminho completo para garantir que a aplicação conseguirá acessar__   

### Execuções em série

Foi criado um script para facilitar as execuções, nele são criados arquivos para utilizar nas execuções onde o primeiro arquivo é criado, renomeado e outro arquivo gerado em seguida.

Para executar o script basta digita navegar via até o diretório onde os arquivos se encontram e executar o comando:

> $ bash executa.sh

###RESTRIÇÕES

__Importante!__

__A versão de multiplicação em blocos pode ter seu desempenho melhorado ou degradado de acordo com o a dimensão dos blocos escolhida, a variável *TILE* presente no código main pode ser alterada facilmente. Entretanto deve ser escolhido respeitandoa condição de que dimensão da matriz de entrada (N), a dimensão do bloco (T) e o número de procesos (NP) divididos devem ter resto da divisão igual a zero (se N/T/NP == 0 OK), (se N/T/NP != 0 bad).__


## Remoção dos arquivos

Para remover os arquivos criados basta executar o comando abaixo

> $ make clean 


## Contato

Quaisquer dúvidas ou problemas favor entrar em contato pelo endereço escobarvasques@gmail.com.

## Autor

Gabriel Escobar.

## Data
07/06/2019
