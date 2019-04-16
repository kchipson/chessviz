#include "checks.h"
#include "board.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <regex>
#include <string>
using namespace std;
extern char board[8][8];
int i = 1;
int yMove(char x)
{
    return (x - '0' - 1);
}
int xMove(char y)
{
    return (y - 'a');
}
int checkStr(string str)
{
    // Проверка на входные значения
    //[ТипФигуры] Поле ТипХода Поле [ТипФигуры | 'e.p.'| Рокировка | '+' | '#']

    if (!regex_match(
                str,
                regex("^[0-9]+\\. "
                      "(((([RNBQK]{0,1}[a-h][1-8][-x][a-h][1-8](e.p.|[RNBQK]){"
                      "0,1})|O-O-O|O-O)[+]{0,1} "
                      "(([RNBQK]{0,1}[a-h][1-8][-x][a-h][1-8](e.p.|[RNBQK]){0,"
                      "1})|O-O-O|O-O)[+#]{0,1})|((([RNBQK]{0,1}[a-h][1-8][-x]["
                      "a-h][1-8](e.p.|[RNBQK]){0,1})|O-O-O|O-O)[#]{0,1}))"))) {
        cout << "\x1b[1;31mПроверьте правильность введенного хода в "
                "строке \x1b[0m\""
             << str << "\"\x1b[1;31m" << endl
             << "Запись хода должна осуществляться следующим бразом:\x1b[0m"
             << endl
             << "\x1b[1;34m"
             << "<№ Хода>. <Ход> <Ход>" << endl
             << endl
             << "\x1b[1;35m"
             << " Ход = [ТипФигуры] Поле ТипХода Поле [ТипФигуры | 'e.p.' | "
                "'+' | '#'] | Рокировка"
             << endl
             << " ТипФигуры = 'K' | 'Q' | 'R' | 'B' | 'N'" << endl
             << " Поле = /[a-h][1-8]/" << endl
             << " ТипХода = '-' | 'x'" << endl
             << " Рокировка = '0-0-0' | '0-0'" << endl
             << "\x1b[0m" << endl;
        return 1;
    }

    //Проверка на номер
    if (!regex_match(str, regex("^" + to_string(i) + "+\\. .+"))) {
        cout << "\x1b[1;31mПроверьте правильность введенного номера хода в "
                "строке \x1b[0m\""
             << str << "\"\x1b[1;31m , номер хода должен быть равен " << i
             << " и после него должен стоять пробел!\x1b[0m" << endl;
        return 1;
    }
    i++;

    //Проверка взятия на проходе
    if ((regex_match(
                str, regex(".+ ((.+-.+e\\.p\\.)|([RNBQK].+e\\.p\\.)).* .*")))
        || (regex_match(
                   str,
                   regex(".+ .+ ((.+-.+e\\.p\\.)|([RNBQK].+e\\.p\\.)).*")))) {
        cout << "\x1b[1;31mПроверьте правильность введенного хода в "
                "строке \x1b[0m\""
             << str
             << "\"\x1b[1;31m , взятие на проходе возможно только при типе "
                "хода взятие и только пешкой!\x1b[0m"
             << endl;
        return 1;
    }

    //Проверка превращения др фигур
    if ((regex_match(
                str, regex(".+ (([RNBQK].+[RNBQK].* )|(.+[^8][RNBQK].* )).*")))
        || (regex_match(
                   str,
                   regex(".+ .+ (([RNBQK].+[RNBQK])|(.+[^1][RNBQK])).*")))) {
        cout << "\x1b[1;31mПроверьте правильность введенного хода в "
                "строке \x1b[0m\""
             << str
             << "\"\x1b[1;31m , превращение возможно только пешки и только при "
                "ходе на 8(для белых) или 1(для черных) клетку!\x1b[0m"
             << endl;
        return 1;
    }
    return 0;
}

