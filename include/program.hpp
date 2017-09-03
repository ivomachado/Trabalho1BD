#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include <string>

/**
 * \author Juliana Castro
 * 
 * Classe que concentra os programas pedidos no trabalho
 */
class Program {
public:
    /**
     * \author Juliana Castro
     * 
     * Abre o arquivo passado e gera um arquivo de dados, e dois de índice para este de dados
     */
    static void upload(std::string filename = "teste.csv");
    /**
     * \author Juliana Castro
     * 
     * Procura o id no arquivo de dados usando hashing
     */
    static void findrec(int32_t id);
    /**
     * \author Juliana Castro
     * 
     * Procura o id no arquivo de índice primário
     */
    static void seek1(int32_t id);
    /**
     * \author Juliana Castro
     * 
     * Procura o título no arquivo de índice secundário
     */
    static void seek2(std::string title);
    /**
     * \author Juliana Castro
     * 
     * Imprime mensagem de ajuda
     */
    static void help();
};

#endif // !PROGRAM_HPP
