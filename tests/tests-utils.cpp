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
    const int testSize = 31;
    Utils::BitMap m(testSize + 1), mTestSize(testSize);
    REQUIRE(mTestSize.m_data.size() == 4);
    for (int i = 0; i < testSize; i++) {
        REQUIRE(!m.get(i));
    }

    for (int i = 0; i < testSize; i++) {
        m.set(i, i % 2);
    }

    for (int i = 0; i < testSize; i++) {
        REQUIRE(m.get(i) == i % 2);
    }
    std::vector<Field> fields{ Field::asString(1), Field::asString(1), Field::asString(2) };
    Record rec(fields);
    std::vector<Record> recs{rec};
    m.write(recs);
    Utils::BitMap m2(recs);

    REQUIRE(m.m_data == m2.m_data);

    for (int i = 0; i < testSize; i++) {
        REQUIRE(m.get(i) == m2.get(i));
    }
}
