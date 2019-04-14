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
void checkFlag(string str){
    if ((str == string("--browser")) || (str == string("-b")))
        print_html_create();

    if (!((str == string("--console")) || (str == string("-c")) || (str == string("--browser")) || (str == string("-b")))){
        cout<<" Неверный флаг, допустимые флаги: "<<endl
            << "\x1b[1;35m• <--console/-c> - для вывода нотации в консоль" << endl
            << "• <--browser/-b> - для вывода нотации в html-файл\x1b[0m" << endl;
        exit(0);
    }
}
int main(int argc, char* argv[])
{ 
    string buffer;
    string moveWhite, moveBlack;
   
    switch (argc)
    {
    case 1:
        cout << "\x1b[1;35m Для запуска программы необходимо обязательно указать один из флагов:"<< endl
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
        cout << "\x1b[1;31mОШИБКА! Приложение может принимать на вход только один параметр(<флаг, указывающий параметр вывода>) или два параметра(<флаг, указывающий параметр вывода> <файл с игровой партией>)!\x1b[0m"<< endl;
        return 1;
        break;
    }
    
    if (checksMoves())
        return 1;

    ifstream file_in("./bin/temp/notation.txt"); // открытие файла для чтения
    while (!file_in.eof()) {
        int i = 0;
        moveWhite= moveBlack="";
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            
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
        || (string(argv[1]) == string("-b"))) {
        print_html();
        system("sensible-browser bin/temp/chessviz.html");
    }

    return 0;
}