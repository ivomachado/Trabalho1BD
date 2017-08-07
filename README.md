# Trabalho Prático I

Primeiro trabalho da disciplina de Banco de Dados I no período 2017/2.

## Alunos

- Ivo Machado de Souza - 21553684
- Juliana Castro da Silva - 21553686

## Documentação

Utiliza-se a ferramenta [Doxygen](http://www.stack.nl/~dimitri/doxygen/) 
para a documentação do código fonte.
Para gerar a documentação atualizada é necessário ter o software instalado na 
máquina e pela linha de comando na pasta raiz do projeto executar:

```bash
doxygen
```

Serão gerado as pastas `doc/html` e `doc/latex` com a documentação do código fonte.

## Compilação

O projeto possui um makefile mais orientado a ambiente Unix, ainda estamos 
estudando como melhorá-lo para funcionar sem problemas no Windows também.

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
