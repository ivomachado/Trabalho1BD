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
        REQUIRE(hashfile.m_overflowBlocks == 2);
        REQUIRE(aIndex == 2);
        REQUIRE(bIndex == HashFile::NUMBER_BLOCKS + 0);
        REQUIRE(cIndex == HashFile::NUMBER_BLOCKS + 1);
    }
    remove("hash.bin");
}

TEST_CASE("Escrita de registro no Indexfile") {
    Field field1 = Field::asString("1",1024);
    Field field2 = Field::asString("2",1024);
    Field field3 = Field::asString("3",1024);
    Field field4 = Field::asString("4",1024);
    Field field5 = Field::asString("5",1024);
    Field field6 = Field::asString("6",1024);
    Field field7 = Field::asString("7",1024);
    Field field8 = Field::asString("8",1024);
    {
        IndexFile indexFile = IndexFile::Create("index.bin");
        indexFile.insert(field1, 1);
        indexFile.insert(field2, 2);
        indexFile.insert(field3, 3);
        indexFile.insert(field4, 4);
        indexFile.insert(field5, 5);
        indexFile.insert(field6, 6);
        indexFile.insert(field7, 7);
        indexFile.insert(field8, 8);
    }

    {
        IndexFile indexFile = IndexFile::Open("index.bin");
        REQUIRE(indexFile.search(field1) == 1);
        REQUIRE(indexFile.search(field2) == 2);
        REQUIRE(indexFile.search(field3) == 3);
        REQUIRE(indexFile.search(field4) == 4);
        REQUIRE(indexFile.search(field5) == 5);
        REQUIRE(indexFile.search(field6) == 6);
        REQUIRE(indexFile.search(field7) == 7);
        REQUIRE(indexFile.search(field8) == 8);
    }
}
