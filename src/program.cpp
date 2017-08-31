#include "program.hpp"
#include "article.hpp"
#include "field.hpp"
#include "hashfile.hpp"
#include "indexfile.hpp"
#include "record.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

void Program::upload()
{
    string filename = "teste.csv";
    // cout << "Digite o caminho do arquivo:\n";
    // cin >> filename;
    vector<Article> myArticles;
    FILE* file = fopen(filename.c_str(), "r");

    while (!feof(file)) {
        myArticles.emplace_back(file);
    }
    fclose(file);
}

int main()
{
    Field field1 = Field::asString("1", 1024);
    Field field2 = Field::asString("2", 1024);
    Field field3 = Field::asString("3", 1024);
    Field field4 = Field::asString("4", 1024);
    Field field5 = Field::asString("5", 1024);
    Field field6 = Field::asString("6", 1024);
    Field field7 = Field::asString("7", 1024);
    Field field8 = Field::asString("8", 1024);
    {
        IndexFile indexFile = IndexFile::Create("index.bin");
        indexFile.insert(field1, 1);
        indexFile.insert(field2, 2);
        indexFile.insert(field3, 3);
        indexFile.insert(field4, 4);
        indexFile.insert(field5, 5);
        indexFile.insert(field6, 6);
        indexFile.insert(field7, 7);
        indexFile.insert(field8, 8);
    }

    {
        IndexFile indexFile = IndexFile::Open("index.bin");
        indexFile.search(field1);
        indexFile.search(field2);
        indexFile.search(field3);
        indexFile.search(field4);
        indexFile.search(field5);
        indexFile.search(field6);
        indexFile.search(field7);
        indexFile.search(field8);
    }
}
