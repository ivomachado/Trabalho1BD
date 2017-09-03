#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "record.hpp"
#include <cstdint>
#include <cstdio>
#include <vector>

/**
 * \author Ivo Machado
 * 
 * Classe responsável por realizar abstração de um bloco, todos os acessos de leitura e escrita ao disco são feitos por ela
 */
class DiskBlock {
public:
    DiskBlock(std::vector<Field>& recordFields);
    /**
     * \author Ivo Machado
     * 
     * Lê um bloco do disco de um arquivo previamente posicionado no endereço certo para um vetor de char.
     * Depois com base na quantidade de registros no bloco, faz o parse para registros em memória. */
    void readFromFile(FILE* file);
    /**
     * \author Ivo Machado
     * 
     * Faz o parse dos registros em memória para o buffer
     */
    void writeToFile(FILE* file);
    /**
     * \author Ivo Machado
     * 
     * Tamanho do bloco
     */
    static const int SIZE = 4096;
    /**
     * \author Ivo Machado
     * 
     * Tamanho disponível considerando o espaço ocupado pelo cabeçalho do bloco
     */
    static const int AVAILABLE_SIZE = 4088; //Menos 2 inteiros
    std::vector<Record> m_records;
    short m_recordSize{ 0 };
    /**
     * \author Ivo Machado
     * 
     * Buffer de char que para onde é lido o bloco do disco e que é escrito no disco
     */
    char m_buffer[DiskBlock::SIZE];
    /**
     * \author Ivo Machado
     * 
     * Vetor dos registros em memória
     */
    std::vector<Field> m_recordFields;
    /**
     * \author Ivo Machado
     * 
     * Cabeçalho do bloco
     */
    Record m_header;
    /**
     * \author Ivo Machado
     * 
     * Posição do buffer para fazer a próxima escrita/leitura
     */
    short m_bufferPos{ 0 };
    /**
     * \author Ivo Machado
     * 
     * Escreve o cabeçalho do bloco e todos seus registros no buffer
     */
    void writeToBuffer();
    /**
     * \author Ivo Machado
     * 
     * Lê o cabeçalho do bloco e todos seus registros do buffer
     */
    void readFromBuffer();
    /**
     * \author Ivo Machado
     * 
     * Tenta inserir um novo registro no bloco caso o registro caiba no bloco
     */
    bool insert(const Record& record);
    /**
     * \author Ivo Machado
     * 
     * Informa se ainda cabe mais um registro no bloco
     */
    bool fitOneMoreRecord();
};

#endif // !BLOCK_HPP
