#include <fstream>
#include <iostream>
using namespace std;

void read()
{
    ofstream file_out("./bin/temp/notation.txt");
    // открыли файл для записи
    cout << "Введите построчно шахматную нотацию: " << endl << endl;
    char buffer[1200];
    cin.getline(buffer, 1200); // считали строку
    file_out << buffer << endl;
    cout << endl << "Введите y для завершения ввода: ";
    if (getchar() == 'y') {
        file_out.close(); // закрываем файл
        return;
    }
    while (getchar() != 'y') {
        cin.get();
        cin.getline(buffer, 1200); // считали строку
        file_out << buffer << endl;
        cout << endl << "Введите y для завершения ввода: ";
    }

    file_out.close(); // закрываем файл
}

void read_file(char dir[])
{
    ifstream file_in(dir); // открыли файл для чтения
    if (!file_in.is_open()) {
        cout << "\x1b[1;31mТакого файла не существует либо неверно указан "
                "путь!\x1b[0m"
             << endl
             << "* Проверьте правильность введенных данных и/или попробуйте "
                "указать путь полностью"
             << endl;

        exit(0);
    }
    ofstream file_out("./bin/temp/notation.txt");
    // открыли файл для записи
    char buffer[1200];
    while (!file_in.eof()) {
        file_in.getline(buffer, 1200); // считали строку из файла
        file_out << buffer << endl;
    }
    file_in.close();  // закрываем файл
    file_out.close(); // закрываем файл
}
