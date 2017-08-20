#include "catch.hpp"
#include "utils.hpp"
#include <limits>

TEST_CASE("Escrita de inteiro em buffer", "[.][intConvetion]")
{
    int x = 0;
    char buffer[8];
    for (x = 0; x <= std::numeric_limits<int>::max()/1024; x++) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
    for (x = 0; x >= std::numeric_limits<int>::min()/1024; x--) {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
    }
}
