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

Para executar a aplicação principal é preciso gerar um arquivo com as dimensões NxM. N e M devem ser iguais (matriz quadradas) para garantir que a execução ocorra corretamente. Caso o usuário deseje executar com dois arquivos diferentes é necessário gerar um arquivo renomear o arquivo manualmente, e posteriormente gerar novo arquivo com as mesmas dimensões do primeiro para garantir a compatibilidade dos arquivos de entrada, levando em conta que devem ser arquivos de entrada com mesmas dimensões. 

Se você gerar um arquivo com as dimensões 128 x 128 através do comando acima, a aplicação irá gerar um arquivo com o nome 128x128-mat. Caso deseje é possível usar um único arquivo como entrada, basta colocar nos dois parâmetros de execução da aplicação o mesmo nome.
Já para executar com dois arquivos diferentes é necessário gerar dois arquivos com as mesmas dimensões. Entretanto, é necessário gerar o primeiro, renomear manualmente e gerar o outro arquivo com as mesmas dimensões do primeiro.


### Execução local (memória compartilhada).

Para executar localmente em ambiente de memória compartilhada, basta navegar até o diretório onde os arquivos estão presentes e executar o comando abaixo:

> $ mpirun -np 4 main_matriz 128x128-mat.map 128x128-mat.map 

O primeiro parâmetro para execução é mpirun, este identifica que  logo após -np 4 (número de processos = 4) seguido do executável e seus respectivos parâmetros (main_matriz NxM-mat.map NxM-mat.map)


### Execução distribuída.

O MPI apesar de possibilitar execuções em ambientes de memória compartilhada é voltado para ambientes de memória distribuída. Para executar em ambiente de memória distribuída são necessários alguns cuidados.

Os executáveis e demais códigos devem estar em diretórios com os mesmos caminhos em todos os *hosts*, dessa forma todos serão executados corretamente.

É necessário passar como parâmetro a lista de *hosts* e a interface de rede pela qual a comunicação entre os processos irá acontecer.

Para executar a aplicação executar em terminal linux o comando abaixo:

> $ mpirun --mca btl ^openib --mca btl_tcp_if_include ens3 -np 4 --map-by node --hostfile /home/aluno10/mpi/hostfile /home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map

O primeiro parâmetro indica que será executada uma aplicação mpi (mpirun), logo após estão os parâmetros de rede (--mca btl ^openib, --mca btl_tcp_if_include ens3), modo de mapeamento dos processos (--map-by node), arquivo de hosts (--hostfile /home/aluno10/mpi/hostfile). Os últimos três parâmetros são respectivamente o executável seguido dos arquivos de entrada (/home/aluno10/mpi/main_matriz /home/aluno10/mpi/3000x3000-mat.map /home/aluno10/mpi/3000x3000-mat.map).

No comando acima a interface de rede utilizada é identificada como *ens3*. Para verificar a interface de rede correta no seu ambiente de execução execute o comando ifconfig e verifique o nome correto da interface de rede do ambiente de testes. Coloque os caminhos dos arquivos e executável de acordo com o seu usuário, o comando acima é baseado na execução realizada no usuário do autor (aluno10). 

__Importante!__

__É necessário compilar os códigos em todos os hosts para garantir o funcionamento correto da aplicação.__

__Ao executar matenha os arquivos e executáveis em diretórios com caminhos idênticos nos hosts__

__Passe os parâmetros de execução do arquivo executável e arquivos de entrada com o caminho completo para garantir que o acesso aos mesmos na execução.__ 

__O arquivo *hostfile* possui a lista de hosts onde a aplicação será executada, nele estão colocados os hosts ppa-0 e ppa-1 sugeridos pelo professor.__

__Também foi utilizado o comando slots para definir quantos processos podem ser utilizados por host. No hostfile disponibilizado para esta aplicação foram definidos 4 slots por host que é a capacidade máxima do ambiente disponibilizado pelo professor__

### Execuções em série

Foi criado um script para facilitar as execuções, nele são criados arquivos para utilizar nas execuções onde o primeiro arquivo é criado, renomeado e outro arquivo gerado em seguida.

Para executar o script basta digita navegar via até o diretório onde os arquivos se encontram e executar o comando:

> $ bash executa.sh

### Restrições

__Importante!__

__A versão de multiplicação em blocos pode ter seu desempenho melhorado ou degradado de acordo com a dimensão dos blocos escolhida, a variável *TILE* presente no código main_matriz.c pode ser alterada facilmente. Entretanto deve ser escolhido respeitando a condição de que dimensão da matriz de entrada (N), a dimensão do bloco (T) e o número de procesos (NP) divididos devem ter resto da divisão igual a zero, caso contrário não irá executar__


## Remoção dos arquivos.

Para remover os arquivos executáveis criados basta executar o comando abaixo

> $ make clean 


## Contato.

Quaisquer dúvidas ou problemas favor entrar em contato pelo endereço escobarvasques@gmail.com.

## Autor.

Gabriel Escobar.

## Data.
21/06/2019
