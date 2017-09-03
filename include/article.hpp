#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "record.hpp"
#include <string>
#include <iostream>

/** 
 * Classe que concentra as operações centradas em artigos
 * \author Ivo Machado
 */
class Article {
public:
    int m_id;
    char m_title[301];
    int m_year;
    char m_authors[1025];
    int m_quotes;
    char m_updateTime[101];
    char m_snippet[1025];
    /**
     * \author Ivo Machado
     * 
     * Recebe um arquivo em formato csv e lê um registro dele, modificando o cursor do arquivo
     */
    Article(FILE* file);

    /**
     * \author Ivo Machado
     * 
     * Construtor padrão, existe apenas para podermos criar coleções de artigos
     */
    Article();

    /**
     * \author Ivo Machado
     * 
     * Retorna um Record com os dados do artigo
     */
    Record toRecord();

    /**
     * \author Ivo Machado
     * 
     * Muda os dados do artigo para os dados presentes no Record recebido por parâmetro
     */
    void fromRecord(Record rec);

    /**
     * \author Ivo Machado
     * 
     * Retorna um vector de Fields que contém os dados do artigo, este vetor 
     * pode ser usado como schema no DiskBlock e como parâmetro do search do 
     * HashFile
     */
    std::vector<Field> getFields();

    /**
     * \author Ivo Machado
     * 
     * Operação de impressão na saída padrão
     */
    friend std::ostream& operator<<(std::ostream& os, const Article& article)
    {
        os << "ID: " << article.m_id << '\n';
        os << "TITLE: " << article.m_title << '\n';
        os << "YEAR: " << article.m_year << '\n';
        os << "AUTHORS: " << article.m_authors << '\n';
        os << "QUOTES: " << article.m_quotes << '\n';
        os << "UPDATE_TIME: " << article.m_updateTime << '\n';
        os << "SNIPPET: " << article.m_snippet << '\n';
        return os;
    }
};

#endif
