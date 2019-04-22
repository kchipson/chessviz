#ifndef CHECKS_H
#define CHECKS_H
#include <string>
int checkStr(std::string str);
int checkMove(char board[][8], std::string move, bool color);
int checkPawn(char board[][8], std::string move, bool color);
int checkKnight(char board[][8], std::string move, bool color);
int checkBishop(char board[][8], std::string move, bool color);
int checkRook(char board[][8], std::string move, bool color);
int checkQueen(char board[][8], std::string move, bool color);
int checkKing(char board[][8], std::string move, bool color);
int checksMoves(char board[][8]);

#endif