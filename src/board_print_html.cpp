#include <fstream>
#include <iostream>
using namespace std;

void print_html_create()
{
    ofstream html("./bin/temp/chessviz.html");
    html.close();
    ofstream table("./bin/temp/table.html");
    table.close();
}
void print_html()
{
    ofstream html("./bin/temp/chessviz.html");
    if (html.is_open()) {
        html << "<!DOCTYPE html>" << endl
             << "<html>" << endl
             << "<head>" << endl
             << "<meta charset='utf-8'>" << endl
             << "<title>chessviz</title>" << endl
             << "<style type='text/css'>table.chessboard{border:5px solid "
                "#333;border-collapse:collapse;height:320px;margin:20px;width:"
                "320px;float:left}table.chessboard "
                "caption{text-align:left}table.chessboard "
                "td{background-color:#fff;font-size:25px;height:40px;text-"
                "align:center;vertical-align:middle;width:40px}table."
                "chessboard tr:nth-child(even) "
                "td:nth-child(odd),table.chessboard tr:nth-child(odd) "
                "td:nth-child(even){background-color:#999}table.chessboard "
                ".white.king:before{content:\"\\2654\"}table.chessboard "
                ".white.queen:before{content:\"\\2655\"}table.chessboard "
                ".white.rook:before{content:\"\\2656\"}table.chessboard "
                ".white.bishop:before{content:\"\\2657\"}table.chessboard "
                ".white.knight:before{content:\"\\2658\"}table.chessboard "
                ".white.pawn:before{content:\"\\2659\"}table.chessboard "
                ".black.king:before{content:\"\\265A\"}table.chessboard "
                ".black.queen:before{content:\"\\265B\"}table.chessboard "
                ".black.rook:before{content:\"\\265C\"}table.chessboard "
                ".black.bishop:before{content:\"\\265D\"}table.chessboard "
                ".black.knight:before{content:\"\\265E\"}table.chessboard "
                ".black.pawn:before{content:\"\\265F\"}</style>"
             << endl
             << "</head>" << endl

             << "<body>" << endl;

        char buffer[1200];
        ifstream table("./bin/temp/table.html"); // открыли файл для чтения
        while (!table.eof()) {
            table.getline(buffer, 1200); // считали строку из файла
            html << buffer << endl;
        }
        table.close(); // закрываем файл

        html << "</body>" << endl << "</html>" << endl;

    } else
        cout << endl << "Не удалось открыть файл!";

    html.close(); // закрываем файл
}
void print_html(char board[8][8], char name[])
{
    ofstream table("./bin/temp/table.html", ios::app);

    table.seekp(0, ios::end);

    table << "<table class='chessboard'>" << endl
          << "<caption style=\"text-align: center\">" << name << "</caption>"
          << endl;

    for (int i = 7; i > -1; i--) {
        table << "<tr>" << endl;
        for (int j = 0; j < 8; j++) {
            char t = board[i][j];
            switch (t) {
            case ' ':
                table << "<td></td>" << endl;
                break;
            case 'P':
                table << "<td><span class='white pawn'></span></td>" << endl;
                break;
            case 'R':
                table << "<td><span class='white rook'></span></td>" << endl;
                break;
            case 'N':
                table << "<td><span class='white knight'></span></td>" << endl;
                break;
            case 'B':
                table << "<td><span class='white bishop'></span></td>" << endl;
                break;
            case 'Q':
                table << "<td><span class='white queen'></span></td>" << endl;
                break;
            case 'K':
                table << "<td><span class='white king'></span></td>" << endl;
                break;

            case 'p':
                table << "<td><span class='black pawn'></span></td>" << endl;
                break;
            case 'r':
                table << "<td><span class='black rook'></span></td>" << endl;
                break;
            case 'n':
                table << "<td><span class='black knight'></span></td>" << endl;
                break;
            case 'b':
                table << "<td><span class='black bishop'></span></td>" << endl;
                break;
            case 'q':
                table << "<td><span class='black queen'></span></td>" << endl;
                break;
            case 'k':
                table << "<td><span class='black king'></span></td>" << endl;
                break;
            }
        }
        table << "</tr>" << endl;
    }

    table << "</table>" << endl;
    table.close();
}
