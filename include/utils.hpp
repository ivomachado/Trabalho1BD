#ifndef UTILS_HPP
#define UTILS_HPP

#include "block.hpp"
#include "record.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * \author Ivo Machado
 * 
 * Contém coisas não diretamente ligadas ao problema mas que são úteis
 */
namespace Utils {

/**
 * \author Ivo Machado
 * 
 * Escreve o vector m_data no buffer
 */
template <typename T>
short writeVectorToBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto field : m_data) {
        begin = field.writeToBuffer(buffer, begin);
    }
    return begin;
}

/**
 * \author Ivo Machado
 * 
 * Lê o vector m_data do buffer
 */
template <typename T>
short readVectorFromBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto& field : m_data) {
        begin = field.readFromBuffer(buffer, begin);
    }
    return begin;
}

/**
 * \author Ivo Machado
 * 
 * Converte o value para 4 char e os escreve em buffer
 */
inline void intToCharArray(int32_t value, char* buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

/**
 * \author Ivo Machado
 * 
 * converte 4 char para inteiro
 */
inline int32_t charArrayToInt(char* buffer)
{
    int32_t num = ((buffer[0] & 0xFF) << 24) | ((buffer[1] & 0xFF) << 16) | ((buffer[2] & 0xFF) << 8) | (0xFF & (buffer[3]));
    return num;
}

/**
 * \author Ivo Machado
 * 
 * Abstrai um mapa de bits para facilitar as operações de ligar e desligar bits
 */
class BitMap {
public:
    std::string m_data{ "" };
    BitMap()
        : BitMap(0)
    {
    }

    /**
     * \author Ivo Machado
     * 
     * Cria um bitmap com os dados dos ByteArray dos blocos passados por parâmetro
     */
    BitMap(const std::vector<DiskBlock>& data)
    {
        for (auto& block : data) {
            for (auto& rec : block.m_records) {
                for (auto& field : rec.m_data) {
                    if (field.m_type == DataTypes::ByteArray) {
                        for (int i = 0; i < field.m_maxSize; i++) {
                            m_data += field.m_string[i];
                        }
                    }
                }
            }
        }
    }

    /**
     * \author Ivo Machado
     * 
     * Cria um bitmap com capacidade no primeiro múltiplo de 8 maior ou igual ao tamanho pedido
     */
    BitMap(int32_t size)
    {
        if (size % 8 == 0) {
            size /= 8;
        } else {
            size /= 8;
            size++;
        }
        m_data = std::string(size, static_cast<char>(0));
    }

    /**
     * \author Ivo Machado
     * 
     * Retorna o booleano da posição informada
     */
    bool get(int32_t pos)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        return (m_data[charIndex] & (1 << bitIndex)) > 0;
    }

    /**
     * \author Ivo Machado
     * 
     * Atribui o valor passado à posição pedida
     */
    void set(int32_t pos, bool value)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        m_data[charIndex] = value ? m_data[charIndex] | (1 << bitIndex) : m_data[charIndex] & (~(1 << bitIndex));
    }

    /**
     * \author Ivo Machado
     * 
     * Escreve o bitmap divido nos atributos ByteArray de vários blocos
     */
    void write(std::vector<DiskBlock>& data)
    {
        int pos = 0;
        for (auto& block : data) {
            for (auto& rec : block.m_records) {
                for (auto& field : rec.m_data) {
                    if (field.m_type == DataTypes::ByteArray) {
                        for (int i = 0; i < field.m_maxSize; i++) {
                            field.m_string[i] = m_data[pos + i];
                        }
                        pos += field.m_maxSize;
                    }
                }
            }
        }
    }
};

/**
 * \author Ivo Machado
 * 
 * Calcula o offset em bytes do bloco pedido considerando o overhead de cabeçalho do arquivo
 */
inline int64_t calcBlockOffset(int32_t blockIndex, int32_t headerOverhead = 1)
{
    return (static_cast<int64_t>(blockIndex) + static_cast<int64_t>(headerOverhead)) * static_cast<int64_t>(DiskBlock::SIZE);
}
}

#endif // !UTILS_HPP
