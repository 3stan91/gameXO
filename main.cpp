#include <iostream>
#include <string>
#include "gameXO_Head.h"

int main() {
    string s[3];
    for (int i = 0; i < sizeOfTable; ++i)
        inputString(s[i]);

    char table[sizeOfTable][sizeOfTable];

    for (int i = 0; i < sizeOfTable; ++i)
        for (int j = 0; j < sizeOfTable; ++j)
            table[i][j] = s[i][j];

    if (!isCorrectInputUser(table)) {
        cout << "Incorrect\n";
        exit(-1);
    }

    char winner;
    bool detectedWinner = false;
    while (!detectedWinner) {
        if (searchWinner(table, winner)) {

            switch (isCorrectCondition(table, winner)) {
                case Status::INCORRECT:
                    cout << "Incorrect\n";
                    detectedWinner = true;
                    break;
                case Status::NOBODY:
                    cout << "Nobody\n";
                    detectedWinner = true;
                    break;
                case Status::PETYA:
                    cout << "Petya won\n";
                    detectedWinner = true;
                    break;
                case Status::VANYA:
                    // if (isCorrectCondition(table, 'X')) {
                    cout << "Vanya won\n";
                    detectedWinner = true;
                    break;
            }
        } else {
            cout << "Nobody\n";
            return 0;
        }
    }
    return 0;
}

bool searchWinner(char table[sizeOfTable][sizeOfTable], char &won) {
    int counter = 0, i = 0;
    char XO[2]{'X', 'O'};
    bool victory = false;
    do {
        for (int row = 0; !victory && row < sizeOfTable; row++) {
            for (int column = 0; column < sizeOfTable; column++) {
                if (table[row][column] == XO[i])
                    counter++;
            }

            if (counter == sizeOfTable && (XO[i] == 'X' || XO[i] == 'O')) {
                victory = true;
                won = XO[i];
                break;
            }
            counter = 0;
        }

        for (int row = 0; !victory && row < sizeOfTable; row++) {
            for (int column = 0; column < sizeOfTable; column++) {
                if (table[column][row] == XO[i])
                    counter++;
            }
            if (counter == sizeOfTable && (XO[i] == 'X' || XO[i] == 'O')) {
                victory = true;
                won = XO[i];
                break;
            }
            counter = 0;
        }

        for (int column = 0; column < sizeOfTable; column++) {
            if (table[column][column] == XO[i])
                counter++;
        }
        if (counter == sizeOfTable && (XO[i] == 'X' || XO[i] == 'O')) {
            victory = true;
            won = XO[i];
        } else
            counter = 0;

        for (int column = 0; column < sizeOfTable; column++) {
            if (table[column][sizeOfTable - 1 - column] == XO[i])
                counter++;
        }
        if (counter == sizeOfTable && (XO[i] == 'X' || XO[i] == 'O')) {
            victory = true;
            won = XO[i];
        }
    } while (!victory && ++i < sizeof(XO) / sizeof(XO[0]));
    return victory;
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
    return true;
}

Status isCorrectCondition(char table[sizeOfTable][sizeOfTable], char &w) {
    int countO = 0, countX = 0, countDot = 0;

    for (int i = 0; i < sizeOfTable; ++i) {
        for (int j = 0; j < sizeOfTable; ++j) {
            if (table[i][j] == 'O')
                ++countO;
            if (table[i][j] == 'X')
                ++countX;
            if (table[i][j] == '.')
                ++countDot;
        }
    }

    if (countX <= 2 && countO <= 2 && countDot > 4)
        return Status::NOBODY;
    if ((w == 'X' && countO >= 3) || (w == 'O' && countX >= 3))
        return Status::INCORRECT;
    if (w == 'X' && countX == 3) {
        if (countO < 3)
            return Status::PETYA;
    }
    if (w == 'O' && countO == 3) {
        if (countX < 3)
            return Status::VANYA;
    }
    if (countO >= countX || countX >= countO)
        return Status::INCORRECT;
}