#include "board.h"
#include "board_print_html.h"
#include "board_read.h"
#include "checks.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;

char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

void checkFlag(string str)
{
    if ((str == string("--browser")) || (str == string("-b")))
        print_html_create();

    if (!((str == string("--console")) || (str == string("-c"))
          || (str == string("--browser")) || (str == string("-b")))) {
        cout << " Неверный флаг, допустимые флаги: " << endl
             << "\x1b[1;35m• <--console/-c> - для вывода нотации в консоль"
             << endl
             << "• <--browser/-b> - для вывода нотации в html-файл\x1b[0m"
             << endl;
        exit(0);
    }
}
int main(int argc, char* argv[])
{
    switch (argc) {
    case 1:
        cout << "\x1b[1;35m Для запуска программы необходимо обязательно "
                "указать один из флагов:"
             << endl
             << "• <--console/-c> - для вывода нотации в консоль" << endl
             << "• <--browser/-b> - для вывода нотации в html-файл" << endl
             << "*Опционально: <Путь к файлу для считывания нотации>"
             << "\x1b[0m" << endl;
        return 1;
    case 2:
        checkFlag(string(argv[1]));
        read();
        break;
    case 3:
        checkFlag(string(argv[1]));
        read_file(argv[2]);
        break;
    default:
        cout << "\x1b[1;31mОШИБКА! Приложение может принимать на вход только "
                "один параметр(<флаг, указывающий параметр вывода>) или два "
                "параметра(<флаг, указывающий параметр вывода> <файл с игровой "
                "партией>)!\x1b[0m"
             << endl;
        return 1;
        break;
    }

    if (checksMoves(board))
        return 1;

    print(argv[1]);
    return 0;
}