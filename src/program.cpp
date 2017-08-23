#include "program.hpp"
#include "article.hpp"
#include "field.hpp"
#include "hashfile.hpp"
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
    vector<Field> recordFields;
    recordFields.emplace_back(Field::asInteger());
    recordFields.emplace_back(Field::asString(DiskBlock::AVAILABLE_SIZE - 4));
    int32_t aIndex, bIndex, cIndex;

    Record a(recordFields), b(recordFields), c(recordFields);

    a.m_data[0].m_integer = 2;
    a.m_data[1].m_string = string("bankai");

    b.m_data[0].m_integer = 2;
    b.m_data[1].m_string = string("shikai");

    c.m_data[0].m_integer = 2;
    c.m_data[1].m_string = string("cero");

    string firstBitMap;
    {
        HashFile hashfile = HashFile::Create("hash.bin");
        aIndex = hashfile.insert(a);
        bIndex = hashfile.insert(b);
        cIndex = hashfile.insert(c);
    }
}
