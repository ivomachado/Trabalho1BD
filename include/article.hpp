#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <string>

/** 
 * Artigos
 * \author Ivo Machado
 */
class Article {
public:
    int m_id;
    std::string m_title;
    int m_year;
    std::string m_authors;
    int m_quotes;
    std::string m_updateTime;
    std::string m_snippet;
    /**
     * Recebe uma linha de um CSV para criar um artigo com as informações 
     * contidas nesta linha
     */
    Article(const char* csvEntry);

    /**
     * Construtor padrão
     */
    Article();
};

#endif
