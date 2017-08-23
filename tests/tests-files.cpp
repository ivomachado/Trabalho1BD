#include "catch.hpp"
#include "field.hpp"
#include "hashfile.hpp"
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
}
