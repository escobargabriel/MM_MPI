# Descrição.

Este programa em sua execução realiza operações básicas e a multiplição de estruturas matriciais de quatro diferentes maneiras: convencional, em blocos, MPI convencional e MPI em blocos. 

Estão presentes nos códigos funções para alocação de memória, geração e preenchimento de todas as posições das matrizes, liberação da memória, etc.


## Compilação.

__Importante!__

__Este código e demais arquivos auxiliares foram desenvolvidos e executados em sistema operacional linux.__

Para compilar os códigos é necessário executar o arquivo "Makefile", neste arquivo estão presentes flags adicionais e comandos necessários para a compilação da aplicação e bibliotecas auxiliares. Para executar este arquivo é necessário navegar através do terminal no sistema operacional linux até o diretório onde se encontram os arquivos ".c", ".h", além do "Makefile" (exemplo: $ cd /home/MM_MPI).

 Estando dentro do diretório correto basta executar o *Makefile*:

> $ make

Após execução deste comando no terminal os códigos seram compilados e gerados os executáveis e binarios.

	
## Execução.
Após compilação para gerar os arquivos de entrada basta executar o comando abaixo:

> $./geraMatriz2 128 128

O primeiro parâmetro corresponde ao executável gerado na compilação, já o segundo e o terceiro parâmetros correspondem as dimensões da matriz N x M (128 x 128).

São necessários dois arquivos de entrada para execução da aplicação principal *main_matriz.c*, ambos são passados como parâmetro no momento da execução da aplicação.

O arquivo gerado pela aplicação *geraMatriz2.c* possui por padrão o nome NxM-mat.map.

Para executar a aplicação principal é preciso gerar um arquivo com as dimensões NxM. N e M devem ser iguais (matriz quadradas) para garantir que a execução ocorra corretamente. Caso o usuário deseje executar com dois arquivos diferentes é necessário gerar um arquivo renomear o arquivo manualmente, e posteriormente gerar novo arquivo com as mesmas dimensões do primeiro para garantir a compatibilidade dos arquivos de entrada, levando em conta que devem ser arquivos de entrada com mesmas dimensões e a aplicação irá gerar dois arquivos com nome idêntico. Outra possibilidade é gerar um único arquivo de entrada com uma matriz quadrada e utilizar o mesmo nos dois parâmetros de arquivos de entrada.


### Execução local (memória compartilhada).
Para executar localmente em ambiente de memória compartilhada basta navegar até o diretório onde os arquivos estão presentes e executar o comando abaixo

> $ mpirun -np 4 main_matriz 128x128-mat.map 128x128-mat.map 

O primeiro parâmetro para execução é mpirun, este identifica que  logo após -np 4 (número de processos = 4) seguido do executável e seus respectivos parâmetros (main_matriz NxN-mat.map NxN-mat.map)

### Execução distribuída.
O MPI apesar de possibilitar execuções em ambientes de memória compartilhada é voltado para ambientes de memória distribuída. Para executar em ambiente de memória distribuída são necessários alguns cuidados.

Os executáveis e demais códigos devem estar em diretórios com os mesmos caminhos em todos os *hosts* para que todos sejam executados corretamente.

É necessário passar como parâmetro a lista de *hosts* e a interface de rede pela qual a comunicação irá acontecer.

Para executar a aplicação basta navegar executar no terminal linux o comando abaixo:

> $ mpirun --mca btl ^openib --mca btl_tcp_if_include ens3 -np 4 --map-by node --hostfile /home/aluno10/mpi/hostfile /home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map

O primeiro parâmetro é mpirun seguido pelos parâmetros de rede (--mca btl ^openib, --mca btl_tcp_if_include ens3), modo de mapeamento dos processos (--map-by node), arquivo de hosts (--hostfile /home/aluno10/mpi/hostfile). Os últimos parâmetros são o executável seguido dos arquivos de entrada (/home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map)

No comando acima a interface de rede utilizada é identificada como *ens3*. Para verificar a interface de rede correta no seu ambiente de execução execute o comando ifconfig e verifique o nome correto da interface de rede presente no ambiente de testes que se pretende utilizar.

__Importante!__

__Ao executar matenha os arquivos e executáveis em diretórios com caminhos idênticos e ao passar como parâmetros o executável e os arquivos passar o caminho completo para garantir que a aplicação conseguirá acessar__   

### Execuções em série

Foi criado um script para facilitar as execuções, nele são criados arquivos para utilizar nas execuções onde o primeiro arquivo é criado, renomeado e outro arquivo gerado em seguida.

Para executar o script basta digita navegar via até o diretório onde os arquivos se encontram e executar o comando:

> $ bash executa.sh

### Restrições

__Importante!__

__A versão de multiplicação em blocos pode ter seu desempenho melhorado ou degradado de acordo com a dimensão dos blocos escolhida, a variável *TILE* presente no código main_matriz.c pode ser alterada facilmente. Entretanto deve ser escolhido respeitandoa condição de que dimensão da matriz de entrada (N), a dimensão do bloco (T) e o número de procesos (NP) divididos devem ter resto da divisão igual a zero, caso contrário irá gerar segmentation fault.__


## Remoção dos arquivos.

Para remover os arquivos executáveis criados basta executar o comando abaixo

> $ make clean 


## Contato.

Quaisquer dúvidas ou problemas favor entrar em contato pelo endereço escobarvasques@gmail.com.

## Autor.

Gabriel Escobar.

## Data.
07/06/2019
