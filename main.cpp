#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

enum class Status {
    INCORRECT, CORRECT, NOBODY, VANYA, PETYA
};
constexpr int countOfString = 3;

void inputString(string &);

Status testInput(char table[][countOfString], int);

bool checking(char table[][countOfString], int);

int main() {
    string s[countOfString]{"X..", "OXO", "OOO"};
    /*  for (int i = 0; i < countOfString; ++i)
          inputString(s[i]);
    */
    char table[countOfString][countOfString];

    for (int i = 0; i < countOfString; ++i)
        for (int j = 0; j < countOfString; ++j)
            table[i][j] = s[i][j];

    if (!checking(table, countOfString)) {
        cout << "Incorrect\n";
        exit(1);
    }

    switch (testInput(table, countOfString)) {
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

Status testInput(char table[][3], int numberString) {
    int countDots = 0, countO = 0, countX = 0;
    // bool nobody = false;
    char mas[3];
     for (int i = 0; i < numberString; ++i) {
         for (int j = 0; j < numberString; ++j) {
             if (table[i][j] == '.')
                 ++countDots;
             if (table[i][j] == 'O')
                 ++countO;
             if (table[i][j] == 'X')
                 ++countX;
         }
     }

      /*   if (countX < countO || countO < countX)
             nobody = true;

         if ((countX > countO && countX > 3) || (countX < countO && countO > 3))
             return Status::INCORRECT;
         if (nobody)
             return Status::NOBODY;

         if (countO <= countDots && countX <= countDots)
             return Status::NOBODY;
     */

    int testDialonal = 0;
    while (testDialonal < 2) {
        if (testDialonal == 0) {
            for (int i = 0; i < numberString; ++i) {
                mas[i] = table[i][i];
            }
        } else
            for (int i = 0; i < numberString; ++i) {
                mas[i] = table[i][numberString - i - 1];
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

        if (countO == 3)
            return Status::VANYA;
        else if (countX == 3)
            return Status::PETYA;
        testDialonal++;
        countX = countO = 0;
    }

    for (int i = 0; i < numberString; ++i) {
        if ((table[i][0] == table[i][1] == table[i][2] == 'X') ||
            (table[0][i] == table[1][i] == table[2][i] == 'X'))
            return Status::PETYA;
        else if ((table[i][0] == table[i][1] == table[i][2] == 'O') ||
                 (table[0][i] == table[1][i] == table[2][i] == 'O'))
            return Status::VANYA;
        else
            return Status::NOBODY;
    }


    /*      if ((table[i][i] == 'X') || (table[i][numberString - i - 1] == 'X') ||
              (table[i][0] == table[i][1] && table[i][0] == table[i][2] && table[i][0] == 'X')
              || (table[0][i] == table[1][i] && table[0][i] == table[2][i] && table[0][i] == 'X'))
              return Status::PETYA;
          else if ((table[i][i] == 'O') || (table[i][numberString - i - 1] == 'O') ||
                   (table[i][0] == table[i][1] && table[i][0] == table[i][2] && table[i][0] == 'O')
                   || (table[0][i] == table[1][i] && table[0][i] == table[2][i] && table[0][i] == 'O'))
              return Status::VANYA;
          else
              return Status::NOBODY;
      }
      */
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