#include "catch.hpp"
#include "utils.hpp"

TEST_CASE("Escrita de inteiro em buffer")
{
    int x = 0;
    char buffer[8];
    do {
        Utils::intToCharArray(x, buffer + 4);
        REQUIRE(x == Utils::charArrayToInt(buffer + 4));
        x++;
    } while (x != 0);
}
