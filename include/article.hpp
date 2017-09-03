#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "record.hpp"
#include <string>
#include <iostream>

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
    void fromRecord(Record rec);

    std::vector<Field> getFields();

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
