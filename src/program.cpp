#include "program.hpp"
#include "article.hpp"
#include "field.hpp"
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
    // Program::upload();
    vector<Field> vet;
    char buffer[4096];
    vet.push_back(Field::asInteger(3));
    vet.push_back(Field::asString(30));
    vet.push_back(Field::asString(22));
    vet.push_back(Field::asInteger(3));
    Record b(vet);
    vet[1].m_string = string("teste1");
    vet[2].m_string = string("teste2");
    Record a(vet);
    cout << a.writeToBuffer(buffer, 0) << '\n';
    b.readFromBuffer(buffer, 0);
    cout << b.m_data[0].m_integer << '\n';
    cout << b.m_data[1].m_string << '\n';
    cout << b.m_data[2].m_string << '\n';
    cout << b.m_data[3].m_integer << '\n';
    // fclose(file);
    return 0;
}
