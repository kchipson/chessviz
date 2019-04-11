#include "checks.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void read()
{
    string buffer;
    ofstream file_out("./bin/temp/notation.txt"); // открытие файла для записи
    cout << "\x1b[1;32mВведите построчно шахматную нотацию:\x1b[0m" << endl;

    do {
        getline(cin, buffer); // считывание строки
    } while (checkStr(buffer));

    file_out << buffer << endl;
    cout << endl << "Введите y для завершения ввода: ";
    if (getchar() == 'y') {
        file_out.close(); // закрытие файла
        return;
    }
    while (getchar() != 'y') {
        cin.get();
        do {
            getline(cin, buffer); // считывание строки
        } while (checkStr(buffer));

        file_out << buffer << endl;
        cout << endl << "Введите y для завершения ввода: ";
    }

    file_out.close(); // закрытие файла
}

void read_file(string dir)
{
    ifstream file_in(dir); // открытие файла для чтения
    if (!file_in.is_open()) {
        cout << "\x1b[1;31mТакого файла не существует либо неверно указан "
                "путь!\x1b[0m"
             << endl
             << "* Проверьте правильность введенных данных или попробуйте "
                "указать путь полностью"
             << endl;

        exit(0);
    }
    ofstream file_out("./bin/temp/notation.txt"); // открытие файла для записи
    string buffer;
    while (!file_in.eof()) {
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            if (checkStr(buffer)) {
                cout << "\x1b[1;33mИсправьте входные данные в файле " << dir
                     << " и повторите попытку\x1b[0m" << endl
                     << "\x1b[1;31mЗавершение программы...\x1b[0m" << endl;
                exit(0);
            }
            file_out << buffer << endl;
        }
        if (buffer[buffer.length() - 1] == '#')
            return;
    }
    file_in.close();  // закрытие файла
    file_out.close(); // закрытие файла
}
