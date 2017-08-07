#include "program.hpp"
#include "article.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void Program::upload()
{
    string filename = "artigo.csv";
    cout << "Digite o caminho do arquivo:\n";
    cin >> filename;
    vector<Article> myArticles;
    FILE* file = fopen(filename.c_str(), "r");
    char line[Program::maxChar];

    while (fgets(line, Program::maxChar, file) != NULL) {
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
