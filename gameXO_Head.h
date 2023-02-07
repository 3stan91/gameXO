#ifndef GAMEXO_GAMEXO_HEAD_H
#define GAMEXO_GAMEXO_HEAD_H

using std::cin;
using std::cout;
using std::string;

enum class Status {
    INCORRECT, NOBODY, VANYA, PETYA
};
constexpr int sizeOfTable = 3;
static bool victory = false;
void inputString(string &s);
Status foundWinner(char table[sizeOfTable][sizeOfTable], const char symbol = 'X');
bool isCorrectInputUser(char table[sizeOfTable][sizeOfTable]);
bool isCorrectCondition(char table[sizeOfTable][sizeOfTable]);
bool sumSymbolsXO(char table[sizeOfTable][sizeOfTable], int &countX, int &countO);

#endif
