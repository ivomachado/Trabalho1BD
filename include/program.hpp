#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include <string>

/**
 * Classe que concentra os programas pedidos no trabalho
 * 
 * \author Juliana Castro
 */
class Program {
public:
    /**
     * Abre o arquivo passado e gera um arquivo de dados, e dois de índice para este de dados
     * 
     * \author Juliana Castro
     */
    static void upload(std::string filename = "teste.csv");
    /**
     * Procura o id no arquivo de dados usando hashing
     * 
     * \author Juliana Castro
     */
    static void findrec(int32_t id);
    /**
     * Procura o id no arquivo de índice primário
     * 
     * \author Juliana Castro
     */
    static void seek1(int32_t id);
    /**
     * Procura o título no arquivo de índice secundário
     * 
     * \author Juliana Castro
     */
    static void seek2(std::string title);
    /**
     * Imprime mensagem de ajuda
     * 
     * \author Juliana Castro
     */
    static void help();
};

#endif // !PROGRAM_HPP
