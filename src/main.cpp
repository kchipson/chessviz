#include "board_print_plain.h"
#include <cstdlib>
using namespace std;

extern char board[8][8];

int main(int argc, char* argv[])
{
    system("clear");print_consol(board); return 0;
}