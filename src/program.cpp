#include "program.hpp"
#include "article.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

const int maxChar = 2001; /* A maior linha do arquivo possui 1545 caracteres*/

using namespace std;

/** Função que lê da entrada padrão o nome de um arquivo, lê o arquivo e popula
 * O banco de dados com os dados do arquivo.
 */
void Program::upload()
{
    string filename = "artigo.csv";
    cout << "Digite o caminho do arquivo:\n";
    cin >> filename;
    vector<Article> myArticles;
    FILE* file = fopen(filename.c_str(), "r");
    char line[maxChar];

    while (fgets(line, maxChar, file) != NULL) {
        myArticles.emplace_back(line);
    }
    cout << myArticles.size() << '\n';
    fclose(file);
}

int main()
{
    Program::upload();
    return 0;
}
