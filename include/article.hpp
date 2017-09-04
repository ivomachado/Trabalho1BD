#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "record.hpp"
#include <string>
#include <iostream>

/** 
 * Classe que concentra as operações centradas em artigos
 * 
 * \author Juliana Castro
 */
class Article {
public:
    /** Id do artigo */
    int m_id;
    /** Title do artigo */
    char m_title[301];
    /** Year do artigo */
    int m_year;
    /** Authors do artigo */
    char m_authors[1025];
    /** Quotes do artigo */
    int m_quotes;
    /** Update Time do artigo */
    char m_updateTime[101];
    /** Snippet do artigo */
    char m_snippet[1025];
    /**
     * Recebe um arquivo em formato csv e lê um registro dele, modificando o cursor do arquivo
     * 
     * \author Juliana Castro
     */
    Article(FILE* file);

    /**
     * Construtor padrão, existe apenas para podermos criar coleções de artigos
     * 
     * \author Juliana Castro
     */
    Article();

    /**
     * Retorna um Record com os dados do artigo
     * 
     * \author Juliana Castro
     */
    Record toRecord();

    /**
     * Muda os dados do artigo para os dados presentes no Record recebido por parâmetro
     * 
     * \author Juliana Castro
     */
    void fromRecord(Record rec);

    /**
     * Retorna um vector de Fields que contém os dados do artigo, este vetor 
     * pode ser usado como schema no DiskBlock e como parâmetro do search do 
     * HashFile
     * 
     * \author Juliana Castro
     */
    std::vector<Field> getFields();

    /**
     * Operação de impressão na saída padrão
     * 
     * \author Juliana Castro
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
