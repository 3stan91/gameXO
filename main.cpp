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

Status testInput(char table[][sizeOfTable], int);

bool checking(char table[][sizeOfTable], int);

int main() {
    string s[sizeOfTable]{"X..", "OXO", "OOO"};
    /*  for (int i = 0; i < sizeOfTable; ++i)
          inputString(s[i]);
    */
    char table[sizeOfTable][sizeOfTable];

    for (int i = 0; i < sizeOfTable; ++i)
        for (int j = 0; j < sizeOfTable; ++j)
            table[i][j] = s[i][j];

    if (!checking(table, sizeOfTable)) {
        cout << "Incorrect\n";
        exit(1);
    }

    switch (testInput(table, sizeOfTable)) {
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

Status testInput(char table[][3], int sizeOfTable) {
    int countDots = 0, countO = 0, countX = 0;
    bool nobody = false;
    char mas[3];
     for (int i = 0; i < sizeOfTable; ++i) {
         for (int j = 0; j < sizeOfTable; ++j) {
             if (table[i][j] == '.')
                 ++countDots;
             if (table[i][j] == 'O')
                 ++countO;
             if (table[i][j] == 'X')
                 ++countX;
         }

         if (countX < countO || countO < countX)
             nobody = true;

         if ((countO<=2 && countX > sizeOfTable) || (countX <=2 && countO > sizeOfTable))
             return Status::INCORRECT;
         if (nobody)
             return Status::NOBODY;

         if (countO <= countDots && countX <= countDots)
             return Status::NOBODY;
     }

    int testDialonal = 0;
    while (testDialonal < 2) {
        if (testDialonal == 0) {
            for (int i = 0; i < sizeOfTable; ++i) {
                mas[i] = table[i][i];
            }
        } else
            for (int i = 0; i < sizeOfTable; ++i) {
                mas[i] = table[i][sizeOfTable - i - 1];
            }
        for (const char c: mas) {
            switch (c) {
                case 'X':
                    countX++;
                    break;
                case 'O':
                    countO++;
                    break;
            }
        }

        if (countO == sizeOfTable)
            return Status::VANYA;
        else if (countX == sizeOfTable)
            return Status::PETYA;
        testDialonal++;
        countX = countO = 0;
    }

    for (int i = 0; i < sizeOfTable; ++i) {
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


void inputString(string &s) {
    static int numberString = 0;
    cout << "input " << ++numberString << " string\n";
    std::getline(cin, s);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

bool checking(char table[][3], int n) {
    bool result = true;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (table[i][j] != 'X' && table[i][j] != 'O' && table[i][j] != '.') {
                result = false;
                break;
            } else
                continue;
    return result;
}