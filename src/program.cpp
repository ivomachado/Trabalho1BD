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

void upload()
{
    string filename = "teste.csv";
    FILE* file = fopen(filename.c_str(), "r");
    HashFile dataFile = HashFile::Create("data.bin");
    IndexFile primaryIndex = IndexFile::Create("primary.index");
    IndexFile secondaryIndex = IndexFile::Create("secondary.index");
    while (!feof(file)) {
        Record rec = Article(file).toRecord();

        int32_t blockIndex = dataFile.insert(rec);
        primaryIndex.insert(rec.m_data[0], blockIndex);
        secondaryIndex.insert(rec.m_data[1], blockIndex);
    }
    fclose(file);
}

void findrec()
{
    HashFile dataFile = HashFile::Open("data.bin");
    Article article;
    int32_t id;
    cout << "Digite o id a ser buscado: ";
    cin >> id;
    std::pair<Record, int32_t> searchResult = dataFile.search(Field::asInteger(id), article.getFields());
    if(searchResult.first.m_data.size() > 0) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        article.fromRecord(searchResult.first);
        cout << article;
    }
}

int main()
{
    // upload();
    findrec();
}
