#include<iostream>
#include<string>

using namespace std;

// Winner class (it should be struct T-T)
class Winner {
public:
    char winner;

    explicit Winner(char str) {
         winner = str; 
    
    }


    char getWinner(){return winner;}
    void setWinner(char str){winner = str;}
};

// Board Class
class Board {
private:
    string sections[3][3] = {
        {"1","2","3"},
        {"4","5","6"},
        {"7","8","9"}
    };

    char characters[2];

public:


    Board(char one, char two) {
        characters[0] = one;
        characters[1] = two;
    }

    void setIndex(int index, string value) {
        switch (index) {

            case 1: sections[0][0] = value; break;
            case 2: sections[0][1] = value; break;
            case 3: sections[0][2] = value; break;
            case 4: sections[1][0] = value; break;
            case 5: sections[1][1] = value; break;
            case 6: sections[1][2] = value; break;
            case 7: sections[2][0] = value; break;
            case 8: sections[2][1] = value; break;
            case 9: sections[2][2] = value; break;


        }
    }

    bool isSet(int index) {
        char indexLabel = getIndex(index);
        return !isdigit(indexLabel);
        
    }

    char getIndex(int vindex) {


        switch (vindex) {

            case 1: return sections[0][0][0];
            case 2: return sections[0][1][0];
            case 3: return sections[0][2][0];
            case 4: return sections[1][0][0];
            case 5: return sections[1][1][0];
            case 6: return sections[1][2][0];
            case 7: return sections[2][0][0];
            case 8: return sections[2][1][0];
            case 9: return sections[2][2][0];
            default: return '?';
        }

    }

    string getBoardLabel() {

        string label;

        for (size_t y = 0; y < 3; y++) {

            for (size_t i = 0; i < 3; i++) {


                label.append(sections[y][i]).append(" | ");
            }

            label.append("\n------------\n");


        }

        return label.empty() ? "?" : label;
    }
};

// Checker Class
class Checker {
private:
    Board &board;
public:
    explicit Checker(Board &board_) : board(board_) {}

    static bool same(char val1, char val2, char val3) {
        return val1 == val2 && val2 == val3;
    }

    Winner check() { 

        char values[9];

        for (int i = 0; i < 9; i++) {
            values[i] = board.getIndex(i+1);
        }

        // ways to win
        int patterns[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };

        for (auto &pattern : patterns) {

            if (
                same(values[pattern[0]],
             values[pattern[1]],
              values[pattern[2]])) {

                return Winner(values[pattern[0]]);
            }

        }
        return Winner('n');
    }
};

// Main function
int main() {
    char currentChar = 'X';
    Board board('X', 'O');
    Checker checker(board);

    while (checker.check().getWinner() == 'n') {

        cout << board.getBoardLabel();


        int input;

        cout << "It's "<<currentChar<<"'s turn! Enter a number of displayed: ";
        cin >> input;

        if (board.isSet(input)) {
            cout <<"Slot already taken! Try again.\n";
            continue;
        }


        board.setIndex(input, string(1, currentChar));
        currentChar = (currentChar == 'X')? 'O' : 'X';


    }


    cout << "\nPlayer "<<((currentChar == 'X') ? 'O' : 'X')<<" wins!\n";
    return 0;
}
