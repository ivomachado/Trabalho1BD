#ifndef PROGRAM_HPP
#define PROGRAM_HPP

class Program {
private:
public:
    static const int BLOCK_SIZE = 4096;
    /** Função que lê da entrada padrão o nome de um arquivo, lê o arquivo e popula
     * O banco de dados com os dados do arquivo.
     */
    static void upload();
};

#endif
