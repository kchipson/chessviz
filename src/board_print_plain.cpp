#include <iostream>
using namespace std;

void print_consol(char board[8][8], char name[])
{ // Функция отрисовки доски
    cout << endl << "\x1b[1;33m" << name << "\x1b[0m" << endl;
    int i, j;
    for (i = 7; i > -1; i--) {
        cout << i + 1 << " ";
        for (j = 0; j < 8; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "  ";
    for (i = 97; i < 105; i++)
        cout << (char)i << " ";
    cout << endl;
}