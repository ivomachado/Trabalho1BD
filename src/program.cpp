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
#include <sstream>
#include <vector>

using namespace std;

void Program::upload(string filename)
{
    FILE* file = fopen(filename.c_str(), "r");
    HashFile dataFile = HashFile::Create("data.bin");
    IndexFile primaryIndex = IndexFile::Create("primary.index");
    IndexFile secondaryIndex = IndexFile::Create("secondary.index");
    int totalInserted = 0;
    while (!feof(file)) {
        Record rec = Article(file).toRecord();
        int32_t blockIndex = dataFile.insert(rec);
        primaryIndex.insert(rec.m_data[0], blockIndex);
        secondaryIndex.insert(rec.m_data[1], blockIndex);
        totalInserted++;
        if (totalInserted % 1000 == 0) {
            cout << totalInserted << " registros inseridos\n";
        }
    }
    fclose(file);
}

void Program::findrec(int32_t id)
{
    HashFile dataFile = HashFile::Open("data.bin");
    Article article;
    std::pair<Record, int32_t> searchResult = dataFile.search(Field::asInteger(id), article.getFields());
    if (searchResult.first.m_data.size() > 0) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        fseek(dataFile.m_file, 0, SEEK_END);
        cout << "Há " << ftell(dataFile.m_file) / DiskBlock::SIZE << " blocos no arquivo de índice primário\n\n";
        article.fromRecord(searchResult.first);
        cout << article << '\n';
    } else {
        cout << "Não foi encontrado artigos com este id\n\n";
    }
}

void Program::seek1(int32_t id)
{
    HashFile dataFile = HashFile::Open("data.bin");
    IndexFile primaryIndex = IndexFile::Open("primary.index");
    Article article;
    std::pair<int32_t, int32_t> searchResult = primaryIndex.search(Field::asInteger(id));
    if (searchResult.first != -1) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        cout << "Há " << primaryIndex.m_locatedBlocks + 1 << " blocos no arquivo de índice primário\n\n";
        Record rec = dataFile.getFromBlock(searchResult.first, Field::asInteger(id), article.getFields());
        article.fromRecord(rec);
        cout << article << '\n';
    } else {
        cout << "Não foi encontrado artigos com este id\n\n";
    }
}

void Program::seek2(string title)
{
    HashFile dataFile = HashFile::Open("data.bin");
    IndexFile secondaryIndex = IndexFile::Open("secondary.index");
    Article article;
    std::pair<int32_t, int32_t> searchResult = secondaryIndex.search(Field::asString(title.c_str(), 300));
    if (searchResult.first != -1) {
        cout << "Foi necessário acessar " << searchResult.second << " blocos para encontrar o registro" << '\n';
        cout << "Há " << secondaryIndex.m_locatedBlocks + 1 << " blocos no arquivo de índice secundário\n\n";
        Record rec = dataFile.getFromBlock(searchResult.first, Field::asString(title.c_str(), 300), article.getFields(), 1);
        article.fromRecord(rec);
        cout << article << '\n';
    } else {
        cout << "Não foi encontrado artigos com este id\n\n";
    }
}

void Program::help()
{
    cout << "As seguintes operações estão disponíveis:\n\n";
    cout << "upload <filename>   \t Cria um arquivo de dados e arquivos de índice primário e secundário\n";
    cout << "findrec <id>        \t Busca diretamente no arquivo de dados pelo id informado\n";
    cout << "seek1 <id>          \t Busca no índice primário pelo id informado\n";
    cout << "seek2 <title>       \t Busca no índice primário pelo titulo informado informado\n";
    cout << "help                \t Imprime esta mensagem de ajuda\n";
    cout << "exit                \t sai do programa\n\n\n";
}

int main()
{
    Program::help();

    string command;
    while (true) {
        cout << "> ";
        cin >> command;
        if (command == "upload") {
            string filename;
            cin >> filename;
            Program::upload(filename);
            cout << "Upload completo!!\n";
        } else if (command == "findrec") {
            int32_t id;
            cin >> id;
            Program::findrec(id);
            cout << '\n';
        } else if (command == "seek1") {
            int32_t id;
            cin >> id;
            Program::seek1(id);
            cout << '\n';
        } else if (command == "seek2") {
            char title[301];
            cin.getline(title, 301);
            Program::seek2(string(title + 1));
            cout << '\n';
        } else if (command == "help") {
            Program::help();
        } else if (command == "exit") {
            return 0;
        }
    }
}
