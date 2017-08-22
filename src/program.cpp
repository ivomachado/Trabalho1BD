#include "program.hpp"
#include "article.hpp"
#include "field.hpp"
#include "record.hpp"
#include "hashfile.hpp"
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
    std::string firstBitMap;
    {
        HashFile hashfile = HashFile::Create("hash.bin");
        hashfile.m_blocksMap.set(3, true);
        hashfile.m_overflowBlocks = 3;
        firstBitMap = hashfile.m_blocksMap.m_data;
        hashfile.writeHeaderToDisk();
    }

    {
        HashFile hashfile = HashFile::Open("hash.bin");
    }
}
