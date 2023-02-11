#include <iostream>
#include <string>
#include "gameXO_Head.h"

int main() {
    /*string s[sizeOfTable]{"X..", "OXO", "OOO"};
    //string s[sizeOfTable]{"X..", ".X.", "OO."}; +
    //string s[sizeOfTable]{"XXO", "OOX", "XOX"}; +
    //string s[sizeOfTable]{"XO.", "XO.", "X.O"};  +

    //string s[sizeOfTable]{"..X", "OX.", "X.O"};
    string s[3];
    for (int i = 0; i < sizeOfTable; ++i)
        inputString(s[i]);
    */
    string s[sizeOfTable]{"X..", "OXO", "OOO"};
    char table[sizeOfTable][sizeOfTable];

    for (int i = 0; i < sizeOfTable; ++i)
        for (int j = 0; j < sizeOfTable; ++j)
            table[i][j] = s[i][j];

    if (!isCorrectInputUser(table)) {
        cout << "Incorrect\n";
        exit(-1);
    }

    int i = 0;
    char XO[]{'X', 'O'};
    bool detectedWinner = false;
    while (!detectedWinner && i < 2) {   //|| symbol < 2) {
        // cout << XO[symbol];
        // if(symbol<2)
        switch (searchWinner(table, XO[i], i)) {
            //  incorrect:
            case Status::INCORRECT:
                cout << "Incorrect\n";
                detectedWinner = true;
                break;
            case Status::NOBODY:
                cout << "Nobody\n";
                detectedWinner = true;
                break;
            case Status::PETYA:
                // if (isCorrectCondition(table, 'O')) {
                cout << "Petya won\n";
                detectedWinner = true;
                break;
                //}
                //  else                        goto incorrect;
            case Status::VANYA:
                // if (isCorrectCondition(table, 'X')) {
                cout << "Vanya won\n";
                detectedWinner = true;
                break;
                // }
                //  else                        goto incorrect;
        }
        i++;
    }
    return 0;
}

Status searchWinner(char table[sizeOfTable][sizeOfTable], const char c, int index) {
    int counter = 0; //, counterRow = 0, counter1Diagonal = 0, counter2Diagonal = 0;
    Status winner = Status::NOBODY;

    for (int row = 0; row < sizeOfTable; row++) {
        for (int column = 0; column < sizeOfTable; column++) {
            if (table[row][column] == c)
                counter++;
        }
        if (counter == sizeOfTable && c == 'X')
            return Status::PETYA;
        if(counter == sizeOfTable && c == 'O')
            return Status::VANYA;
    }

    for (int row = 0; row < sizeOfTable; row++) {
        for (int column = 0; column < sizeOfTable; column++) {
            if (table[column][row] == c)
                counter++;
        }
        if (counter == sizeOfTable && c == 'X')
            return Status::PETYA;
        if(counter == sizeOfTable && c == 'O')
            return Status::VANYA;
    }
    for (int column = 0; column < sizeOfTable; column++) {
        if (table[column][column] == c)
            counter++;
        if (table[column][sizeOfTable - 1 - column] == c)
            counter++;

        if (counter == sizeOfTable && c == 'X')
            return Status::PETYA;
        if(counter == sizeOfTable && c == 'O')
            return Status::VANYA;
    }
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

bool isCorrectCondition(char table[sizeOfTable][sizeOfTable], const char c) {
    int countO = 0, countX = 0;
    bool correctCondition = true;

    if (c == 'X') {
        for (int i = 0; i < sizeOfTable; ++i) {
            for (int j = 0; j < sizeOfTable; ++j) {
                if (table[i][j] == 'O')
                    ++countO;
            }
        }
        if (countO >= sizeOfTable)
            correctCondition = false;
    }
    if (c == 'O') {
        for (int i = 0; i < sizeOfTable; ++i) {
            for (int j = 0; j < sizeOfTable; ++j) {
                if (table[i][j] == 'X')
                    ++countX;
            }
        }
        if (countX >= sizeOfTable)
            correctCondition = false;
    }

    if ((countO <= 2 && countX > sizeOfTable) || (countX <= 2 && countO > sizeOfTable))
        correctCondition = false;
    return correctCondition;
}
