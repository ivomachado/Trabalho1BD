#include "catch.hpp"
#include "field.hpp"
#include "hashfile.hpp"
#include "indexfile.hpp"
#include "record.hpp"
#include "utils.hpp"
#include <cstdint>
#include <limits>
#include <vector>

using namespace std;

TEST_CASE("Escrita de Header de HashFile")
{
    string firstBitMap;
    {
        HashFile hashfile = HashFile::Create("hash.bin");
        hashfile.m_blocksMap.set(3, true);
        hashfile.m_overflowBlocks = 3;
        firstBitMap = hashfile.m_blocksMap.m_data;
        hashfile.writeHeaderToDisk();
    }

    {
        HashFile hashfile = HashFile::Open("hash.bin");
        REQUIRE(hashfile.m_blocksMap.m_data == firstBitMap);
        REQUIRE(hashfile.m_overflowBlocks == 3);
    }
    remove("hash.bin");
}

TEST_CASE("Escrita de registro no HashFile")
{
    vector<Field> recordFields;
    recordFields.emplace_back(Field::asInteger());
    recordFields.emplace_back(Field::asString(DiskBlock::AVAILABLE_SIZE - 4));
    int32_t aIndex, bIndex, cIndex;
    int32_t eaIndex, ebIndex, ecIndex;
    HashFile hashfile = HashFile::Create("hash.bin");

    Record a(recordFields), b(recordFields), c(recordFields);
    a.m_data[1].m_string = string("bankai");
    b.m_data[1].m_string = string("shikai");
    c.m_data[1].m_string = string("cero");

    SECTION("Com colisão") {
        a.m_data[0].m_integer = 2;
        b.m_data[0].m_integer = 2;
        c.m_data[0].m_integer = 2;
        aIndex = hashfile.insert(a);
        bIndex = hashfile.insert(b);
        cIndex = hashfile.insert(c);
        eaIndex = 2;
        ebIndex = HashFile::NUMBER_BLOCKS + 0;
        ecIndex = HashFile::NUMBER_BLOCKS + 1;
        REQUIRE(hashfile.m_overflowBlocks == 2);
    }

    SECTION("Sem Colisão") {
        eaIndex = a.m_data[0].m_integer = 2;
        ebIndex = b.m_data[0].m_integer = 3;
        ecIndex = c.m_data[0].m_integer = 15340;
        aIndex = hashfile.insert(a);
        bIndex = hashfile.insert(b);
        cIndex = hashfile.insert(c);
        REQUIRE(hashfile.m_overflowBlocks == 0);
    }

    REQUIRE(aIndex == eaIndex);
    REQUIRE(bIndex == ebIndex);
    REQUIRE(cIndex == ecIndex);
    remove("hash.bin");
}

TEST_CASE("Teste massivo de Indexfile") {
    const int TESTS_NUMBER = 1500;
    vector<Field> fields(TESTS_NUMBER);
    for (int i = 0; i < TESTS_NUMBER; i++) {
        stringstream s;
        s << i;
        // fields[i] = Field::asString(s.str().c_str(), 128);
        fields[i] = Field::asInteger(i);
    }

    SECTION("Inserção") {
        IndexFile indexFile = IndexFile::Create("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            indexFile.insert(fields[i], i);
        }
    }

    SECTION("Busca") {
        IndexFile indexFile = IndexFile::Open("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            REQUIRE(indexFile.search(fields[i]) == i);
        }
        remove("index.bin");
    }
}

TEST_CASE("Teste massivo de HashFile")
{
    const int TESTS_NUMBER = 1000;
    vector<Record> records;
    for (int i = 0; i < TESTS_NUMBER; i++) {
        stringstream s;
        s << i;
        records.emplace_back(std::vector<Field>{ Field::asInteger(i), Field::asString(s.str().c_str(), 2048) });
        // fields[i] = Field::asInteger(i);
    }

    SECTION("Inserção")
    {
        HashFile hashFile = HashFile::Create("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            hashFile.insert(records[i]);
        }
    }

    SECTION("Busca")
    {
        HashFile hashFile = HashFile::Open("index.bin");
        for (int i = 0; i < TESTS_NUMBER; i++) {
            std::pair<Record, int32_t> searchResult = hashFile.search(records[i].m_data[0], records[i].m_data);
            REQUIRE(searchResult.first.m_data[0] == records[i].m_data[0]);
            REQUIRE(searchResult.first.m_data[1] == records[i].m_data[1]);
        }
    }
}
