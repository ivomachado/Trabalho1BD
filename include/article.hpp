#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "record.hpp"
#include <string>
#include <iostream>

/** 
 * Class that centralizes operations focused on articles
 * 
 * @author Juliana Castro
 */
class Article {
public:
    /** Article ID */
    int m_id;
    /** Article Title */
    char m_title[301];
    /** Article Year */
    int m_year;
    /** Article Authors */
    char m_authors[1025];
    /** Article Quotes */
    int m_quotes;
    /** Article Update Time */
    char m_updateTime[101];
    /** Article Snippet */
    char m_snippet[1025];
    /**
     * Receives a csv file and reads a record from it, modifying the file cursor
     * 
     * @author Juliana Castro
     */
    Article(FILE* file);

    /**
     * Default constructor, exists only to allow creating collections of articles
     * 
     * @author Juliana Castro
     */
    Article();

    /**
     * Returns a Record with the article's data
     * 
     * @author Juliana Castro
     */
    Record toRecord();

    /**
     * Changes the article's data to the data present in the Record received as a parameter
     * 
     * @author Juliana Castro
     */
    void fromRecord(Record rec);

    /**
     * Returns a vector of Fields containing the article's data. This vector 
     * can be used as a schema in DiskBlock and as a parameter for HashFile's 
     * search
     * 
     * @author Juliana Castro
     */
    std::vector<Field> getFields();

    /**
     * Standard output print operation
     * 
     * @author Juliana Castro
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