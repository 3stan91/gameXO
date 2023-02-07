#include <iostream>
#include <string>
#include "gameXO_Head.h"

int main() {
    //string s[sizeOfTable]{"X..", "OXO", "OOO"};
    //string s[sizeOfTable]{"X..", ".X.", "OO."};
    //string s[sizeOfTable]{"XXO", "OOX", "XOX"};
    //string s[sizeOfTable]{"XO.", "XO.", "X.O"};
    string s[sizeOfTable]{"OX.", "XOX", "X.O"};  //?
    //string s[sizeOfTable]{"..X", "OX.", "X.O"};
    /*
    string s[3];
    for (int i = 0; i < sizeOfTable; ++i)
        inputString(s[i]);
    */
    char table[sizeOfTable][sizeOfTable];

    for (int i = 0; i < sizeOfTable; ++i)
        for (int j = 0; j < sizeOfTable; ++j)
            table[i][j] = s[i][j];

    if (!isCorrectInputUser(table)) {
        cout << "Incorrect\n";
        exit(1);
    }
    char XO[2]{'X', 'O'};
    int i = -1;
    bool detectedWinner = false;
    while (!detectedWinner && ++i < 2) {
        switch (foundWinner(table, XO[i])) {
            label:
            case Status::INCORRECT:
                cout << "Incorrect\n";
                detectedWinner = true;
                break;
            case Status::NOBODY:
                cout << "Nobody\n";
                detectedWinner = true;
                break;
            case Status::PETYA:
                if (isCorrectCondition(table)) {
                    cout << "Petya won\n";
                    detectedWinner = true;
                    break;
                } else
                    goto label;
            case Status::VANYA:
                if (isCorrectCondition(table)) {
                    cout << "Vanya won\n";
                    detectedWinner = true;
                    break;
                } else
                    goto label;
        }
    }
    return 0;
}

Status foundWinner(char table[sizeOfTable][sizeOfTable], const char symbol) {
    int counterColumn = 0, counterRow = 0, counter1Diagonal = 0, counter2Diagonal = 0;
    Status winner;
    for (int row = 0; row < sizeOfTable; row++) {
        for (int column = 0; column < sizeOfTable; column++) {

            if (table[row][column] == symbol)
                counterColumn++;
            if (table[column][row] == symbol)
                counterRow++;
            if (table[column][column] == symbol)
                counter1Diagonal++;
            if (table[column][sizeOfTable - 1 - column] == symbol)
                counter2Diagonal++;
        }

        if ((counterColumn == sizeOfTable || counterRow == sizeOfTable
             || counter1Diagonal == sizeOfTable || counter2Diagonal == sizeOfTable) && symbol == 'X') {
            victory = true;
            winner = Status::PETYA;
            break;
        } else if ((counterColumn == sizeOfTable || counterRow == sizeOfTable
                    || counter1Diagonal == sizeOfTable || counter2Diagonal == sizeOfTable) && symbol == 'O') {
            victory = true;
            winner = Status::VANYA;
            break;
        } else if (counterColumn <= 2 || counterRow <= 2 || counter1Diagonal <= 2 || counter2Diagonal <= 2) {
            winner = Status::NOBODY;
            break;
        }
        counterColumn = 0;
        counterRow = 0;
        counter1Diagonal = 0;
        counter2Diagonal = 0;
    }
    return winner;
}

void inputString(string &s) {
    static int numberString = 0;
    cout << "input " << ++numberString << " string\n";
    std::getline(cin, s);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

bool sumSymbolsXO(char table[sizeOfTable][sizeOfTable], int &countX, int &countO) {
    bool more3Symbols = false;
    for (int i = 0; i < sizeOfTable; ++i) {
        for (int j = 0; j < sizeOfTable; ++j) {
            if (table[i][j] == 'O')
                ++countO;
            else if (table[i][j] == 'X')
                ++countX;
        }
    }
    if (countX >= sizeOfTable || countO >= sizeOfTable)
        more3Symbols = true;
    return more3Symbols;
}

bool isCorrectInputUser(char table[sizeOfTable][sizeOfTable]) {
    for (int i = 0; i < sizeOfTable; ++i) {
        for (int j = 0; j < sizeOfTable; ++j) {
            if (table[i][j] != 'X' && table[i][j] != 'O' && table[i][j] != '.') {
                return false;
            }
        }
    }
    /* for (int i = 0; i < size; ++i) {
         for (int j = 0; j < size; ++j) {
             if (table[i][j] != 'X' && table[i][j] != 'O' && table[i][j] != '.') {
                 correct = false;
                 break;
             } else if (table[i][j] == '.')
                 ++countDots;
             else if (table[i][j] == 'O')
                 ++countO;
             else if (table[i][j] == 'X')
                 ++countX;
         }
       //  if (countX >= size || countO >= size) //&& victory)
         //    correct = false;
     }
     */
    return true;
}

bool isCorrectCondition(char table[sizeOfTable][sizeOfTable]){
    int countO = 0, countX = 0;
    bool correctCondition = true;

    if (sumSymbolsXO(table, countO, countX) && victory)
        correctCondition = false;
    if ((countO <= 2 && countX > sizeOfTable) || (countX <= 2 && countO > sizeOfTable))
        correctCondition = false;
return correctCondition;
}