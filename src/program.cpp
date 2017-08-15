#include "program.hpp"
#include "article.hpp"
#include "datatype.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
    // Program::upload();
    databaseTypes::Integer mySecondInteger;
    char buffer[Program::BLOCK_SIZE];
    FILE* file = fopen("my.bin", "rb");
    // myInteger.writeToBuffer(buffer, 0);
    fread(buffer, Program::BLOCK_SIZE * sizeof(char), 1, file);
    // fwrite(buffer, Program::BLOCK_SIZE * sizeof(char), 1, file);
    mySecondInteger.readFromBuffer(buffer, 0);
    cout << mySecondInteger.m_data << '\n';
    fclose(file);
    return 0;
}
