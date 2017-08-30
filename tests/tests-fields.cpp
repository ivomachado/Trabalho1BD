#include "catch.hpp"
#include "field.hpp"

TEST_CASE("Testes de comparação de files")
{
    SECTION("Com string") {
        Field a = Field::asString("a", 30);
        Field b = Field::asString("b", 30);
        REQUIRE(a < b);
        REQUIRE(a <= a);
        REQUIRE(a == a);
        REQUIRE(b >= a);
        REQUIRE(b != a);
        REQUIRE(b > a);
    }

    SECTION("Com integer")
    {
        Field a = Field::asInteger(29);
        Field b = Field::asInteger(30);
        REQUIRE(a < b);
        REQUIRE(a <= a);
        REQUIRE(a == a);
        REQUIRE(b >= a);
        REQUIRE(b != a);
        REQUIRE(b > a);
    }
}
