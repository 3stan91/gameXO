#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

enum class Status {
    INCORRECT, NOBODY, VANYA, PETYA
};
constexpr int sizeOfTable = 3;
static bool victory = false;

void inputString(string &);

Status foundWinner(char table[sizeOfTable][sizeOfTable], char c);

bool isCorrect(char table[sizeOfTable][sizeOfTable], int);

int main() {
    //string s[sizeOfTable]{"..X", "OX.", "X.O"};
    //string s[sizeOfTable]{"X..", "OXO", "OOO"};
    //string s[sizeOfTable]{"XO.", "XO.", "X.OO"};
    //string s[sizeOfTable]{"OX.", "XOX", "X.O"};
    string s[sizeOfTable]{"XXO", "OOX", "XOX"};
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
    char XO[2]{'X', 'O'};
    int i = 0;
    bool isResult = false;
    while (!isResult || i++ < 2) {
        switch (foundWinner(table, XO[i])) {
            label:
            case Status::INCORRECT:
                cout << "Incorrect\n";
                break;
            case Status::NOBODY:
                cout << "Nobody\n";
                isResult = true;
                break;
            case Status::PETYA:
                if (isCorrect(table, 3)) {
                    cout << "Petya won\n";
                    break;
                } else
                    goto label;
            case Status::VANYA:
                if (isCorrect(table, 3)) {
                    cout << "Vanya won\n";
                    break;
                } else
                    goto label;
        }
    }
    return 0;
}

Status foundWinner(char table[sizeOfTable][sizeOfTable], const char v) {
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

    for (int row = 0; row < sizeOfTable; row++) {
        for (int col = 0; col < sizeOfTable; col++) {

            if (table[row][col] == v)
                count1++;
            if (table[col][row] == v)
                count2++;
            if (table[col][col] == v)
                count3++;
            if (table[col][sizeOfTable - 1 - col] == v)
                count4++;
        }
        if ((count1 == sizeOfTable || count2 == sizeOfTable
             || count3 == sizeOfTable || count4 == sizeOfTable) && v == 'X') {
            victory = true;
            return Status::PETYA;
        } else if ((count1 == sizeOfTable || count2 == sizeOfTable
                    || count3 == sizeOfTable || count4 == sizeOfTable) && v == 'O') {
            victory = true;
            return Status::VANYA;
        } else if (count1 <= 2 || count2 <= 2 || count3 <= 2 || count4 <= 2)
            return Status::NOBODY;

        count1 = 0;
        count2 = 0;
        count3 = 0;
        count4 = 0;
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

bool isCorrect(char table[3][3], int n) {
    bool result = true;
    int countDots = 0, countO = 0, countX = 0;

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
    if ((countX >= n && countO >= n) && victory)
        result = false;
    return result;
}