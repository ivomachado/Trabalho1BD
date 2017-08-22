#include "catch.hpp"
#include "field.hpp"
#include "hashfile.hpp"
#include "record.hpp"
#include "utils.hpp"
#include <cstdint>
#include <limits>
#include <vector>

TEST_CASE("Escrita de Header de HashFile")
{
    std::string firstBitMap;
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
