#include "board_print_plain.h"
#include <iostream>
using namespace std;

extern char board[8][8];

int main(int argc, char* argv[])
{
    print_consol(board);
    return 0;
}