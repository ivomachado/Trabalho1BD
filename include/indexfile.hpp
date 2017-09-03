#ifndef INDEXFILE_HPP
#define INDEXFILE_HPP

#include "field.hpp"
#include "block.hpp"
#include <cstdint>
#include <cstdio>


/**
 * \author Juliana Castro
 * 
 * Classe responsável por cuidar de um arquivo de índice denso, seja primário 
 * ou secundário, é onde fica de fato a B-Tree.
 */
class IndexFile{
    public:
    FILE *m_file;
    int32_t m_locatedBlocks{0};
    int32_t m_root{-1};
    /**
     * \author Juliana Castro
     * 
     * Abre um arquivo com o modo especificado
     */
    IndexFile(std::string filename, std::string mode);
    /**
     * \author Juliana Castro
     * 
     * Salva o cabeçalho no disco
     */
    ~IndexFile();
    /**
     * \author Juliana Castro
     * 
     * Cria um novo arquivo de índice
     */
    static IndexFile Create(std::string filename);
    /**
     * \author Juliana Castro
     * 
     * Abre um arquivo de índice já existente
     */
    static IndexFile Open(std::string filename);
    /**
     * \author Juliana Castro
     * 
     * Insere uma nova chave dada por field no índice com o dataBlockIndex como 
     * apontador de dados
     */
    void insert(Field field, int32_t dataBlockIndex);
    /**
     * \author Juliana Castro
     * 
     * Escreve o cabeçalho no disco
     */
    void writeHeaderToDisk();
    /**
     * \author Juliana Castro
     * 
     * Lê o cabeçalho do arquivo para a memória
     */
    void readHeaderFromDisk();
    /**
     * \author Juliana Castro
     * 
     * Busca no índice, retorna o apontador de dados caso encontre o field especificado
     * ou -1 se não encontrar. O segundo elemento do par é a quantidade de blocos
     * lidos do disco para achar o resultado
     */
    std::pair<int32_t, int32_t> search(Field field);
    size_t m_fanOut{0};

    /**
     * \author Juliana Castro
     * 
     * Encontra o apontador de índice que deve seguir para buscar/inserir um field
     */
    int findLocation(Field field, DiskBlock block);
    /**
     * \author Juliana Castro
     * 
     * Diz se um block é leaf
     */
    bool isLeaf(DiskBlock block);
    /**
     * \author Juliana Castro
     * 
     * Divide o bloco passado por parâmetro em dois novos blocos
     */
    Record split(DiskBlock& block);

    /**
     * \author Juliana Castro
     * 
     * Insere o field e seu apontador de dados em sua devida folha e sobe na árvore 
     * fazendo os splits necessários
     */
    Record insertNonFull(DiskBlock& block, int32_t blockOffset, Field field, int32_t dataBlockIndex);
};
#endif