int checksMoves()
{
    ifstream file_in("./bin/temp/notation.txt"); // открытие файла для чтения
    string buffer, move;
    while (!file_in.eof()) {
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            i = 0;

            while (buffer[i] != ' ')
                i++;
            i++;

            for (int m = 0; m < 2; m++) {
                move = "";
                while ((buffer[i] != ' ') && (i != (int)buffer.length())) {
                    move += buffer[i];
                    i++;
                }
                i++;

                cout << "Ход \"" << buffer << "\"";
                if (checkMove(
                            move, m)) // checkMove(move, m) m=0-белые m=1-черные
                    return 1;
                if (i == (int)buffer.length())
                    m++;
                cout << "\x1b[1;32m верен!\x1b[0m" << endl;
                if (buffer[buffer.length() - 1] == '#')
                    return 0;
            }
        }
    }
    file_in.close(); // закрытие файла
    return 0;
}

int checkMove(string move, bool color) //Ход и цвет(0-белые,1-черные)
{
    if (color)
        cout << "\x1b[1;35m <ход черных> \x1b[1;31m" << endl;
    else
        cout << "\x1b[1;35m <ход белых> \x1b[1;31m" << endl;
    if (regex_match(move, regex("^[a-h].+")))
        return checkPawn(move, color);
    if (regex_match(move, regex("^N.+")))
        return checkKnight(move, color);
    if (regex_match(move, regex("^B.+")))
        return checkBishop(move, color);
    if (regex_match(move, regex("^R.+")))
        return checkRook(move, color);
    if (regex_match(move, regex("^Q.+")))
        return checkQueen(move, color);
    if (regex_match(move, regex("^K.+")))
        return checkKing(move, color);
    return 0;
}
int checkKing(string move, bool color)
{
    int y = yMove(move[2]), x = xMove(move[1]), y_end = yMove(move[5]),
        x_end = xMove(move[4]);
    // cout<<"x= "<<x<<"    y= "<<y<<"    x_end= "<<x_end<<"    y_end=
    // "<<y_end<<endl;
    if (color) {
        if (board[y][x] == 'K') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x] != 'k') { //Проверка на наличие коня в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ферзя! Ход ферзем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        if (board[y][x] == 'k') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'K') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ферзя! Ход ферзем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (!(((x == x_end) && (1 == abs(y - y_end)))
          || ((y == y_end) && (1 == abs(x - x_end)))
          || ((abs(x - x_end) == 1)
              && (1 == abs(y - y_end))))) { //Проверка на правильность хода
        cout << "Ошибка в ходе " << move
             << "! Король может ходить на одну клетку по горизонтали, "
                "вертикали, диагонали!"
             << endl;
        return 1;
    }

    if (move[3] == '-') {
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(4, 6)
                 << " стоит фигура!" << endl;
            return 1;
        }

    } else {
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(4, 6) << " нет фигуры!" << endl;
            return 1;
        }
    }

    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'k';
    else
        board[y_end][x_end] = 'K';
    return 0;
}

int checkQueen(string move, bool color)
{
    int y = yMove(move[2]), x = xMove(move[1]), y_end = yMove(move[5]),
        x_end = xMove(move[4]);
    // cout<<"x= "<<x<<"    y= "<<y<<"    x_end= "<<x_end<<"    y_end=
    // "<<y_end<<endl;
    if (color) {
        if (board[y][x] == 'Q') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x] != 'q') { //Проверка на наличие коня в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ферзя! Ход ферзем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        if (board[y][x] == 'q') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'Q') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ферзя! Ход ферзем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (!(((x == x_end) && (y != y_end)) || ((x != x_end) && (y == y_end))
          || (abs(x - x_end)
              == abs(y - y_end)))) { //Проверка на правильность хода
        cout << "Ошибка в ходе " << move
             << "! Ферзь ходит только по вертикали, горизонтали или диагонали!"
             << endl;
        return 1;
    }

    if (move[3] == '-') {
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(4, 6)
                 << " стоит фигура!" << endl;
            return 1;
        }

    } else {
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(4, 6) << " нет фигуры!" << endl;
            return 1;
        }
    }

    //Проверка на наличие фигур по пути
    if (abs(x - x_end) == abs(y - y_end)) {
        int temp_x = 0, temp_y = 0, z_x = 1, z_y = 1;
        if (x > x_end)
            z_x = -1;
        if (y > y_end)
            z_y = -1;

        for (temp_x = x + z_x, temp_y = y + z_y; temp_x != x_end;
             temp_x = temp_x + z_x, temp_y = temp_y + z_y)
            if (board[temp_y][temp_x] != ' ') {
                cout << "Ход " << move
                     << " невозможен, т.к на пути хода ферьзя стоит фигура "
                     << endl;
                return 1;
            }
    } else {
        int temp_x = x, temp_y = y, z_x = 0, z_y = 0;
        if (x > x_end)
            z_x = -1;
        else if (x < x_end)
            z_x = 1;
        if (y > y_end)
            z_y = -1;
        else if (y < y_end)
            z_y = 1;

        if (x != x_end) {
            for (temp_x = x + z_x; temp_x != x_end; temp_x = temp_x + z_x) {
                if (board[temp_y][temp_x] != ' ') {
                    cout << "Ход " << move
                         << " невозможен, т.к на пути хода ферьзя стоит фигура "
                         << endl;
                    return 1;
                }
            }
        } else if (y != y_end) {
            for (temp_y = y + z_y; temp_y != y_end; temp_y = temp_y + z_y) {
                if (board[temp_y][temp_x] != ' ') {
                    cout << "Ход " << move
                         << " невозможен, т.к на пути хода ферьзя стоит фигура "
                         << endl;
                    return 1;
                }
            }
        }
    }

    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'q';
    else
        board[y_end][x_end] = 'Q';
    return 0;
}

