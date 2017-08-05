#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <ctime>
#include <string>

/** 
 * Artigos
 * \author Ivo Machado
 */
class Article {
    int m_id;
    std::string m_title;
    int m_year;
    std::string m_authors;
    int m_quotesQtde;
    tm updateTime;
    std::string snippet;
};

#endif
