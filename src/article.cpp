#include "article.hpp"
#include <iostream>

Article::Article(FILE* file)
{
    char buffer[2001];

    std::string intPattern = "\"%d\";";
    std::string stringPattern = "\"%2000[^\"]\";";
    std::string bigPattern = intPattern
        + "\"%300[^\"]\";" //300 limit
        + intPattern
        + "\"%1024[^\"]\";" //1024 limit
        + intPattern
        + "\"%100[^\"]\";" //100 limit
        + "%1024[^\n]\n"; //1024 limit
    fscanf(file, intPattern.c_str(), &m_id);

    fscanf(file, stringPattern.c_str(), buffer);
    buffer[300] = '\0';
    m_title = std::string(buffer);

    fscanf(file, intPattern.c_str(), &m_year);

    fscanf(file, stringPattern.c_str(), buffer);
    buffer[1024] = '\0';
    m_authors = std::string(buffer);
    
    fscanf(file, intPattern.c_str(), &m_quotes);

    fscanf(file, stringPattern.c_str(), buffer);
    buffer[100] = '\0';
    m_updateTime = std::string(buffer);

    fscanf(file, "%2000[^\n]\n", buffer);
    buffer[1024] = '\0';
    m_snippet = std::string(buffer);

    if(m_snippet.size() > 0 && m_snippet[0] == '"') {
        m_snippet = m_snippet.substr(1, m_snippet.size() - 2);
    }
}
