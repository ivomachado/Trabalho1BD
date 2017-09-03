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

void upload(string filename = "teste.csv")
{
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

void findrec(int32_t id)
{
    HashFile dataFile = HashFile::Open("data.bin");
    Article article;
    std::pair<Record, int32_t> searchResult = dataFile.search(Field::asInteger(id), article.getFields());
    if(searchResult.first.m_data.size() > 0) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        article.fromRecord(searchResult.first);
        cout << article;
    } else {
        cout << "Não foi encontrado artigos com este id\n";
    }
}

void seek1(int32_t id)
{
    HashFile dataFile = HashFile::Open("data.bin");
    IndexFile primaryIndex = IndexFile::Open("primary.index");
    Article article;
    std::pair<int32_t, int32_t> searchResult = primaryIndex.search(Field::asInteger(id));
    if (searchResult.first != -1) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        // article.fromRecord(searchResult.first);
        // cout << article;
    }
}

int main()
{
    cout << "As seguintes operações estão disponíveis:\n\n";
    cout << "upload <filename>   \t Cria um arquivo de dados e arquivos de índice primário e secundário\n";
    cout << "findrec <id>        \t Busca diretamente no arquivo de dados pelo id informado\n";
    cout << "seek1 <id>          \t Busca no índice primário pelo id informado\n";
    cout << "seek2 <title>       \t Busca no índice primário pelo titulo informado informado\n";
    cout << "exit                \t sai do programa\n\n\n";

    string command;
    while(true) {
        cout << "> ";
        cin >> command;
        if(command == "upload") {
            string filename;
            cin >> filename;
            upload(filename);
        } else if(command == "findrec") {
            int32_t id;
            cin >> id;
            findrec(id);
        }
    }
}

// int main() {
//     upload();
//     findrec(738289);
// }
