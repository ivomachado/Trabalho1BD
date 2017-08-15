#include "article.hpp"
#include <iostream>
#include <cstring>

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
    strcpy(m_title, buffer);

    fscanf(file, intPattern.c_str(), &m_year);

    fscanf(file, stringPattern.c_str(), buffer);
    buffer[1024] = '\0';
    strcpy(m_authors, buffer);

    fscanf(file, intPattern.c_str(), &m_quotes);

    fscanf(file, stringPattern.c_str(), buffer);
    buffer[100] = '\0';
    strcpy(m_updateTime, buffer);

    fscanf(file, "%2000[^\n]\n", buffer);
    buffer[1024] = '\0';
    std::string snippetMiddleware(buffer);
    if(snippetMiddleware.size() > 0 && snippetMiddleware[0] == '"') {
        snippetMiddleware = snippetMiddleware.substr(1, snippetMiddleware.size() - 2);
    }
    strcpy(m_snippet, snippetMiddleware.c_str());
}

Article::Article() {

}
