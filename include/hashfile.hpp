#ifndef HASHFILE_HPP
#define HASHFILE_HPP
#include "block.hpp"
#include "cstdint"
#include "cstdio"
#include "functional"
#include "record.hpp"
#include "utils.hpp"
#include "vector"

/**
 * \author Ivo Machado
 * 
 * Classe responsável por cuidar do arquivo de dados utilizando hashing
 */
class HashFile {
public:
    /**
     * \author Ivo Machado
     * 
     * Insere o Record passado por parâmetro em sua posição devida no hashing ou 
     * em blocos de overflow e retorna qual o índice do bloco em que foi feita a
     * inserção
     */
    int32_t insert(Record rec);
    FILE* m_file{ nullptr };
    /**
     * \author Ivo Machado
     * 
     * Escreve o cabeçalho do arquivo em disco e fecha o arquivo.
     */
    ~HashFile();
    /**
     * \author Ivo Machado
     * 
     * Abre o arquivo filename com o modo passado por parâmetro.
     */
    HashFile(std::string filename, std::string mode);
    /**
     * \author Ivo Machado
     * 
     * Cria um novo arquivo com o nome passado por parâmetro.
     */
    static HashFile Create(std::string filename);
    /**
     * \author Ivo Machado
     * 
     * Abre o arquivo filename com o modo passado por parâmetro.
     */
    static HashFile Open(std::string filename);
    /**
     * \author Ivo Machado
     * 
     * Número de blocos usados para o cabeçalho do arquivo
     */
    static const int NUMBER_BLOCKS_HEADER = 46;
    /**
     * \author Ivo Machado
     * 
     * Número total de blocos alocados para fazer o hashing
     */
    static const int32_t NUMBER_BLOCKS{ (DiskBlock::AVAILABLE_SIZE * NUMBER_BLOCKS_HEADER - 4) * 8 };
    int m_fieldHashIndex{ 0 };
    Utils::BitMap m_blocksMap;
    /**
     * \author Ivo Machado
     * 
     * Escreve o cabeçalho do arquivo no disco
     */
    void writeHeaderToDisk();
    /**
     * \author Ivo Machado
     * 
     * Lê o cabeçalho do arquivo para a memória
     */
    void readHeaderFromDisk();
    int32_t m_overflowBlocks{ 0 };
    /**
     * \author Ivo Machado
     * 
     * Procura pelo field no arquivo, recordFields é o esquema dos registros nele salvo.
     */
    std::pair<Record, int32_t> search(Field field, std::vector<Field> recordFields);
    /**
     * \author Ivo Machado
     * 
     * Compara todos os registros do bloco em blockIndex com o field passado por parâmetro
     * usando o fieldIndex para escolher o campo dentro de cada registro
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields, int fieldIndex);
    /**
     * \author Ivo Machado
     * 
     * Pega o registro de um bloco que tenha o campo de hash igual ao field passado
     * por parâmetro.
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields);
};
#endif // !HASHFILE_HPP
