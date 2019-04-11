#include "board_print_html.h"
#include "board_print_plain.h"
#include "board_read.h"
#include "checks.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;

extern char boardc[8][8];

int main(int argc, char* argv[])
{
    if (!((argc > 1)
          && ((string(argv[1]) == string("--console"))
              || (string(argv[1]) == string("-c"))
              || (string(argv[1]) == string("--browser"))
              || (string(argv[1]) == string("-b"))))) {
        cout << "\x1b[1;35m Для запуска программы необходимо обязательно "
                "указать один из флагов:"
             << endl
             << "• <--console/-c> - для вывода нотации в консоль" << endl
             << "• <--browser/-b> - для вывода нотации в html-файл" << endl
             << "*Опционально: <Путь к файлу для считывания нотации>"
             << "\x1b[0m" << endl;
        return 1;
    } else if (argc == 2) { //Чтение из ввода
        read();
    } else if (argc == 3) { //Чтение из файла
        read_file(argv[2]);
    } else {
        cout << "\x1b[1;31mОШИБКА! Приложение может принимать на вход "
                "только "
                "один "
                "параметр- файл с игровой партией!\x1b[0m"
             << endl;
        return (1);
    }
    if (checksMoves())
        return 1;

    ifstream file_in("./bin/temp/notation.txt"); // открытие файла для чтения
    if (!file_in.is_open()) {
        cout << "\x1b[1;31mERROR 404!\x1b[0m" << endl << endl;
        exit(0);
    }
    string buffer;

    if ((string(argv[1]) == string("--browser"))
        || (string(argv[1]) == string("-b")))
        print_html_create();
    while (!file_in.eof()) {
        int i = 0;
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            string moveWhite, moveBlack;
            while (buffer[i] != ' ')
                i++;
            i++;
            while (buffer[i] != ' ') {
                moveWhite += buffer[i];
                i++;
            }
            i++;
            while (i != (int)buffer.length()) {
                moveBlack += buffer[i];
                i++;
            };

            if ((string(argv[1]) == string("--browser"))
                || (string(argv[1]) == string("-b"))) {
                boardc[(moveWhite[1] - '0' - 1)][(moveWhite[0] - 'a')] = ' ';
                boardc[(moveWhite[4] - '0' - 1)][(moveWhite[3] - 'a')] = 'P';
                print_html(
                        boardc,
                        (buffer
                         + "<span style='color: #ff6600'> <ход белых> "
                           "</span>"));
                boardc[(moveBlack[1] - '0' - 1)][(moveBlack[0] - 'a')] = ' ';
                boardc[(moveBlack[4] - '0' - 1)][(moveBlack[3] - 'a')] = 'p';
                print_html(
                        boardc,
                        (buffer
                         + "<span style='color: #000092'> <ход черных> "
                           "</span>"));

            } else {
                boardc[(moveWhite[1] - '0' - 1)][(moveWhite[0] - 'a')] = ' ';
                boardc[(moveWhite[4] - '0' - 1)][(moveWhite[3] - 'a')] = 'P';
                print_consol(
                        boardc, (buffer + "\x1b[1;35m <ход белых> \x1b[1;31m"));
                boardc[(moveBlack[1] - '0' - 1)][(moveBlack[0] - 'a')] = ' ';
                boardc[(moveBlack[4] - '0' - 1)][(moveBlack[3] - 'a')] = 'p';
                print_consol(
                        boardc,
                        (buffer + "\x1b[1;35m <ход черных> \x1b[1;31m"));
            }
        }
        if (buffer[buffer.length() - 1] == '#')
            break;
    }
    if ((string(argv[1]) == string("--browser"))
        || (string(argv[1]) == string("-b")))
        print_html();
    system("sensible-browser bin/temp/chessviz.html");

    return 0;
}