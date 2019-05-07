#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "../src/checks.h"
#include "../thirdparty/catch.hpp"
#include <string>
using namespace std;
TEST_CASE("СheckStr input error", "[checkStr]")
{
    REQUIRE(checkStr((string) "error") == 0);
    REQUIRE(checkStr((string) "2. e2-e3 a7-a6") == 1);
    REQUIRE(checkStr((string) "2. e9-e3 a7-a6") == 1);
}
TEST_CASE("СheckStr success", "[checkStr]")
{
    REQUIRE(checkStr((string) "1. a2-a3 c7-c6") == 0);
    REQUIRE(checkStr((string) "2. d2-d4 e5xd4") == 0);
    REQUIRE(checkStr((string) "3. c2-c3 f7-f5") == 0);
}

TEST_CASE("checkPawn input error", "[checkPawn]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkPawn(boardc, (string) "a5-a6", 0) == 1);
    REQUIRE(checkPawn(boardc, (string) "a7-b5", 1) == 1);
    REQUIRE(checkPawn(boardc, (string) "a2xa1", 0) == 1);
}

TEST_CASE("CheckPawn success", "[checkPawn]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', ' ', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', 'P', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'p', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkPawn(boardc, (string) "b4xa5", 0) == 0);
    REQUIRE(checkPawn(boardc, (string) "c7-c5", 1) == 0);
    REQUIRE(checkPawn(boardc, (string) "a5-a6", 0) == 0);
}

TEST_CASE("checkKnight input error", "[checkKnight]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkKnight(boardc, (string) "Nb1-a6", 0) == 1);
    REQUIRE(checkKnight(boardc, (string) "Na2-a6", 1) == 1);
    REQUIRE(checkKnight(boardc, (string) "Nb1xa3", 0) == 1);
}

TEST_CASE("checkKnight success", "[checkKnight]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', 'p', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'p', ' ', 'p', 'p', 'p', 'p', 'p', 'p'},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkKnight(boardc, (string) "Nb1-a3", 0) == 0);
    REQUIRE(checkKnight(boardc, (string) "Nb8-c6", 1) == 0);
    REQUIRE(checkKnight(boardc, (string) "Na3xb5", 0) == 0);
}

TEST_CASE("checkBishop input error", "[checkBishop]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkBishop(boardc, (string) "Bc1-c6", 0) == 1);
    REQUIRE(checkBishop(boardc, (string) "Bc8-a6", 1) == 1);
    REQUIRE(checkBishop(boardc, (string) "Bc1xc8", 0) == 1);
}

TEST_CASE("checkBishop success", "[checkBishop]")
{
    char boardc[8][8] = {{' ', ' ', 'B', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', 'B', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', 'b', ' ', ' ', 'b', ' ', ' '}};
    REQUIRE(checkBishop(boardc, (string) "Bc1-a3", 0) == 0);
    REQUIRE(checkBishop(boardc, (string) "Bf8xa3", 1) == 0);
    REQUIRE(checkBishop(boardc, (string) "Bd3-c4", 0) == 0);
}

TEST_CASE("checkRook input error", "[checkRook]")
{
    char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    REQUIRE(checkRook(boardc, (string) "Ra1-a2", 0) == 1);
    REQUIRE(checkRook(boardc, (string) "Ra8-e6", 1) == 1);
    REQUIRE(checkRook(boardc, (string) "Ra8xc8", 0) == 1);
}

TEST_CASE("checkRook success", "[checkRook]")
{
    char boardc[8][8] = {{'R', ' ', 'B', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', 'B', ' ', 'R', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', 'r', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', 'b', ' ', ' ', 'b', ' ', 'r'}};
    REQUIRE(checkRook(boardc, (string) "Ra1-a3", 0) == 0);
    REQUIRE(checkRook(boardc, (string) "Rc5xc1", 1) == 0);
    REQUIRE(checkRook(boardc, (string) "Ra3-c3", 0) == 0);
}