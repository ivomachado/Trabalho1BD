#include "article.hpp"
#include "field.hpp"
#include <cstring>
#include <iostream>

void removeQuotes(char* buffer)
{
    std::string stringMiddleware(buffer);
    if (stringMiddleware.size() > 0 && stringMiddleware[0] == '"') {
        stringMiddleware = stringMiddleware.substr(1, stringMiddleware.size() - 2);
    }
    strcpy(buffer, stringMiddleware.c_str());
}

void readString(FILE* file, char* buffer, char* destination, int maxSize, bool acceptNewLines = true)
{
    buffer[0] = fgetc(file);
    if (buffer[0] == ';') {
        destination[0] = '\0';
        return;
    }
    for (int i = 1; i < 2000 && !feof(file); i++) {
        buffer[i] = fgetc(file);
        if(i == 4) {
            if (buffer[0] == 'N' && buffer[1] == 'U' && buffer[2] == 'L' && buffer[3] == 'L') {
                destination[0] = '\0';
                return;
            }
        }
        if(!acceptNewLines && buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
        if (buffer[i - 1] == '\"' && buffer[i] == ';') {
            buffer[i] = '\0';
            break;
        }
    }
    removeQuotes(buffer);
    buffer[maxSize] = '\0';
    strcpy(destination, buffer);
}

Article::Article(FILE* file)
{
    char buffer[2001];

    std::string intPattern = "\"%d\";";
    std::string stringPattern = "\"%2000[^\"]\";";
    fscanf(file, intPattern.c_str(), &m_id);

    readString(file, buffer, m_title, 300);

    fscanf(file, intPattern.c_str(), &m_year);

    readString(file, buffer, m_authors, 1024);
    
    fscanf(file, intPattern.c_str(), &m_quotes);
    
    readString(file, buffer, m_updateTime, 100);

    readString(file, buffer, m_snippet, 1024, false);
}

Article::Article()
{
}

std::vector<Field> Article::getFields()
{
    return std::vector<Field>{
        Field::asInteger(m_id),
        Field::asString(m_title, 300),
        Field::asInteger(m_year),
        Field::asString(m_authors, 1024),
        Field::asInteger(m_quotes),
        Field::asString(m_updateTime, 100),
        Field::asString(m_snippet, 1024),
    };
}

Record Article::toRecord()
{
    return Record(getFields());
}
