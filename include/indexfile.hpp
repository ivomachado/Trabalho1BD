#ifndef INDEXFILE_HPP
#define INDEXFILE_HPP

#include "field.hpp"
#include "block.hpp"
#include <cstdint>
#include <cstdio>


/**
 * Classe responsável por cuidar de um arquivo de índice denso, seja primário 
 * ou secundário, é onde fica de fato a B-Tree.
 * 
 * @author Juliana Castro
 */
class IndexFile{
    public:
    /** Ponteiro para o arquivo */
    FILE *m_file;
    /** Quantidade de nós da árvore */
    int32_t m_locatedBlocks{0};
    /** Apontador para o raiz da árvore */
    int32_t m_root{-1};
    /**
     * Abre um arquivo com o modo especificado
     * 
     * @author Juliana Castro
     */
    IndexFile(std::string filename, std::string mode);
    /**
     * Salva o cabeçalho no disco
     * 
     * @author Juliana Castro
     */
    ~IndexFile();
    /**
     * Cria um novo arquivo de índice
     * 
     * @author Juliana Castro
     */
    static IndexFile Create(std::string filename);
    /**
     * Abre um arquivo de índice já existente
     * 
     * @author Juliana Castro
     */
    static IndexFile Open(std::string filename);
    /**
     * Insere uma nova chave dada por field no índice com o dataBlockIndex como 
     * apontador de dados
     * 
     * @author Juliana Castro
     */
    void insert(Field field, int32_t dataBlockIndex);
    /**
     * Escreve o cabeçalho no disco
     * 
     * @author Juliana Castro
     */
    void writeHeaderToDisk();
    /**
     * Lê o cabeçalho do arquivo para a memória
     * 
     * @author Juliana Castro
     */
    void readHeaderFromDisk();
    /**
     * Busca no índice, retorna o apontador de dados caso encontre o field especificado
     * ou -1 se não encontrar. O segundo elemento do par é a quantidade de blocos
     * lidos do disco para achar o resultado
     * 
     * @author Juliana Castro
     */
    std::pair<int32_t, int32_t> search(Field field);
    /** Número máximo de chaves em um nó da árvore, é sempre par */
    size_t m_fanOut{0};

    /**
     * Encontra o apontador de índice que deve seguir para buscar/inserir um field
     * 
     * @author Juliana Castro
     */
    int findLocation(Field field, DiskBlock block);
    /**
     * Diz se um block é leaf
     * 
     * @author Juliana Castro
     */
    bool isLeaf(DiskBlock block);
    /**
     * Divide o bloco passado por parâmetro em dois novos blocos
     * 
     * @author Juliana Castro
     */
    Record split(DiskBlock& block);

    /**
     * Insere o field e seu apontador de dados em sua devida folha e sobe na árvore 
     * fazendo os splits necessários
     * 
     * @author Juliana Castro
     */
    Record insertNonFull(DiskBlock& block, int32_t blockOffset, Field field, int32_t dataBlockIndex);
};
#endif
