#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>
#include <cstdint>
#include <iostream>

enum class DataTypes { Invalid,
    Integer,
    String,
    ByteArray };

/**
 * \author Ivo Machado
 * 
 * Classe de abstração de campos atômicos com seus tipos de dados possíveis, 
 * escreve e lê suas informações em buffer de bytes
 */
class Field {
public:
    short m_maxSize;
    DataTypes m_type{ DataTypes::Invalid };
    Field(DataTypes type);
    Field() {}
    int32_t m_integer;
    std::string m_string{""};
    /** 
     * \author Ivo Machado
     * 
     * Cria um Field do tipo inteiro sem valor definido
     */
    static Field asInteger();
    /** 
     * \author Ivo Machado
     * 
     * Cria um Field do tipo inteiro com valor definido pelo parâmetro
     */
    static Field asInteger(int32_t value);
    /** 
     * \author Ivo Machado
     * 
     * Cria um Field do tipo string sem valor definido e com tamanho máximo
     */
    static Field asString(short maxSize);
    /** 
     * \author Ivo Machado
     * 
     * Cria um Field do tipo byteArray sem valor definido e com tamanho máximo
     */
    static Field asByteArray(short maxSize);
    /** 
     * \author Ivo Machado
     * 
     * Cria um Field do tipo string com valor definido pelo parâmetro e com tamanho máximo
     */
    static Field asString(const char* data, short maxSize);
    /** 
     * \author Ivo Machado
     * 
     * Retorna a posição a que a instância de Field pertence numa tabela hash de 
     * tamanho size.
     */
    int32_t hash(int32_t size);
    /** 
     * \author Ivo Machado
     * 
     * Retorna o tamanho que o campo ocupa no disco em bytes.
     */
    short size();
    /**
     * \author Ivo Machado
     * 
     * Escreve o valor do field no buffer a partir da posição begin
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * \author Ivo Machado
     * 
     * Lê o dado do field do buffer a partir da posição begin
     */
    short readFromBuffer(char* buffer, short begin);
    friend bool operator==(const Field& a, const Field& b);
    friend bool operator!=(const Field& a, const Field& b);
    friend bool operator>(const Field& a, const Field& b);
    friend bool operator<(const Field& a, const Field& b);
    friend bool operator<=(const Field& a, const Field& b);
    friend bool operator>=(const Field& a, const Field& b);
    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

#endif
