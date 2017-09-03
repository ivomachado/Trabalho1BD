#ifndef RECORD_HPP
#define RECORD_HPP

#include "field.hpp"
#include <vector>

/**
 * \author Ivo Machado
 * 
 * Classe de abstração de um registro e seus campos, escreve e lê suas informações 
 * em buffer de bytes
 */
class Record {
    
public:
    std::vector<Field> m_data;
    /**
     * \author Ivo Machado
     * 
     * Escreve os dados do Record no buffer
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * \author Ivo Machado
     * 
     * Lê os dados do buffer para o Record
     */
    short readFromBuffer(char* buffer, short begin);
    /**
     * \author Ivo Machado
     * 
     * Cria um novo Recor com os dados do vector de fields recebido por parâmetro
     */
    Record(const std::vector<Field>& data);
    /**
     * \author Ivo Machado
     * 
     * Construtor padrão
     */
    Record();
};

#endif // !RECORD_HPP
