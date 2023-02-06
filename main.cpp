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

Status foundWinner(char table[sizeOfTable][sizeOfTable], const char symbol = 'X');

bool isCorrect(char table[sizeOfTable][sizeOfTable], int);

int main() {
    //string s[sizeOfTable]{"X..", "OXO", "OOO"};
    //string s[sizeOfTable]{"X..", ".X.", "OO."};
    string s[sizeOfTable]{"XXO", "OOX", "XOX"};
    //string s[sizeOfTable]{"XO.", "XO.", "X.OO"};
    //string s[sizeOfTable]{"OX.", "XOX", "X.O"};

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

    if (!isCorrect(table, sizeOfTable)) {
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
                if (isCorrect(table, 3)) {
                    cout << "Petya won\n";
                    detectedWinner = true;
                    break;
                } else
                    goto label;
            case Status::VANYA:
                if (isCorrect(table, 3)) {
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
        }
        else if ((counterColumn == sizeOfTable || counterRow == sizeOfTable
                  || counter1Diagonal == sizeOfTable || counter2Diagonal == sizeOfTable) && symbol == 'O') {
                victory = true;
            winner = Status::VANYA;
                break;
        }
        else if (counterColumn <= 2 || counterRow <= 2 || counter1Diagonal <= 2 || counter2Diagonal <= 2){
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

bool isCorrect(char table[sizeOfTable][sizeOfTable], int size) {
    bool correct = true;
    int countDots = 0, countO = 0, countX = 0;

    for (int i = 0; i < size; ++i) {
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
    }

    if ((countO <= 2 && countX > size) || (countX <= 2 && countO > size))
        correct = false;
    if ((countX >= size && countO >= size) && victory)
        correct = false;
    return correct;
}