int checkRook(string move, bool color)
{
    // TODO: NULL
    int y = yMove(move[2]), x = xMove(move[1]), y_end = yMove(move[5]),
        x_end = xMove(move[4]);
    // cout<<"x= "<<x<<"    y= "<<y<<"    x_end= "<<x_end<<"    y_end=
    // "<<y_end<<endl;
    if (color) {
        if (board[y][x] == 'R') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x] != 'r') { //Проверка на наличие коня в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ладью! Ход ладьей из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        if (board[y][x] == 'r') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'R') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит ладью! Ход ладьей из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (!(((x == x_end) && (y != y_end))
          || ((x != x_end) && (y == y_end)))) { //Проверка на правильность хода
        cout << "Ошибка в ходе " << move
             << "! Ладья ходит по вертикали или горизонтали!" << endl;
        return 1;
    }

    if (move[3] == '-') {
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(4, 6)
                 << " стоит фигура!" << endl;
            return 1;
        }

    } else {
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(4, 6) << " нет фигуры!" << endl;
            return 1;
        }
    }

    //Проверка на наличие фигур по пути
    int temp_x = x, temp_y = y, z_x = 0, z_y = 0;
    if (x > x_end)
        z_x = -1;
    else if (x < x_end)
        z_x = 1;
    if (y > y_end)
        z_y = -1;
    else if (y < y_end)
        z_y = 1;

    if (x != x_end) {
        for (temp_x = x + z_x; temp_x != x_end; temp_x = temp_x + z_x) {
            if (board[temp_y][temp_x] != ' ') {
                cout << "Ход " << move
                     << " невозможен, т.к на пути хода ладьи стоит фигура "
                     << endl;
                return 1;
            }
        }
    } else if (y != y_end) {
        for (temp_y = y + z_y; temp_y != y_end; temp_y = temp_y + z_y) {
            if (board[temp_y][temp_x] != ' ') {
                cout << "Ход " << move
                     << " невозможен, т.к на пути хода ладьи стоит фигура "
                     << endl;
                return 1;
            }
        }
    }

    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'r';
    else
        board[y_end][x_end] = 'R';
    return 0;
}

int checkBishop(string move, bool color)
{
    // TODO: NULL
    int y = yMove(move[2]), x = xMove(move[1]), y_end = yMove(move[5]),
        x_end = xMove(move[4]);
    if (color) {
        if (board[y][x] == 'B') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x] != 'b') { //Проверка на наличие коня в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит слона! Ход слоном из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        if (board[y][x] == 'b') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'B') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит слона! Ход слоном из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (!(abs(x - x_end) == abs(y - y_end))) { //Проверка на правильность хода
        cout << "Ошибка в ходе " << move << "! Слон ходит по диагонали!"
             << endl;
        return 1;
    }

    if (move[3] == '-') {
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(4, 6)
                 << " стоит фигура!" << endl;
            return 1;
        }

    } else {
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(4, 6) << " нет фигуры!" << endl;
            return 1;
        }
    }

    //Проверка на наличие фигур по пути
    int temp_x = 0, temp_y = 0, z_x = 1, z_y = 1;
    if (x > x_end)
        z_x = -1;
    if (y > y_end)
        z_y = -1;

    for (temp_x = x + z_x, temp_y = y + z_y; temp_x != x_end;
         temp_x = temp_x + z_x, temp_y = temp_y + z_y)
        if (board[temp_y][temp_x] != ' ') {
            cout << "Ход " << move
                 << " невозможен, т.к на пути хода слона стоит фигура " << endl;
            return 1;
        }

    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'b';
    else
        board[y_end][x_end] = 'B';
    return 0;
}

