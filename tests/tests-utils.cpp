#include "catch.hpp"
#include "field.hpp"
#include "record.hpp"
#include "utils.hpp"
#include <cstdint>
#include <limits>
#include <vector>

TEST_CASE("Escrita de inteiro em buffer", "[.][intConvetion]")
{
    int32_t x = 0;
    char buffer[8];
    for (x = 0; x <= std::numeric_limits<int32_t>::max() / 1024; x++) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
    for (x = 0; x >= std::numeric_limits<int32_t>::min() / 1024; x--) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
}

TEST_CASE("Operações com bitmap")
{
    const int testSize = 64;
    Utils::BitMap m(testSize), mTestSize(testSize - 1);
    REQUIRE(mTestSize.m_data.size() == 8);
    for (int i = 0; i < testSize; i++) {
        REQUIRE(!m.get(i));
    }

    for (int i = 0; i < testSize; i++) {
        m.set(i, i % 2);
    }

    for (int i = 0; i < testSize; i++) {
        REQUIRE(m.get(i) == i % 2);
    }
    std::vector<Field> fields{
        Field::asInteger(), Field::asByteArray(1), Field::asByteArray(1), Field::asInteger(),
    };
    // m.m_data = "data";
    Record rec(fields);
    std::vector<DiskBlock> blocks;
    for (int i = 0; i < 4; i++) {
        blocks.emplace_back(fields);
        blocks.back().insert(rec);
    }
    m.write(blocks);
    Utils::BitMap m2(blocks);

    REQUIRE(m.m_data == m2.m_data);

    for (int i = 0; i < testSize; i++) {
        REQUIRE(m.get(i) == m2.get(i));
    }
}
