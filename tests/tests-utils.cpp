#include "catch.hpp"
#include "utils.hpp"
#include <cstdint>
#include <limits>

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
    Utils::BitMap m(testSize);
    for (int i = 0; i < testSize; i++) {
        REQUIRE(!m.get(i));
    }

    for (int i = 0; i < testSize; i++) {
        m.set(i, i % 2);
    }

    for (int i = 0; i < testSize; i++) {
        REQUIRE(m.get(i) == i % 2);
    }
}
