#include "board_print_html.h"
#include "board_print_plain.h"
#include "board_read.h"
#include <cstdlib>
#include <iostream>
using namespace std;

extern char board[8][8];

int main(int argc, char* argv[])
{
    system("clear");

    // ТЕСТ Вывода
    print_html_create();
    print_html(board, (char*)"TEST");
    print_consol(board, (char*)"TEST");
    board[1][3] = ' ';
    board[3][3] = 'P';
    print_html(board, (char*)"TEST2");
    print_consol(board, (char*)"TEST2");

    cout << endl
         << "Отобразить шахматную нотацию в браузере?" << endl
         << "            \x1b[1;32m[y]-да\x1b[0m     \x1b[1;31m[n]-нет\x1b[0m"
         << endl;

    if (getchar() == 'y') {
        print_html();
        system("sensible-browser bin/temp/chessviz.html");
    }
    return 0;
}