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
#include <sstream>

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
    const int TESTS_NUMBER = 23;
    vector<Field> fields(TESTS_NUMBER);
    for (int i = 0; i < TESTS_NUMBER; i++) {
        stringstream s;
        s << i;
        fields[i] = Field::asString(s.str().c_str(), 177);
        // fields[i] = Field::asInteger(i);
    }
    {
        IndexFile indexFile = IndexFile::Create("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            indexFile.insert(fields[i], i);
        }
    }

    {
        IndexFile indexFile = IndexFile::Open("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            indexFile.search(fields[i]);
        }
    }
}
