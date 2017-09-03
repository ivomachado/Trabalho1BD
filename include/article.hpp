#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "record.hpp"
#include <string>

/** 
 * Artigos
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
     * Recebe um arquivo em formato csv e lê um registro dele, modificando o cursor do arquivo
     */
    Article(FILE* file);

    /**
     * Construtor padrão
     */
    Article();

    Record toRecord();

    std::vector<Field> getFields();
};

#endif
