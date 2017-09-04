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
 * Classe responsável por cuidar do arquivo de dados utilizando hashing
 * 
 * @author Ivo Machado
 */
class HashFile {
public:
    /**
     * Insere o Record passado por parâmetro em sua posição devida no hashing ou 
     * em blocos de overflow e retorna qual o índice do bloco em que foi feita a
     * inserção
     * 
     * @author Ivo Machado
     */
    int32_t insert(Record rec);
    /** Ponteiro para o arquivo */
    FILE* m_file{ nullptr };
    /**
     * Escreve o cabeçalho do arquivo em disco e fecha o arquivo.
     * 
     * @author Ivo Machado
     */
    ~HashFile();
    /**
     * Abre o arquivo filename com o modo passado por parâmetro.
     * 
     * @author Ivo Machado
     */
    HashFile(std::string filename, std::string mode);
    /**
     * Cria um novo arquivo com o nome passado por parâmetro.
     * 
     * @author Ivo Machado
     */
    static HashFile Create(std::string filename);
    /**
     * Abre o arquivo filename com o modo passado por parâmetro.
     * 
     * @author Ivo Machado
     */
    static HashFile Open(std::string filename);
    /**
     * Número de blocos usados para o cabeçalho do arquivo
     * 
     * @author Ivo Machado
     */
    static const int NUMBER_BLOCKS_HEADER = 46;
    /** Número total de blocos alocados para fazer o hashing */
    static const int32_t NUMBER_BLOCKS{ (DiskBlock::AVAILABLE_SIZE * NUMBER_BLOCKS_HEADER - 4) * 8 };
    /** Campo do registro que será utilizado no hash, default para 0 */
    int m_fieldHashIndex{ 0 };

    /** Mapa de Bytes em memória dos blocos ocupados */
    Utils::BitMap m_blocksMap;
    /**
     * Escreve o cabeçalho do arquivo no disco
     * 
     * @author Ivo Machado
     */
    void writeHeaderToDisk();
    /**
     * Lê o cabeçalho do arquivo para a memória
     * 
     * @author Ivo Machado
     */
    void readHeaderFromDisk();
    /** Quantidade de blocos de overflow em memória */
    int32_t m_overflowBlocks{ 0 };
    /**
     * Procura pelo field no arquivo, recordFields é o esquema dos registros nele salvo.
     * 
     * @author Ivo Machado
     */
    std::pair<Record, int32_t> search(Field field, std::vector<Field> recordFields);
    /**
     * Compara todos os registros do bloco em blockIndex com o field passado por parâmetro
     * usando o fieldIndex para escolher o campo dentro de cada registro
     * 
     * @author Ivo Machado
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields, int fieldIndex);
    /**
     * Pega o registro de um bloco que tenha o campo de hash igual ao field passado
     * por parâmetro.
     * 
     * @author Ivo Machado
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields);
};
#endif // !HASHFILE_HPP
