#include "catch.hpp"
#include "utils.hpp"
#include <limits>
#include <cstdint>

TEST_CASE("Escrita de inteiro em buffer", "[.][intConvetion]")
{
    int32_t x = 0;
    char buffer[8];
    for (x = 0; x <= std::numeric_limits<int32_t>::max()/1024; x++) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
    for (x = 0; x >= std::numeric_limits<int32_t>::min()/1024; x--) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
}
