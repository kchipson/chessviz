#ifndef CHECKS_H
#define CHECKS_H
#include <string>
int checkStr(std::string str);
int checkMove(std::string move, bool color);
int checkPawn(std::string move, bool color);
int checkKnight(std::string move, bool color);
int checkBishop(std::string move, bool color);
int checkRook(std::string move, bool color);
int checkQueen(std::string move, bool color);
int checksMoves();

#endif