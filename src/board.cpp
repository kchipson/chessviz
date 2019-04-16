#include "board.h"

char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

char boardc[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                     {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                     {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

void print(string out)
{
    string buffer;
    string move;
    ifstream file_in("./bin/temp/notation.txt"); // открытие файла для чтения
    while (!file_in.eof()) {
        int i = 0;
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            while (buffer[i] != ' ')
                i++;
            i++;
            for (int m = 0; m < 2; m++) {
                move = "";
                while ((buffer[i] != ' ') && (i != (int)buffer.length())) {
                    move += buffer[i];
                    i++;
                    if (i == (int)buffer.length())
                        m++;
                }
                i++;

                if (regex_match(move, regex("^[a-h].+"))) {
                    boardc[(move[4] - '0' - 1)][(move[3] - 'a')]
                            = boardc[(move[1] - '0' - 1)][(move[0] - 'a')];
                    boardc[(move[1] - '0' - 1)][(move[0] - 'a')] = ' ';

                    if ((out == string("--browser")) || (out == string("-b"))) {
                        if (!m)
                            print_html(
                                    boardc,
                                    (buffer
                                     + "<span style='color: #ff6600'> <ход "
                                       "белых> </span>"));
                        else
                            print_html(
                                    boardc,
                                    (buffer
                                     + "<span style='color: #006f66'> <ход "
                                       "черных> </span>"));
                    } else {
                        if (!m)
                            print_consol(
                                    boardc,
                                    (buffer
                                     + "\x1b[1;35m <ход черных> \x1b[1;31m"));
                        else
                            print_consol(
                                    boardc,
                                    (buffer
                                     + "\x1b[1;35m <ход черных> \x1b[1;31m"));
                    }

                } else {
                    boardc[(move[5] - '0' - 1)][(move[4] - 'a')]
                            = boardc[(move[2] - '0' - 1)][(move[1] - 'a')];
                    boardc[(move[2] - '0' - 1)][(move[1] - 'a')] = ' ';

                    if ((out == string("--browser")) || (out == string("-b"))) {
                        if (!m)
                            print_html(
                                    boardc,
                                    (buffer
                                     + "<span style='color: #ff6600'> <ход "
                                       "белых> </span>"));
                        else
                            print_html(
                                    boardc,
                                    (buffer
                                     + "<span style='color: #006f66'> <ход "
                                       "черных> </span>"));
                    } else {
                        if (!m)
                            print_consol(
                                    boardc,
                                    (buffer
                                     + "\x1b[1;35m <ход черных> \x1b[1;31m"));
                        else
                            print_consol(
                                    boardc,
                                    (buffer
                                     + "\x1b[1;35m <ход черных> \x1b[1;31m"));
                    }
                }
            }
        }
        if (buffer[buffer.length() - 1] == '#')
            break;
    }
    if ((out == string("--browser")) || out == string("-b")) {
        print_html();
        system("sensible-browser bin/temp/chessviz.html");
    }
}