#include "checks.h"
#include "board.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;
extern char board[8][8];
int i = 1;

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
    if (!file_in.is_open()) {
        cout << "\x1b[1;31mERROR 404!\x1b[0m" << endl << endl;
        exit(0);
    }
    string buffer;

    while (!file_in.eof()) {
        getline(file_in, buffer); // считывание строки из файла
        if (buffer != "") {
            i = 0;
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
            }

            cout << "Ход \"" << buffer << "\"";
            if (checkMove(moveWhite, 0))
                return 1;
            cout << "\x1b[1;32m верен!\x1b[0m" << endl;
            cout << "Ход \"" << buffer << "\"";
            if (checkMove(moveBlack, 1))
                return 1;
            cout << "\x1b[1;32m верен!\x1b[0m" << endl << endl;
        }
        if (buffer[buffer.length() - 1] == '#')
            return 0;
    }
    file_in.close(); // закрытие файла
    return 0;
}

int checkMove(string move, bool color) //Ход и цвет(0-белые,1-черные)
{
    if (color)
        cout << "\x1b[1;35m <ход черных> \x1b[1;31m";
    else
        cout << "\x1b[1;35m <ход белых> \x1b[1;31m";
    if (regex_match(move, regex("^[a-h].+")))
        return checkPawn(move, color);
    return 0;
}

int checkPawn(string move, bool color)
{
    if (color) {
        if (board[(move[1] - '0' - 1)][(move[0] - 'a')]
            != 'p') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(0, 2)
                 << " не содержит пешку! Ход пешкой из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
        if (move[2] == '-') {
            if (!((move[0] == move[3])
                  && ((move[1] == move[4] + 1)
                      | (move[1]
                         == move[4] + 2)))) { //Проверка на правильность хода
                cout << "Пешка может ходить только вперед и только на "
                        "1/(2-если ход из начальной позиции) клетку/и!"
                     << endl;
                return 1;
            }
            if (board[(move[4] - '0' - 1)][(move[3] - 'a')]
                != ' ') { //Проверка на наличие фигуры в конечной позиции
                cout << "Ход невозможен, т.к в " << move.substr(3, 5)
                     << " стоит фигура!" << endl;
                return 1;
            }
            if (move[1] == move[4] + 2)
                if (board[(move[4] - '0' - 1)][(move[3] - 'a')] != ' ') {
                    cout << board[(move[4] - '0' - 1)][(move[3] - 'a')];
                    cout << "Ход невозможен, т.к на пути хода пешки стоит "
                            "фигура "
                         << endl;
                    return 1;
                }
        } else {
            if (!(move[1] == move[4] + 1)
                && ((move[0] == move[3] - 1)
                    || (move[0]
                        == move[3] + 1))) { //Проверка на правильность хода
                cout << "При взятии пешка может ходить на одну клетку по "
                        "диагонали!"
                     << endl;
                return 1;
            }
            if (board[(move[4] - '0' - 1)][(move[3] - 'a')]
                == ' ') { //Проверка на наличие фигуры в конечной позиции
                cout << (move[4] - '0') << " + " << (move[3] - 'a');
                cout << "Взятие невозможно, т.к в " << move.substr(3, 5)
                     << " нет фигуры!" << endl;
                return 1;
                // TODO: реализовать взятие на проходе, шах, мат
            }
        }
    } else {
        if (board[(move[1] - '0' - 1)][(move[0] - 'a')]
            != 'P') { //Проверка на наличие пешки в начальной позиции
            cout << "Место " << move.substr(0, 2)
                 << " не содержит пешку! Ход пешкой из данной позиции "
                    "выполнить невозможно!"
                 << endl;
            return 1;
        }
        if (move[2] == '-') {
            if (!((move[0] == move[3])
                  && ((move[1] == move[4] - 1)
                      | (move[1]
                         == move[4] - 2)))) { //Проверка на правильность хода
                cout << "Пешка может ходить только вперед и только на "
                        "1/(2-если ход из начальной позиции) клетку/и!"
                     << endl;
                return 1;
            }
            if (board[(move[4] - '0' - 1)][(move[3] - 'a')]
                != ' ') { //Проверка на наличие фигуры в конечной позиции
                cout << "Ход невозможен, т.к в " << move.substr(3, 5)
                     << " стоит фигура!" << endl;
                return 1;
            }
            if (move[1] == move[4] - 2)
                if (board[(move[4] - '0' - 1)][(move[3] - 'a')] != ' ') {
                    cout << "Ход невозможен, т.к на пути хода пешки стоит "
                            "фигура "
                         << endl;
                    return 1;
                }
        } else {
            if (!(move[1] == move[4] - 1)
                && ((move[0] == move[3] - 1)
                    || (move[0]
                        == move[3] + 1))) { //Проверка на правильность хода
                cout << "При взятии пешка может ходить на одну клетку по "
                        "диагонали!"
                     << endl;
                return 1;
            }
            if (board[(move[4] - '0' - 1)][(move[3] - 'a')]
                == ' ') { //Проверка на наличие фигуры в конечной позиции
                cout << "Взятие невозможно, т.к в " << move.substr(3, 5)
                     << " нет фигуры!" << endl;
                return 1;
                // TODO: реализовать взятие на проходе, шах, мат
            }
        }
    }

    board[(move[1] - '0' - 1)][(move[0] - 'a')] = ' ';
    if (color)
        board[(move[4] - '0' - 1)][(move[3] - 'a')] = 'p';
    else
        board[(move[4] - '0' - 1)][(move[3] - 'a')] = 'P';
    return 0;
}