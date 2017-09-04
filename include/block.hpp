#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "record.hpp"
#include <cstdint>
#include <cstdio>
#include <vector>

/**
 * Classe responsável por realizar abstração de um bloco, todos os acessos de leitura e escrita ao disco são feitos por ela
 * 
 * \author Ivo Machado
 */
class DiskBlock {
public:
    DiskBlock(std::vector<Field>& recordFields);
    /**
     * Lê um bloco do disco de um arquivo previamente posicionado no endereço certo para um vetor de char.
     * Depois com base na quantidade de registros no bloco, faz o parse para registros em memória.
     * 
     * \author Ivo Machado
     */
    void readFromFile(FILE* file);
    /**
     * Faz o parse dos registros em memória para o buffer
     * 
     * \author Ivo Machado
     */
    void writeToFile(FILE* file);
    /**
     * Tamanho do bloco
     * 
     * \author Ivo Machado
     */
    static const int SIZE = 4096;
    /** Tamanho disponível considerando o espaço ocupado pelo cabeçalho do bloco */
    static const int AVAILABLE_SIZE = 4088; //Menos 2 inteiros
    /** Vetor de registros do bloco */
    std::vector<Record> m_records;
    /** Tamanho de um registro */
    short m_recordSize{ 0 };
    /**
     * Buffer de char que para onde é lido o bloco do disco e que é escrito no disco
     * 
     * \author Ivo Machado
     */
    char m_buffer[DiskBlock::SIZE];
    /**
     * Vetor dos registros em memória
     * 
     * \author Ivo Machado
     */
    std::vector<Field> m_recordFields;
    /**
     * Cabeçalho do bloco
     * 
     * \author Ivo Machado
     */
    Record m_header;
    /**
     * Posição do buffer para fazer a próxima escrita/leitura
     * 
     * \author Ivo Machado
     */
    short m_bufferPos{ 0 };
    /**
     * Escreve o cabeçalho do bloco e todos seus registros no buffer
     * 
     * \author Ivo Machado
     */
    void writeToBuffer();
    /**
     * Lê o cabeçalho do bloco e todos seus registros do buffer
     * 
     * \author Ivo Machado
     */
    void readFromBuffer();
    /**
     * Tenta inserir um novo registro no bloco caso o registro caiba no bloco
     * 
     * \author Ivo Machado
     */
    bool insert(const Record& record);
    /**
     * Informa se ainda cabe mais um registro no bloco
     * 
     * \author Ivo Machado
     */
    bool fitOneMoreRecord();
};

#endif // !BLOCK_HPP
