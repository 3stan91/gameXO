#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

enum class Status {
    INCORRECT, CORRECT, NOBODY, VANYA, PETYA
};
constexpr int sizeOfTable = 3;

void inputString(string &);

Status gameOver(char table[sizeOfTable][sizeOfTable]);

bool isCorrect(char table[sizeOfTable][sizeOfTable], int);

int main() {
    //string s[sizeOfTable]{"X..", "OXO", "OOO"};
    string s[sizeOfTable]{"XO.", "XO.", "X.O"};
    /*  for (int i = 0; i < sizeOfTable; ++i)
          inputString(s[i]);
    */
    char table[sizeOfTable][sizeOfTable];

    for (int i = 0; i < sizeOfTable; ++i)
        for (int j = 0; j < sizeOfTable; ++j)
            table[i][j] = s[i][j];

    if (!isCorrect(table, sizeOfTable)) {
        cout << "Incorrect\n";
        exit(1);
    }

    switch (gameOver(table)) {
        case Status::CORRECT:
            cout << "Correct\n";
            break;
        case Status::INCORRECT:
            cout << "Incorrect\n";
            break;
        case Status::NOBODY:
            cout << "Nobody\n";
            break;
        case Status::PETYA:
            cout << "Petya won\n";
            break;
        case Status::VANYA:
            cout << "Vanya won\n";
            break;
    }
    return 0;
}

Status gameOver(char table[sizeOfTable][sizeOfTable]) {
    int countDots = 0, countO = 0;
    int countX1 = 0, countX2=0, countX3=0, countX4 =0;

    for (int row = 0; row < sizeOfTable; row++) {
        for (int col = 0; col < sizeOfTable; col++) {
            if (table[row][col] == 'X')
                countX1++;
            if (table[col][row] == 'X')
                countX2++;
            if (table[col][col] == 'X')
                countX3++;
            if (table[col][sizeOfTable-1-col] == 'X')
                countX3++;
        }
        if (countX1 == sizeOfTable  || countX2 == sizeOfTable
                || countX3 == sizeOfTable || countX4 == sizeOfTable)
            return Status::PETYA;

        countX1=0;
        countX2=0;
        countX3=0;
        countX4=0;
    }

}

/*
    for (int i = 0; i < sizeOfTable; ++i) {
        for (int j = 0; j < ; ++j) {

        }
        if ((table[i][0] == table[i][1] == table[i][2] == 'X') ||
            (table[0][i] == table[1][i] == table[2][i] == 'X'))
            return Status::PETYA;
        else if ((table[i][0] == table[i][1] == table[i][2] == 'O') ||
                 (table[0][i] == table[1][i] == table[2][i] == 'O'))
            return Status::VANYA;
        else
            return Status::NOBODY;
    }
}
*/

void inputString(string &s) {
    static int numberString = 0;
    cout << "input " << ++numberString << " string\n";
    std::getline(cin, s);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

bool isCorrect(char table[3][3], int n) {
    bool result = true;
    int countDots = 0, countO = 0, countX = 0;
    bool nobody = false;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (table[i][j] != 'X' && table[i][j] != 'O' && table[i][j] != '.') {
                result = false;
                break;
            } else if (table[i][j] == '.')
                ++countDots;
            else if (table[i][j] == 'O')
                ++countO;
            else if (table[i][j] == 'X')
                ++countX;

        }
    }
    if ((countO <= 2 && countX > n) || (countX <= 2 && countO > n))
        result = false;
    return result;
}