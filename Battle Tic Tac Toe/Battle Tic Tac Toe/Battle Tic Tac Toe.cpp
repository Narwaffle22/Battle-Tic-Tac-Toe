#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

#pragma region Rules Class

class Rules
{
public:
    Rules();
    bool verifyInput(string, string);
    bool isDone();
private:
    string mockBoard[9] = { "1","2","3","4","5","6","7","8","9" };
    int mockTurnCounter = 0;
    int winningCombos[9][3];
    bool checkCorrectCharacter(string);
    bool isInRange(int);
    bool isInteger(const string&);
    bool isAvailble(int);
    bool threeInARow(int, int, int);
};

Rules::Rules(){
    winningCombos[0][0] = 0;
    winningCombos[0][1] = 1;
    winningCombos[0][2] = 2;

    winningCombos[1][0] = 3;
    winningCombos[1][1] = 4;
    winningCombos[1][2] = 5;

    winningCombos[2][0] = 6;
    winningCombos[2][1] = 7;
    winningCombos[2][2] = 8;

    winningCombos[3][0] = 0;
    winningCombos[3][1] = 3;
    winningCombos[3][2] = 6;

    winningCombos[4][0] = 1;
    winningCombos[4][1] = 4;
    winningCombos[4][2] = 7;

    winningCombos[5][0] = 2;
    winningCombos[5][1] = 5;
    winningCombos[5][2] = 8;

    winningCombos[6][0] = 0;
    winningCombos[6][1] = 4;
    winningCombos[6][2] = 8;

    winningCombos[7][0] = 2;
    winningCombos[7][1] = 4;
    winningCombos[7][2] = 6;
}
bool Rules::verifyInput(string space, string token) {
    bool correctToken = true;
    bool correctSpace = true;
    int mark;

    correctToken = checkCorrectCharacter(token);

    if (isInteger(space)) {
        mark = stoi(space);
        correctSpace = isInRange(mark);
        correctSpace = isAvailble(mark);
    }
    else {
        correctSpace = false;
    }

    return correctToken && correctSpace;
}
bool Rules::checkCorrectCharacter(string token) {
    if (token == "X" || token == "O") {
        return true;
    }
    else {
        return false;
    }
}
bool Rules::isInRange(int space) {
    if (space > 0 && space < 10) {
        return true;
    }
    else {
        return false;
    }
}
bool Rules::isInteger(const string& str) {
    istringstream iss(str);
    int num;
    char extra;

    if (!(iss >> num) || (iss >> extra)) {
        return false;
    }

    return true;
}
bool Rules::isAvailble(int space) {
    if ((mockBoard[space - 1] != "X" && mockBoard[space - 1] != "O") && isInRange(space)) {
        if (mockTurnCounter % 2 == 0)
            mockBoard[space - 1] = "X";
        else
            mockBoard[space - 1] = "O";
        mockTurnCounter++;
        return true;
    }
    else {
        return false;
    }
}
bool Rules::isDone() {
    for (int i = 0; i < 8; i++) {
        if (this->threeInARow(winningCombos[i][0], winningCombos[i][1], winningCombos[i][2]))
            return true;
    }

    for (int i = 0; i < 8; i++) {
        if (isInteger(mockBoard[i]))
            return false;
    }

    return false;
}
bool Rules::threeInARow(int indexOne, int indexTwo, int indexThree) {
    return mockBoard[indexOne] == mockBoard[indexTwo] && mockBoard[indexTwo] == mockBoard[indexThree];
}

#pragma endregion

#pragma region Board Class

class Board {
public:
    Board();
    string getBoard();
    void markBoard(int, string);
    string checkTile(int);
    void printBoard();

private:
    string currentBoard;
    string slots[9] = { "1","2","3","4","5","6","7","8","9" };
    string startingBoard = " 1 | 2 | 3 \n---+---+---\n 4 | 5 | 6 \n---+---+---\n 7 | 8 | 9 ";
    string edgeMarker = " ";
    string verticalDivider = " | ";
    string horizontalDivider = "\n---+---+---\n";
    void formatBoard();
    Rules* ruleschecker = new Rules();
};

Board::Board() {
    this->currentBoard = startingBoard;
}
string Board::getBoard() {
    return currentBoard;
}
void Board::markBoard(int slot, string token) {
    slots[slot - 1] = token;

    formatBoard();
}
string Board::checkTile(int slot) {
    return slots[slot];
}
void Board::formatBoard() {
    currentBoard = edgeMarker + slots[0] + verticalDivider + slots[1] + verticalDivider + slots[2] + edgeMarker;
    currentBoard += horizontalDivider;
    currentBoard += edgeMarker + slots[3] + verticalDivider + slots[4] + verticalDivider + slots[5] + edgeMarker;
    currentBoard += horizontalDivider;
    currentBoard += edgeMarker + slots[6] + verticalDivider + slots[7] + verticalDivider + slots[8] + edgeMarker;
}
void Board::printBoard() {
    cout << currentBoard << "\n\n\n";
}

#pragma endregion

#pragma region Game Loop

class Game
{
public:
    Game();
    void start();
private:
    int playerPlay(Rules*);
};

Game::Game()
{
}
void Game::start() {
    Board* board = new Board();
    Rules* rules = new Rules();
    string input = "";
    int mark;
    bool gameInPlay = true;

    while (gameInPlay) {
        board->printBoard();

        cout << "let's do this thing!\n";
        mark = playerPlay(rules);

        board->markBoard(mark, "X");
        board->printBoard();
        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }

        cout << "now it's player two\n";
        mark = playerPlay(rules);

        board->markBoard(mark, "O");
        board->printBoard();

        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }
    }


}
int Game::playerPlay(Rules* rules) {
    string input = "";
    int mark = 0;
    bool canContinue = false;

    while (!canContinue) {
        cout << "make your move\n";
        getline(cin, input);

        if (rules->verifyInput(input, "X")) {
            mark = stoi(input);
            cout << "\n";
            canContinue = true;
        }
        else {
            cout << "\nnot quite try again\n";
        }
    }

    return mark;

}

#pragma endregion

// main 
int main()
{
    Game* game = new Game();

    game->start();

}