int checkKnight(string move, bool color)
{
    // TODO: NULL
    int y = yMove(move[2]), x = xMove(move[1]), y_end = yMove(move[5]),
        x_end = xMove(move[4]);
    if (color) {
        if (board[y][x] == 'N') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x] != 'n') { //Проверка на наличие коня в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит коня! Ход конем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        if (board[y][x] == 'n') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'N') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит коня! Ход конем из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (!(((abs(x - x_end) == 1) && (abs(y - y_end) == 2))
          || ((abs(y - y_end) == 1)
              && (abs(x - x_end) == 2)))) { //Проверка на правильность хода
        cout << "Ошибка в ходе " << move << "! Конь ходит \" буквой Г\""
             << endl;
        return 1;
    }

    if (move[3] == '-') {
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(4, 6)
                 << " стоит фигура!" << endl;
            return 1;
        }

    } else {
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(4, 6) << " нет фигуры!" << endl;
            return 1;
        }
    }
    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'n';
    else
        board[y_end][x_end] = 'N';
    return 0;
}

int checkPawn(string move, bool color)
{
    // TODO: реализовать взятие на проходе, шах, мат, превращение
    int y = yMove(move[1]), x = xMove(move[0]), y_end = yMove(move[4]),
        x_end = xMove(move[3]), temp;
    // cout<<"x= "<<x<<"    y= "<<y<<"    x_end= "<<x_end<<"    y_end=
    // "<<y_end<<endl; getchar();
    if (color) {
        temp = 1;
        if (board[y][x] == 'P') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход черных!"
                 << endl;
            return 1;
        }
        if (board[y][x]
            != 'p') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит пешку! Ход пешкой из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    } else {
        temp = -1;
        if (board[y][x] == 'p') { //Проверка на ход
            cout << "Ошибка в ходе " << move << ", ожидался ход белых!" << endl;
            return 1;
        }
        if (board[y][x]
            != 'P') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(1, 2) << " в ходе " << move
                 << " не содержит пешку! Ход пешкой из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
    }

    if (move[2] == '-') {
        if (!((x == x_end)
              && ((y == y_end + temp * 1)
                  | (y == y_end + temp * 2)))) { //Проверка на правильность хода
            cout << "Ход " << move
                 << "! Пешка может ходить только вперед и только на "
                    "1/(2-если ход из начальной позиции) клетку/и!"
                 << endl;
            return 1;
        }
        if (board[y_end][x_end]
            != ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Ход " << move << " невозможен, т.к в " << move.substr(3, 5)
                 << " стоит фигура!" << endl;
            return 1;
        }
        if (y == y_end + temp * 2)
            if (board[y_end + temp * 1][x_end] != ' ') {
                cout << "Ход " << move
                     << " невозможен, т.к на пути хода пешки стоит фигура "
                     << endl;
                return 1;
            }

    } else {
        if (!(y == y_end + temp * 1)
            && ((x == x_end - temp * 1)
                || (x == x_end + temp * 1))) { //Проверка на правильность хода
            cout << "Ход " << move
                 << "! При взятии пешка может ходить на одну клетку по "
                    "диагонали!"
                 << endl;
            return 1;
        }
        if (board[y_end][x_end]
            == ' ') { //Проверка на наличие фигуры в конечной позиции
            cout << "Взятие в ходе " << move << " невозможно, т.к в "
                 << move.substr(3, 5) << " нет фигуры!" << endl;
            return 1;
        }
    }
    board[y][x] = ' ';
    if (color)
        board[y_end][x_end] = 'p';
    else
        board[y_end][x_end] = 'P';
    return 0;
}