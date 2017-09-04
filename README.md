# Trabalho Prático I

Primeiro trabalho da disciplina de Banco de Dados I no período 2017/2.

## Alunos

- Ivo Machado de Souza - 21553684
- Juliana Castro da Silva - 21553685

## Documentação

Utilizou-se a ferramenta [Doxygen](http://www.stack.nl/~dimitri/doxygen/) 
para a documentação do código fonte.
Para gerar a documentação atualizada é necessário ter o software instalado na 
máquina e pela linha de comando na pasta raiz do projeto executar:

```bash
doxygen
```

Serão geradas as pastas `doc/html` e `doc/latex` com a documentação do código fonte.

Para gerar um `.md` com toda a documentação, utilizamos o 
[Moxygen](https://sourcey.com/generating-beautiful-markdown-documentation-with-moxygen/), 
depois convertemos o .md junto com este readme para um pdf.

## Compilação

O projeto possui um makefile mais orientado a ambiente Unix, para utilizá-lo no Windows, são necessários mais passos.

### Ambientes Unix

Basta executar na pasta do projeto:

```bash
make
```

### Ambientes Windows

É necessário ter o [MinGW](http://www.mingw.org/) 
no path do sistema e 
ter o [WSL](https://msdn.microsoft.com/pt-br/commandline/wsl/about#) instalado na máquina. Com os pré-requisitos satisfeitos, basta 
executar num ambiente WSL os seguintes comandos:

```bash
make OBJDIR=binWsl
rm -r binWsl
mingw32-make.exe # O WSL chamará o make do do MingW no windows
```

Esses passos são apenas para gerar um executável nativo do Windows, para 
executar apenas no WSL, basta seguir os passos para ambiente Unix.


## Execução

Na pasta do projeto, basta chamar:

```bash
bin/program
```


## Estrutura

Foi utilizado registros de tamanho fixo e de alocação não espalhada em todos os
arquivos.

### Bloco

O bloco tem tamanho definido de 4096 e todos os blocos operados no programa tem 
2 inteiros de 4 bytes como cabeçalho, o primeiro que indica o número de registros no
bloco e o segundo que serve como apontador.

### Arquivo de Dados

O arquivo de dados foi feito utilizando hashing com bucket de tamanho 1, em que o 
segundo inteiro do cabeçalho do bloco é utilizado como apontador de bloco de overflow.

Há 46 blocos de cabeçalho para este arquivo, o primeiro contém 1 um inteiro que diz
o número de blocos de overflow alocados e o resto do primeiro bloco é um mapa de bits,
todos os outros 45 blocos são utilizados de mapa de bits.

Somando estes mapas de bits, temos 1504352 bits e cada um deste bit diz se o 
bloco de índice equivalente está ocupado ou não. Ou seja, este é o tamanho da tabela
utilizada no arquivo.

Pensamos em usar número mágico em cada bloco para verificar se o bloco é válido ou não,
mas como essa abordagem deixa margem para erros, decidimos usar os mapas de bits mesmo.

### Arquivo de Índice

Os arquivos de índice usam o segundo inteiro do cabeçalho do bloco como o primeiro
ponteiro de índice do nó que o bloco representa, e cada registro inserido no nó
possui 3 campos:
 - O valor do campo utilizado no índice
 - O apontador de dados que tem o offset de blocos do arquivo de dados
 - O apontador de índice dos elementos maiores que o valor do campo

Assim cada registro guarda o ponteiro para chaves maiores que a sua e o cabeçaçalho 
do bloco guarda o ponteiro para as chaves menores que todas as chaves do bloco.

É utilizado apenas um bloco de cabeçalho que contém dois inteiros: a quantidade de
blocos alocados e o apontador para a raiz da B-Tree.


# Documentação do Código Fonte

A seguir vem a documentação gerada pelo Doxygen a partir do Código fonte

# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`DataTypes`](#field_8hpp_1afb6eb4f28419b652027fad41104a6d22)            | Tipos possíveis de [Field](#class_field)
`public void `[`removeQuotes`](#article_8cpp_1aa762706d3c831a323934373c65c5fd9d)`(char * buffer)`            | Remove aspas da string passada por parâmetro
`public void `[`readString`](#article_8cpp_1ab4e79ea296499ae762c56f95d06049f0)`(FILE * file,char * buffer,char * destination,int maxSize,bool acceptNewLines)`            | Lê um campo string do arquivo de entrada e salva em destination
`public bool `[`operator==`](#field_8cpp_1a7090e5c4b6a4ff35c84ff6af33f13492)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de igual
`public bool `[`operator!=`](#field_8cpp_1a8855ef8272c212ef2513ad42c1a84ce4)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de diferente
`public bool `[`operator>`](#field_8cpp_1aa7173a0f1daae68c681bb0f3a0609d0d)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de maior
`public bool `[`operator>=`](#field_8cpp_1ad00a56d34257328adba743cc7254b2d6)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de maior ou igual
`public bool `[`operator<`](#field_8cpp_1a23d89150c66a67794f40b9d50a8942a9)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de menor
`public bool `[`operator<=`](#field_8cpp_1a49fb1752651a8d1de0787b3eff57ad0d)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)`            | Operador de menor ou igual
`public std::ostream & `[`operator<<`](#field_8cpp_1a6e0c95ea522f1019a429ce39551cdabc)`(std::ostream & os,const `[`Field`](#class_field)` & field)`            | Operador de impressão de um field
`public int `[`main`](#program_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | 
`namespace `[`Utils`](#namespace_utils) | Contém coisas não diretamente ligadas ao problema mas que são úteis
`class `[`Article`](#class_article) | Classe que concentra as operações centradas em artigos
`class `[`DiskBlock`](#class_disk_block) | Classe responsável por realizar abstração de um bloco, todos os acessos de leitura e escrita ao disco são feitos por ela
`class `[`Field`](#class_field) | Classe de abstração de campos atômicos com seus tipos de dados possíveis, escreve e lê suas informações em buffer de bytes
`class `[`HashFile`](#class_hash_file) | Classe responsável por cuidar do arquivo de dados utilizando hashing
`class `[`IndexFile`](#class_index_file) | Classe responsável por cuidar de um arquivo de índice denso, seja primário ou secundário, é onde fica de fato a B-Tree.
`class `[`Program`](#class_program) | Classe que concentra os programas pedidos no trabalho
`class `[`Record`](#class_record) | Classe de abstração de um registro e seus campos, escreve e lê suas informações em buffer de bytes

## Members

#### `enum `[`DataTypes`](#field_8hpp_1afb6eb4f28419b652027fad41104a6d22) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Invalid            | 
Integer            | 
String            | 
ByteArray            | 

Tipos possíveis de [Field](#class_field)

Ivo Machado

#### `public void `[`removeQuotes`](#article_8cpp_1aa762706d3c831a323934373c65c5fd9d)`(char * buffer)` 

Remove aspas da string passada por parâmetro

Juliana Castro

#### `public void `[`readString`](#article_8cpp_1ab4e79ea296499ae762c56f95d06049f0)`(FILE * file,char * buffer,char * destination,int maxSize,bool acceptNewLines)` 

Lê um campo string do arquivo de entrada e salva em destination

Juliana Castro

#### `public bool `[`operator==`](#field_8cpp_1a7090e5c4b6a4ff35c84ff6af33f13492)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de igual

Ivo Machado

#### `public bool `[`operator!=`](#field_8cpp_1a8855ef8272c212ef2513ad42c1a84ce4)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de diferente

Ivo Machado

#### `public bool `[`operator>`](#field_8cpp_1aa7173a0f1daae68c681bb0f3a0609d0d)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de maior

Ivo Machado

#### `public bool `[`operator>=`](#field_8cpp_1ad00a56d34257328adba743cc7254b2d6)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de maior ou igual

Ivo Machado

#### `public bool `[`operator<`](#field_8cpp_1a23d89150c66a67794f40b9d50a8942a9)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de menor

Ivo Machado

#### `public bool `[`operator<=`](#field_8cpp_1a49fb1752651a8d1de0787b3eff57ad0d)`(const `[`Field`](#class_field)` & a,const `[`Field`](#class_field)` & b)` 

Operador de menor ou igual

Ivo Machado

#### `public std::ostream & `[`operator<<`](#field_8cpp_1a6e0c95ea522f1019a429ce39551cdabc)`(std::ostream & os,const `[`Field`](#class_field)` & field)` 

Operador de impressão de um field

Ivo Machado

#### `public int `[`main`](#program_8cpp_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

# namespace `Utils` 

Contém coisas não diretamente ligadas ao problema mas que são úteis

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<typename T>`  <br/>`short `[`writeVectorToBuffer`](#namespace_utils_1a6977805499dd96f8ecdd9fc26b9a50f7)`(char * buffer,std::vector< T > & m_data,short begin)`            | Escreve o vector m_data no buffer
`public template<typename T>`  <br/>`short `[`readVectorFromBuffer`](#namespace_utils_1ae7d74b0347480f0b81fe527d9e095e3c)`(char * buffer,std::vector< T > & m_data,short begin)`            | Lê o vector m_data do buffer
`public inline void `[`intToCharArray`](#namespace_utils_1a3951f18ae5bb82300d49459a199c468b)`(int32_t value,char * buffer)`            | Converte o value para 4 char e os escreve em buffer
`public inline int32_t `[`charArrayToInt`](#namespace_utils_1a7ea463985f5cf7020ea2e68a468fed92)`(char * buffer)`            | converte 4 char para inteiro
`public inline int64_t `[`calcBlockOffset`](#namespace_utils_1a4949e62f15b55b7718482a57a47a33e3)`(int32_t blockIndex,int32_t headerOverhead)`            | Calcula o offset em bytes do bloco pedido considerando o overhead de cabeçalho do arquivo
`class `[`Utils::BitMap`](#class_utils_1_1_bit_map) | Abstrai um mapa de bits para facilitar as operações de ligar e desligar bits

## Members

#### `public template<typename T>`  <br/>`short `[`writeVectorToBuffer`](#namespace_utils_1a6977805499dd96f8ecdd9fc26b9a50f7)`(char * buffer,std::vector< T > & m_data,short begin)` 

Escreve o vector m_data no buffer

Ivo Machado

#### `public template<typename T>`  <br/>`short `[`readVectorFromBuffer`](#namespace_utils_1ae7d74b0347480f0b81fe527d9e095e3c)`(char * buffer,std::vector< T > & m_data,short begin)` 

Lê o vector m_data do buffer

Ivo Machado

#### `public inline void `[`intToCharArray`](#namespace_utils_1a3951f18ae5bb82300d49459a199c468b)`(int32_t value,char * buffer)` 

Converte o value para 4 char e os escreve em buffer

Ivo Machado

#### `public inline int32_t `[`charArrayToInt`](#namespace_utils_1a7ea463985f5cf7020ea2e68a468fed92)`(char * buffer)` 

converte 4 char para inteiro

Ivo Machado

#### `public inline int64_t `[`calcBlockOffset`](#namespace_utils_1a4949e62f15b55b7718482a57a47a33e3)`(int32_t blockIndex,int32_t headerOverhead)` 

Calcula o offset em bytes do bloco pedido considerando o overhead de cabeçalho do arquivo

Ivo Machado

# class `Utils::BitMap` 

Abstrai um mapa de bits para facilitar as operações de ligar e desligar bits

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string `[`m_data`](#class_utils_1_1_bit_map_1a664e80c71868fa0e88a6c69adb20a6be) | Guarda os bytes na memória
`public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a30c43eb1bd508cffa7e9a02eeb1dd2b0)`()` | Construtor padrão com capacidade 0
`public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a66f7d88df852a475a1291e360e909857)`(const std::vector< `[`DiskBlock`](#class_disk_block)` > & data)` | Cria um bitmap com os dados dos ByteArray dos blocos passados por parâmetro
`public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a6eae87de8b9848e16e62c734d937736a)`(int32_t size)` | Cria um bitmap com capacidade no primeiro múltiplo de 8 maior ou igual ao tamanho pedido
`public inline bool `[`get`](#class_utils_1_1_bit_map_1ae3010063b3b92f7942647850e06e5913)`(int32_t pos)` | Retorna o booleano da posição informada
`public inline void `[`set`](#class_utils_1_1_bit_map_1a8596ecd383c6b8696ebf2230a1dea43f)`(int32_t pos,bool value)` | Atribui o valor passado à posição pedida
`public inline void `[`write`](#class_utils_1_1_bit_map_1a202b390976b23e38518f2432d4c9d9eb)`(std::vector< `[`DiskBlock`](#class_disk_block)` > & data)` | Escreve o bitmap divido nos atributos ByteArray de vários blocos

## Members

#### `public std::string `[`m_data`](#class_utils_1_1_bit_map_1a664e80c71868fa0e88a6c69adb20a6be) 

Guarda os bytes na memória

#### `public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a30c43eb1bd508cffa7e9a02eeb1dd2b0)`()` 

Construtor padrão com capacidade 0

Ivo Machado

#### `public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a66f7d88df852a475a1291e360e909857)`(const std::vector< `[`DiskBlock`](#class_disk_block)` > & data)` 

Cria um bitmap com os dados dos ByteArray dos blocos passados por parâmetro

Ivo Machado

#### `public inline  `[`BitMap`](#class_utils_1_1_bit_map_1a6eae87de8b9848e16e62c734d937736a)`(int32_t size)` 

Cria um bitmap com capacidade no primeiro múltiplo de 8 maior ou igual ao tamanho pedido

Ivo Machado

#### `public inline bool `[`get`](#class_utils_1_1_bit_map_1ae3010063b3b92f7942647850e06e5913)`(int32_t pos)` 

Retorna o booleano da posição informada

Ivo Machado

#### `public inline void `[`set`](#class_utils_1_1_bit_map_1a8596ecd383c6b8696ebf2230a1dea43f)`(int32_t pos,bool value)` 

Atribui o valor passado à posição pedida

Ivo Machado

#### `public inline void `[`write`](#class_utils_1_1_bit_map_1a202b390976b23e38518f2432d4c9d9eb)`(std::vector< `[`DiskBlock`](#class_disk_block)` > & data)` 

Escreve o bitmap divido nos atributos ByteArray de vários blocos

Ivo Machado

# class `Article` 

Classe que concentra as operações centradas em artigos

Juliana Castro

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`m_id`](#class_article_1a88006632607b9f6499dbf63358b73f56) | Id do artigo
`public char `[`m_title`](#class_article_1a7e138d1d1d6a67d10c721524353e84a7) | Title do artigo
`public int `[`m_year`](#class_article_1a8a6494a5948423e1c64ed2e2474feb54) | Year do artigo
`public char `[`m_authors`](#class_article_1a6db50a2f20f7bfca2c86149020b81c42) | Authors do artigo
`public int `[`m_quotes`](#class_article_1a1083082e89ee63ed628e3e4b757cff4e) | Quotes do artigo
`public char `[`m_updateTime`](#class_article_1aa17c544a06e8058a5b241c5ec14d52f4) | Update Time do artigo
`public char `[`m_snippet`](#class_article_1a9c78c470b689a3b98626b4a9a7638a08) | Snippet do artigo
`public  `[`Article`](#class_article_1ae2aa33bd4e486625dc47fb7b7580d7a2)`(FILE * file)` | Recebe um arquivo em formato csv e lê um registro dele, modificando o cursor do arquivo
`public  `[`Article`](#class_article_1aba1b3142ede0565d468cb4135384c96f)`()` | Construtor padrão, existe apenas para podermos criar coleções de artigos
`public `[`Record`](#class_record)` `[`toRecord`](#class_article_1a949a4bbb81aa1f00054c6c4a8021f1ff)`()` | Retorna um [Record](#class_record) com os dados do artigo
`public void `[`fromRecord`](#class_article_1a441d6f29f37a60dce0af4b92764a6fdb)`(`[`Record`](#class_record)` rec)` | Muda os dados do artigo para os dados presentes no [Record](#class_record) recebido por parâmetro
`public std::vector< `[`Field`](#class_field)` > `[`getFields`](#class_article_1a2838c10ccf1f322f0771af097897cdec)`()` | Retorna um vector de Fields que contém os dados do artigo, este vetor pode ser usado como schema no [DiskBlock](#class_disk_block) e como parâmetro do search do [HashFile](#class_hash_file)

## Members

#### `public int `[`m_id`](#class_article_1a88006632607b9f6499dbf63358b73f56) 

Id do artigo

#### `public char `[`m_title`](#class_article_1a7e138d1d1d6a67d10c721524353e84a7) 

Title do artigo

#### `public int `[`m_year`](#class_article_1a8a6494a5948423e1c64ed2e2474feb54) 

Year do artigo

#### `public char `[`m_authors`](#class_article_1a6db50a2f20f7bfca2c86149020b81c42) 

Authors do artigo

#### `public int `[`m_quotes`](#class_article_1a1083082e89ee63ed628e3e4b757cff4e) 

Quotes do artigo

#### `public char `[`m_updateTime`](#class_article_1aa17c544a06e8058a5b241c5ec14d52f4) 

Update Time do artigo

#### `public char `[`m_snippet`](#class_article_1a9c78c470b689a3b98626b4a9a7638a08) 

Snippet do artigo

#### `public  `[`Article`](#class_article_1ae2aa33bd4e486625dc47fb7b7580d7a2)`(FILE * file)` 

Recebe um arquivo em formato csv e lê um registro dele, modificando o cursor do arquivo

Juliana Castro

#### `public  `[`Article`](#class_article_1aba1b3142ede0565d468cb4135384c96f)`()` 

Construtor padrão, existe apenas para podermos criar coleções de artigos

Juliana Castro

#### `public `[`Record`](#class_record)` `[`toRecord`](#class_article_1a949a4bbb81aa1f00054c6c4a8021f1ff)`()` 

Retorna um [Record](#class_record) com os dados do artigo

Juliana Castro

#### `public void `[`fromRecord`](#class_article_1a441d6f29f37a60dce0af4b92764a6fdb)`(`[`Record`](#class_record)` rec)` 

Muda os dados do artigo para os dados presentes no [Record](#class_record) recebido por parâmetro

Juliana Castro

#### `public std::vector< `[`Field`](#class_field)` > `[`getFields`](#class_article_1a2838c10ccf1f322f0771af097897cdec)`()` 

Retorna um vector de Fields que contém os dados do artigo, este vetor pode ser usado como schema no [DiskBlock](#class_disk_block) e como parâmetro do search do [HashFile](#class_hash_file)

Juliana Castro

# class `DiskBlock` 

Classe responsável por realizar abstração de um bloco, todos os acessos de leitura e escrita ao disco são feitos por ela

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::vector< `[`Record`](#class_record)` > `[`m_records`](#class_disk_block_1ac7bc8c447c8cf524169d3b9c425f1cbb) | Vetor de registros do bloco
`public short `[`m_recordSize`](#class_disk_block_1a99d1a8822c87c7ea3642f49cae5b8b83) | Tamanho de um registro
`public char `[`m_buffer`](#class_disk_block_1ab4450251ab0feded46c43552e0367771) | Buffer de char que para onde é lido o bloco do disco e que é escrito no disco
`public std::vector< `[`Field`](#class_field)` > `[`m_recordFields`](#class_disk_block_1af223c8a16c961429be49e51d3b61a2c3) | Vetor dos registros em memória
`public `[`Record`](#class_record)` `[`m_header`](#class_disk_block_1a87d352adc767f5fe460dcfa86ae85af4) | Cabeçalho do bloco
`public short `[`m_bufferPos`](#class_disk_block_1a71819fbc56f7d492a43aab43426ca5de) | Posição do buffer para fazer a próxima escrita/leitura
`public  `[`DiskBlock`](#class_disk_block_1addb61ad94fe4e488eeb14c9df03cd339)`(std::vector< `[`Field`](#class_field)` > & recordFields)` | 
`public void `[`readFromFile`](#class_disk_block_1aeaf825dc9ef07d7ba8f6c6934c75371e)`(FILE * file)` | Lê um bloco do disco de um arquivo previamente posicionado no endereço certo para um vetor de char. Depois com base na quantidade de registros no bloco, faz o parse para registros em memória.
`public void `[`writeToFile`](#class_disk_block_1acc14fbd0c60be9df6f62bd0262457c82)`(FILE * file)` | Faz o parse dos registros em memória para o buffer
`public void `[`writeToBuffer`](#class_disk_block_1a2990ec8b607f6d112da5c29b1cbf2116)`()` | Escreve o cabeçalho do bloco e todos seus registros no buffer
`public void `[`readFromBuffer`](#class_disk_block_1ad00fcc5333990842e2399f6b91816941)`()` | Lê o cabeçalho do bloco e todos seus registros do buffer
`public bool `[`insert`](#class_disk_block_1ae8e84f3e5472c22137b7faf3bb94c61d)`(const `[`Record`](#class_record)` & record)` | Tenta inserir um novo registro no bloco caso o registro caiba no bloco
`public bool `[`fitOneMoreRecord`](#class_disk_block_1a5329ae6ded4c51a7a76909df615fc44d)`()` | Informa se ainda cabe mais um registro no bloco

## Members

#### `public std::vector< `[`Record`](#class_record)` > `[`m_records`](#class_disk_block_1ac7bc8c447c8cf524169d3b9c425f1cbb) 

Vetor de registros do bloco

#### `public short `[`m_recordSize`](#class_disk_block_1a99d1a8822c87c7ea3642f49cae5b8b83) 

Tamanho de um registro

#### `public char `[`m_buffer`](#class_disk_block_1ab4450251ab0feded46c43552e0367771) 

Buffer de char que para onde é lido o bloco do disco e que é escrito no disco

Ivo Machado

#### `public std::vector< `[`Field`](#class_field)` > `[`m_recordFields`](#class_disk_block_1af223c8a16c961429be49e51d3b61a2c3) 

Vetor dos registros em memória

Ivo Machado

#### `public `[`Record`](#class_record)` `[`m_header`](#class_disk_block_1a87d352adc767f5fe460dcfa86ae85af4) 

Cabeçalho do bloco

Ivo Machado

#### `public short `[`m_bufferPos`](#class_disk_block_1a71819fbc56f7d492a43aab43426ca5de) 

Posição do buffer para fazer a próxima escrita/leitura

Ivo Machado

#### `public  `[`DiskBlock`](#class_disk_block_1addb61ad94fe4e488eeb14c9df03cd339)`(std::vector< `[`Field`](#class_field)` > & recordFields)` 

#### `public void `[`readFromFile`](#class_disk_block_1aeaf825dc9ef07d7ba8f6c6934c75371e)`(FILE * file)` 

Lê um bloco do disco de um arquivo previamente posicionado no endereço certo para um vetor de char. Depois com base na quantidade de registros no bloco, faz o parse para registros em memória.

Ivo Machado

#### `public void `[`writeToFile`](#class_disk_block_1acc14fbd0c60be9df6f62bd0262457c82)`(FILE * file)` 

Faz o parse dos registros em memória para o buffer

Ivo Machado

#### `public void `[`writeToBuffer`](#class_disk_block_1a2990ec8b607f6d112da5c29b1cbf2116)`()` 

Escreve o cabeçalho do bloco e todos seus registros no buffer

Ivo Machado

#### `public void `[`readFromBuffer`](#class_disk_block_1ad00fcc5333990842e2399f6b91816941)`()` 

Lê o cabeçalho do bloco e todos seus registros do buffer

Ivo Machado

#### `public bool `[`insert`](#class_disk_block_1ae8e84f3e5472c22137b7faf3bb94c61d)`(const `[`Record`](#class_record)` & record)` 

Tenta inserir um novo registro no bloco caso o registro caiba no bloco

Ivo Machado

#### `public bool `[`fitOneMoreRecord`](#class_disk_block_1a5329ae6ded4c51a7a76909df615fc44d)`()` 

Informa se ainda cabe mais um registro no bloco

Ivo Machado

# class `Field` 

Classe de abstração de campos atômicos com seus tipos de dados possíveis, escreve e lê suas informações em buffer de bytes

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public short `[`m_maxSize`](#class_field_1a60df814b17c689b69ca0f225fd4259e3) | Tamanho máximo da string ou do bytearray
`public DataTypes `[`m_type`](#class_field_1a0f8c9fad1a055bd00a3469c00573f6ab) | Tipo do [Field](#class_field), padrão é inválido
`public int32_t `[`m_integer`](#class_field_1a57e6cc81cc7c3381a638df3ef35fd0ea) | Guarda o inteiro
`public std::string `[`m_string`](#class_field_1aa18427d31aed6226cd7cbe942d38cfd6) | Guarda a string e o bytarray
`public  `[`Field`](#class_field_1a40f3f05a383af6fad21d50caa12b4de1)`(DataTypes type)` | Constrói com o type passado
`public inline  `[`Field`](#class_field_1a3e804c92273d9159f413f227b535c672)`()` | Construtor padrão
`public int32_t `[`hash`](#class_field_1a409f03c120448f6b8e24bb2bab3d405f)`(int32_t size)` | Retorna a posição a que a instância de [Field](#class_field) pertence numa tabela hash de tamanho size.
`public short `[`size`](#class_field_1a2ae15ec47b1c1e29ba26c260ef9268b7)`()` | Retorna o tamanho que o campo ocupa no disco em bytes.
`public short `[`writeToBuffer`](#class_field_1a09cb3e1a3d237d388b5e52caac39d4a5)`(char * buffer,short begin)` | Escreve o valor do field no buffer a partir da posição begin
`public short `[`readFromBuffer`](#class_field_1aaabcd0b813fd7b3e4ff8cf0d59634fb2)`(char * buffer,short begin)` | Lê o dado do field do buffer a partir da posição begin

## Members

#### `public short `[`m_maxSize`](#class_field_1a60df814b17c689b69ca0f225fd4259e3) 

Tamanho máximo da string ou do bytearray

#### `public DataTypes `[`m_type`](#class_field_1a0f8c9fad1a055bd00a3469c00573f6ab) 

Tipo do [Field](#class_field), padrão é inválido

#### `public int32_t `[`m_integer`](#class_field_1a57e6cc81cc7c3381a638df3ef35fd0ea) 

Guarda o inteiro

#### `public std::string `[`m_string`](#class_field_1aa18427d31aed6226cd7cbe942d38cfd6) 

Guarda a string e o bytarray

#### `public  `[`Field`](#class_field_1a40f3f05a383af6fad21d50caa12b4de1)`(DataTypes type)` 

Constrói com o type passado

#### `public inline  `[`Field`](#class_field_1a3e804c92273d9159f413f227b535c672)`()` 

Construtor padrão

#### `public int32_t `[`hash`](#class_field_1a409f03c120448f6b8e24bb2bab3d405f)`(int32_t size)` 

Retorna a posição a que a instância de [Field](#class_field) pertence numa tabela hash de tamanho size.

Ivo Machado

#### `public short `[`size`](#class_field_1a2ae15ec47b1c1e29ba26c260ef9268b7)`()` 

Retorna o tamanho que o campo ocupa no disco em bytes.

Ivo Machado

#### `public short `[`writeToBuffer`](#class_field_1a09cb3e1a3d237d388b5e52caac39d4a5)`(char * buffer,short begin)` 

Escreve o valor do field no buffer a partir da posição begin

Ivo Machado

#### `public short `[`readFromBuffer`](#class_field_1aaabcd0b813fd7b3e4ff8cf0d59634fb2)`(char * buffer,short begin)` 

Lê o dado do field do buffer a partir da posição begin

Ivo Machado

# class `HashFile` 

Classe responsável por cuidar do arquivo de dados utilizando hashing

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public FILE * `[`m_file`](#class_hash_file_1ab80a64a91da6e910e00467a3d2077a07) | Ponteiro para o arquivo
`public int `[`m_fieldHashIndex`](#class_hash_file_1a6f00883f9cc7280fa955aea664ef1b9e) | Campo do registro que será utilizado no hash, default para 0
`public `[`Utils::BitMap`](#class_utils_1_1_bit_map)` `[`m_blocksMap`](#class_hash_file_1aed2c3de147b07d33037a2e8c5718a78e) | Mapa de Bytes em memória dos blocos ocupados
`public int32_t `[`m_overflowBlocks`](#class_hash_file_1a7c4d4055474f916dbaa8db6f95aa0208) | Quantidade de blocos de overflow em memória
`public int32_t `[`insert`](#class_hash_file_1af64935632a76c199dbc314b629d7275f)`(`[`Record`](#class_record)` rec)` | Insere o [Record](#class_record) passado por parâmetro em sua posição devida no hashing ou em blocos de overflow e retorna qual o índice do bloco em que foi feita a inserção
`public  `[`~HashFile`](#class_hash_file_1a9845057dcbec1a5d281bf496aa9d3487)`()` | Escreve o cabeçalho do arquivo em disco e fecha o arquivo.
`public  `[`HashFile`](#class_hash_file_1ae385b9c42cd3a981d7a3dc8abe5cb45c)`(std::string filename,std::string mode)` | Abre o arquivo filename com o modo passado por parâmetro.
`public void `[`writeHeaderToDisk`](#class_hash_file_1ad656d6d9b4b63f5233a83d2c041107d7)`()` | Escreve o cabeçalho do arquivo no disco
`public void `[`readHeaderFromDisk`](#class_hash_file_1aced30da629d94eefec94ab3cafe92003)`()` | Lê o cabeçalho do arquivo para a memória
`public std::pair< `[`Record`](#class_record)`, int32_t > `[`search`](#class_hash_file_1a7434127500629cd0e1b79eef69dc8ddc)`(`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields)` | Procura pelo field no arquivo, recordFields é o esquema dos registros nele salvo.
`public `[`Record`](#class_record)` `[`getFromBlock`](#class_hash_file_1a9c857681525a96a6b809211c64fa09a8)`(int32_t blockIndex,`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields,int fieldIndex)` | Compara todos os registros do bloco em blockIndex com o field passado por parâmetro usando o fieldIndex para escolher o campo dentro de cada registro
`public `[`Record`](#class_record)` `[`getFromBlock`](#class_hash_file_1a74b0c25b49be6ddf963b32af3150ead7)`(int32_t blockIndex,`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields)` | Pega o registro de um bloco que tenha o campo de hash igual ao field passado por parâmetro.

## Members

#### `public FILE * `[`m_file`](#class_hash_file_1ab80a64a91da6e910e00467a3d2077a07) 

Ponteiro para o arquivo

#### `public int `[`m_fieldHashIndex`](#class_hash_file_1a6f00883f9cc7280fa955aea664ef1b9e) 

Campo do registro que será utilizado no hash, default para 0

#### `public `[`Utils::BitMap`](#class_utils_1_1_bit_map)` `[`m_blocksMap`](#class_hash_file_1aed2c3de147b07d33037a2e8c5718a78e) 

Mapa de Bytes em memória dos blocos ocupados

#### `public int32_t `[`m_overflowBlocks`](#class_hash_file_1a7c4d4055474f916dbaa8db6f95aa0208) 

Quantidade de blocos de overflow em memória

#### `public int32_t `[`insert`](#class_hash_file_1af64935632a76c199dbc314b629d7275f)`(`[`Record`](#class_record)` rec)` 

Insere o [Record](#class_record) passado por parâmetro em sua posição devida no hashing ou em blocos de overflow e retorna qual o índice do bloco em que foi feita a inserção

Ivo Machado

#### `public  `[`~HashFile`](#class_hash_file_1a9845057dcbec1a5d281bf496aa9d3487)`()` 

Escreve o cabeçalho do arquivo em disco e fecha o arquivo.

Ivo Machado

#### `public  `[`HashFile`](#class_hash_file_1ae385b9c42cd3a981d7a3dc8abe5cb45c)`(std::string filename,std::string mode)` 

Abre o arquivo filename com o modo passado por parâmetro.

Ivo Machado

#### `public void `[`writeHeaderToDisk`](#class_hash_file_1ad656d6d9b4b63f5233a83d2c041107d7)`()` 

Escreve o cabeçalho do arquivo no disco

Ivo Machado

#### `public void `[`readHeaderFromDisk`](#class_hash_file_1aced30da629d94eefec94ab3cafe92003)`()` 

Lê o cabeçalho do arquivo para a memória

Ivo Machado

#### `public std::pair< `[`Record`](#class_record)`, int32_t > `[`search`](#class_hash_file_1a7434127500629cd0e1b79eef69dc8ddc)`(`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields)` 

Procura pelo field no arquivo, recordFields é o esquema dos registros nele salvo.

Ivo Machado

#### `public `[`Record`](#class_record)` `[`getFromBlock`](#class_hash_file_1a9c857681525a96a6b809211c64fa09a8)`(int32_t blockIndex,`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields,int fieldIndex)` 

Compara todos os registros do bloco em blockIndex com o field passado por parâmetro usando o fieldIndex para escolher o campo dentro de cada registro

Ivo Machado

#### `public `[`Record`](#class_record)` `[`getFromBlock`](#class_hash_file_1a74b0c25b49be6ddf963b32af3150ead7)`(int32_t blockIndex,`[`Field`](#class_field)` field,std::vector< `[`Field`](#class_field)` > recordFields)` 

Pega o registro de um bloco que tenha o campo de hash igual ao field passado por parâmetro.

Ivo Machado

# class `IndexFile` 

Classe responsável por cuidar de um arquivo de índice denso, seja primário ou secundário, é onde fica de fato a B-Tree.

Juliana Castro

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public FILE * `[`m_file`](#class_index_file_1a3342bf7d6ded853512db5aa67bb306a2) | Ponteiro para o arquivo
`public int32_t `[`m_locatedBlocks`](#class_index_file_1a42b85ce2e598512c7ff84b9e24746c60) | Quantidade de nós da árvore
`public int32_t `[`m_root`](#class_index_file_1a2205305963cdc51950abd940e5325f0d) | Apontador para o raiz da árvore
`public size_t `[`m_fanOut`](#class_index_file_1a7dcf99d345983edc3307eca793d38edc) | Número máximo de chaves em um nó da árvore, é sempre par
`public  `[`IndexFile`](#class_index_file_1ad6426b2e3a432aa37112eeebeadea873)`(std::string filename,std::string mode)` | Abre um arquivo com o modo especificado
`public  `[`~IndexFile`](#class_index_file_1a0a8a8d6efa22a5a41dc36a46bf3df131)`()` | Salva o cabeçalho no disco
`public void `[`insert`](#class_index_file_1a71965bfc0fd9e56b94022fdedb049a54)`(`[`Field`](#class_field)` field,int32_t dataBlockIndex)` | Insere uma nova chave dada por field no índice com o dataBlockIndex como apontador de dados
`public void `[`writeHeaderToDisk`](#class_index_file_1abb50d2007d3d56b71ba86ea18b92adc5)`()` | Escreve o cabeçalho no disco
`public void `[`readHeaderFromDisk`](#class_index_file_1a1e71554b6dd8d3fe74c8f45e9fff8454)`()` | Lê o cabeçalho do arquivo para a memória
`public std::pair< int32_t, int32_t > `[`search`](#class_index_file_1aaf1cba8c9c7d36943cd5af7b1758e31a)`(`[`Field`](#class_field)` field)` | Busca no índice, retorna o apontador de dados caso encontre o field especificado ou -1 se não encontrar. O segundo elemento do par é a quantidade de blocos lidos do disco para achar o resultado
`public int `[`findLocation`](#class_index_file_1ae09f4cfebe90f6c42b0484af90b96f6c)`(`[`Field`](#class_field)` field,`[`DiskBlock`](#class_disk_block)` block)` | Encontra o apontador de índice que deve seguir para buscar/inserir um field
`public bool `[`isLeaf`](#class_index_file_1ae4b0b683cf1697faa218420a72620e3a)`(`[`DiskBlock`](#class_disk_block)` block)` | Diz se um block é leaf
`public `[`Record`](#class_record)` `[`split`](#class_index_file_1a92735437d4c8f765543812912b3c0231)`(`[`DiskBlock`](#class_disk_block)` & block)` | Divide o bloco passado por parâmetro em dois novos blocos
`public `[`Record`](#class_record)` `[`insertNonFull`](#class_index_file_1a60cd79846eb091a5e19e865ab11d3deb)`(`[`DiskBlock`](#class_disk_block)` & block,int32_t blockOffset,`[`Field`](#class_field)` field,int32_t dataBlockIndex)` | Insere o field e seu apontador de dados em sua devida folha e sobe na árvore fazendo os splits necessários

## Members

#### `public FILE * `[`m_file`](#class_index_file_1a3342bf7d6ded853512db5aa67bb306a2) 

Ponteiro para o arquivo

#### `public int32_t `[`m_locatedBlocks`](#class_index_file_1a42b85ce2e598512c7ff84b9e24746c60) 

Quantidade de nós da árvore

#### `public int32_t `[`m_root`](#class_index_file_1a2205305963cdc51950abd940e5325f0d) 

Apontador para o raiz da árvore

#### `public size_t `[`m_fanOut`](#class_index_file_1a7dcf99d345983edc3307eca793d38edc) 

Número máximo de chaves em um nó da árvore, é sempre par

#### `public  `[`IndexFile`](#class_index_file_1ad6426b2e3a432aa37112eeebeadea873)`(std::string filename,std::string mode)` 

Abre um arquivo com o modo especificado

Juliana Castro

#### `public  `[`~IndexFile`](#class_index_file_1a0a8a8d6efa22a5a41dc36a46bf3df131)`()` 

Salva o cabeçalho no disco

Juliana Castro

#### `public void `[`insert`](#class_index_file_1a71965bfc0fd9e56b94022fdedb049a54)`(`[`Field`](#class_field)` field,int32_t dataBlockIndex)` 

Insere uma nova chave dada por field no índice com o dataBlockIndex como apontador de dados

Juliana Castro

#### `public void `[`writeHeaderToDisk`](#class_index_file_1abb50d2007d3d56b71ba86ea18b92adc5)`()` 

Escreve o cabeçalho no disco

Juliana Castro

#### `public void `[`readHeaderFromDisk`](#class_index_file_1a1e71554b6dd8d3fe74c8f45e9fff8454)`()` 

Lê o cabeçalho do arquivo para a memória

Juliana Castro

#### `public std::pair< int32_t, int32_t > `[`search`](#class_index_file_1aaf1cba8c9c7d36943cd5af7b1758e31a)`(`[`Field`](#class_field)` field)` 

Busca no índice, retorna o apontador de dados caso encontre o field especificado ou -1 se não encontrar. O segundo elemento do par é a quantidade de blocos lidos do disco para achar o resultado

Juliana Castro

#### `public int `[`findLocation`](#class_index_file_1ae09f4cfebe90f6c42b0484af90b96f6c)`(`[`Field`](#class_field)` field,`[`DiskBlock`](#class_disk_block)` block)` 

Encontra o apontador de índice que deve seguir para buscar/inserir um field

Juliana Castro

#### `public bool `[`isLeaf`](#class_index_file_1ae4b0b683cf1697faa218420a72620e3a)`(`[`DiskBlock`](#class_disk_block)` block)` 

Diz se um block é leaf

Juliana Castro

#### `public `[`Record`](#class_record)` `[`split`](#class_index_file_1a92735437d4c8f765543812912b3c0231)`(`[`DiskBlock`](#class_disk_block)` & block)` 

Divide o bloco passado por parâmetro em dois novos blocos

Juliana Castro

#### `public `[`Record`](#class_record)` `[`insertNonFull`](#class_index_file_1a60cd79846eb091a5e19e865ab11d3deb)`(`[`DiskBlock`](#class_disk_block)` & block,int32_t blockOffset,`[`Field`](#class_field)` field,int32_t dataBlockIndex)` 

Insere o field e seu apontador de dados em sua devida folha e sobe na árvore fazendo os splits necessários

Juliana Castro

# class `Program` 

Classe que concentra os programas pedidos no trabalho

Juliana Castro

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Record` 

Classe de abstração de um registro e seus campos, escreve e lê suas informações em buffer de bytes

Ivo Machado

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::vector< `[`Field`](#class_field)` > `[`m_data`](#class_record_1ae1c05faeafeafbcdd48a00eda6dad1e9) | Vetor de [Field](#class_field) do registro
`public short `[`writeToBuffer`](#class_record_1a35a19c6b30eabbe45104bd63524ea213)`(char * buffer,short begin)` | Escreve os dados do [Record](#class_record) no buffer
`public short `[`readFromBuffer`](#class_record_1aa6b1365deb5f19f753325e9f5bc242f6)`(char * buffer,short begin)` | Lê os dados do buffer para o [Record](#class_record)
`public  `[`Record`](#class_record_1aa6395f52af3e5de10bd27fee604c04ff)`(const std::vector< `[`Field`](#class_field)` > & data)` | Cria um novo [Record](#class_record) com os dados do vector de fields recebido por parâmetro
`public  `[`Record`](#class_record_1ae8ee53ffec6ff4dac9911517d47e86a5)`()` | Construtor padrão

## Members

#### `public std::vector< `[`Field`](#class_field)` > `[`m_data`](#class_record_1ae1c05faeafeafbcdd48a00eda6dad1e9) 

Vetor de [Field](#class_field) do registro

#### `public short `[`writeToBuffer`](#class_record_1a35a19c6b30eabbe45104bd63524ea213)`(char * buffer,short begin)` 

Escreve os dados do [Record](#class_record) no buffer

Ivo Machado

#### `public short `[`readFromBuffer`](#class_record_1aa6b1365deb5f19f753325e9f5bc242f6)`(char * buffer,short begin)` 

Lê os dados do buffer para o [Record](#class_record)

Ivo Machado

#### `public  `[`Record`](#class_record_1aa6395f52af3e5de10bd27fee604c04ff)`(const std::vector< `[`Field`](#class_field)` > & data)` 

Cria um novo [Record](#class_record) com os dados do vector de fields recebido por parâmetro

Ivo Machado

#### `public  `[`Record`](#class_record_1ae8ee53ffec6ff4dac9911517d47e86a5)`()` 

Construtor padrão

Ivo Machado

Generated by [Moxygen](https://sourcey.com/moxygen)
