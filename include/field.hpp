#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>
#include <cstdint>
#include <iostream>

/**
 * Tipos possíveis de Field
 * 
 * @author Ivo Machado
 */
enum class DataTypes { Invalid,
    Integer,
    String,
    ByteArray };

/**
 * Classe de abstração de campos atômicos com seus tipos de dados possíveis, 
 * escreve e lê suas informações em buffer de bytes
 * 
 * @author Ivo Machado
 */
class Field {
public:
    /** Tamanho máximo da string ou do bytearray */
    short m_maxSize;
    /** Tipo do Field, padrão é inválido */
    DataTypes m_type{ DataTypes::Invalid };
    /** Constrói com o type passado */
    Field(DataTypes type);
    /** Construtor padrão */
    Field() {}
    /** Guarda o inteiro */
    int32_t m_integer;
    /** Guarda a string e o bytarray */
    std::string m_string{""};
    /** 
     * Cria um Field do tipo inteiro sem valor definido
     * 
     * @author Ivo Machado
     */
    static Field asInteger();
    /** 
     * Cria um Field do tipo inteiro com valor definido pelo parâmetro
     * 
     * @author Ivo Machado
     */
    static Field asInteger(int32_t value);
    /** 
     * Cria um Field do tipo string sem valor definido e com tamanho máximo
     * 
     * @author Ivo Machado
     */
    static Field asString(short maxSize);
    /** 
     * Cria um Field do tipo byteArray sem valor definido e com tamanho máximo
     * 
     * @author Ivo Machado
     */
    static Field asByteArray(short maxSize);
    /** 
     * Cria um Field do tipo string com valor definido pelo parâmetro e com tamanho máximo
     * 
     * @author Ivo Machado
     */
    static Field asString(const char* data, short maxSize);
    /** 
     * Retorna a posição a que a instância de Field pertence numa tabela hash de 
     * tamanho size.
     * 
     * @author Ivo Machado
     */
    int32_t hash(int32_t size);
    /** 
     * Retorna o tamanho que o campo ocupa no disco em bytes.
     * 
     * @author Ivo Machado
     */
    short size();
    /**
     * Escreve o valor do field no buffer a partir da posição begin
     * 
     * @author Ivo Machado
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * Lê o dado do field do buffer a partir da posição begin
     * 
     * @author Ivo Machado
     */
    short readFromBuffer(char* buffer, short begin);
    /**
     * Operador de igual
     * 
     * @author Ivo Machado
     */
    friend bool operator==(const Field& a, const Field& b);
    /**
     * Operador de diferente
     * 
     * @author Ivo Machado
     */
    friend bool operator!=(const Field& a, const Field& b);
    /**
     * Operador de maior
     * 
     * @author Ivo Machado
     */
    friend bool operator>(const Field& a, const Field& b);
    /**
     * Operador de menor
     * 
     * @author Ivo Machado
     */
    friend bool operator<(const Field& a, const Field& b);
    /**
     * Operador de menor ou igual
     * 
     * @author Ivo Machado
     */
    friend bool operator<=(const Field& a, const Field& b);
    /**
     * Operador de maior ou igual
     * 
     * @author Ivo Machado
     */
    friend bool operator>=(const Field& a, const Field& b);
    /**
     * Operador de impressão de um field
     * 
     * @author Ivo Machado
     */
    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

#endif
