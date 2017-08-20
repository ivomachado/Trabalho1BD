#include "block.hpp"
#include "catch.hpp"
#include "field.hpp"
#include "record.hpp"
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

TEST_CASE("Record escrevendo e lendo de buffer")
{
    vector<Field> vet;
    char buffer[4096];
    vet.push_back(Field::asInteger());
    vet.push_back(Field::asString(30));
    vet.push_back(Field::asString(22));
    vet.push_back(Field::asInteger());

    Record b(vet);

    vet[0].m_integer = 3234234;
    strcpy(vet[1].m_string, string("teste1").c_str());
    strcpy(vet[2].m_string, string("teste2").c_str());
    vet[3].m_integer = 323432;
    Record a(vet);

    REQUIRE(a.writeToBuffer(buffer, 0) == 60);
    REQUIRE(b.readFromBuffer(buffer, 0) == 60);

    REQUIRE(b.m_data[0].m_integer == 3234234);
    REQUIRE(strcmp(b.m_data[1].m_string, "teste1") == 0);
    REQUIRE(strcmp(b.m_data[2].m_string, "teste2") == 0);
    REQUIRE(b.m_data[3].m_integer == 323432);
}

TEST_CASE("Escrita e leitura de bloco")
{

    std::vector<Field> recordFields;
    recordFields.emplace_back(Field::asString(38));
    recordFields.emplace_back(Field::asInteger());
    recordFields.emplace_back(Field::asString(50));
    DiskBlock block(recordFields), block2(recordFields);

    Record a(recordFields), b(recordFields);

    strcpy(a.m_data[0].m_string, "bankai");
    a.m_data[1].m_integer = 324;
    strcpy(a.m_data[2].m_string, "shikai");

    strcpy(b.m_data[0].m_string, "bankai2");
    a.m_data[1].m_integer = 326;
    strcpy(b.m_data[2].m_string, "shikai2");

    block.m_records.push_back(a);
    block.m_records.push_back(b);

    SECTION("E/S em buffer")
    {
        REQUIRE(block2.m_bufferPos == block.m_bufferPos);
        block.writeToBuffer();
        for (int i = 0; i < DiskBlock::SIZE; i++) {
            block2.m_buffer[i] = block.m_buffer[i];
        }
        block2.readFromBuffer();
    }

    SECTION("E/S em Arquivo")
    {
        FILE* file = fopen("tmp.bin", "wb+");
        block.WriteToFile(file);
        fclose(file);

        FILE* file2 = fopen("tmp.bin", "rb");

        block2.ReadFromFile(file2);

        fclose(file2);

        remove("tmp.bin");
    }

    REQUIRE(block2.m_bufferPos == block.m_bufferPos);
    for (unsigned int i = 0; i < block2.m_records.size(); i++) {

        for (unsigned int j = 0; j < block2.m_records[i].m_data.size(); j++) {
            CAPTURE(block2.m_records[i].m_data[j]);
            REQUIRE(block.m_records[i].m_data[j] == block2.m_records[i].m_data[j]);
        }
    }
}
