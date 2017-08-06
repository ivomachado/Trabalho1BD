#include "article.hpp"
#include <iostream>

Article::Article(const char* csvEntry)
{
    char title[301], authors[1025], updateTime[101], snippet[1025];
    int id, year, quotes;

    std::string intPattern = "\"%d\";";
    std::string bigPattern = intPattern
        + "\"%300[^;\"]\";" //300 limit
        + intPattern
        + "\"%1024[^;\"]\";" //1024 limit
        + intPattern
        + "\"%100[^;\"]\";" //100 limit
        + "\"%1024[^;\"]\";"; //1024 limit

    sscanf(csvEntry, bigPattern.c_str(),
        &id,
        title,
        &year,
        authors,
        &quotes,
        updateTime,
        snippet);

    m_id = id;
    m_title = std::string(title);
    m_year = year;
    m_authors = std::string(authors);
    m_quotes = quotes;
    m_updateTime = std::string(updateTime);
    m_snippet = std::string(snippet);
}
