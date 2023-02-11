#ifndef GAMEXO_GAMEXO_HEAD_H
#define GAMEXO_GAMEXO_HEAD_H

using std::cin;
using std::cout;
using std::string;

enum class Status {
    INCORRECT, NOBODY, VANYA, PETYA, UNKNOWN
};
bool victory = false;
constexpr int sizeOfTable = 3;

void inputString(string &s);

Status searchWinner(char table[sizeOfTable][sizeOfTable], const char c, int i, bool);

bool isCorrectInputUser(char table[sizeOfTable][sizeOfTable]);

//bool foundWinner(int &countX, int &countO, Status &status);
Status isCorrectCondition(char table[sizeOfTable][sizeOfTable], const char c);
//bool sumSymbolsXO(char table[sizeOfTable][sizeOfTable], int &countX, int &countO);
#endif
