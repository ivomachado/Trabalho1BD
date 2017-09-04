#ifndef RECORD_HPP
#define RECORD_HPP

#include "field.hpp"
#include <vector>

/**
 * Classe de abstração de um registro e seus campos, escreve e lê suas informações 
 * em buffer de bytes
 * 
 * @author Ivo Machado
 */
class Record {
public:
    /** Vetor de Field do registro */
    std::vector<Field> m_data;
    /**
     * Escreve os dados do Record no buffer
     * 
     * @author Ivo Machado
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * Lê os dados do buffer para o Record
     * 
     * @author Ivo Machado
     */
    short readFromBuffer(char* buffer, short begin);
    /**
     * Cria um novo Record com os dados do vector de fields recebido por parâmetro
     * 
     * @author Ivo Machado
     */
    Record(const std::vector<Field>& data);
    /**
     * Construtor padrão
     * 
     * @author Ivo Machado
     */
    Record();
};

#endif // !RECORD_HPP
