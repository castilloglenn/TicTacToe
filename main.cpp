#include <iostream>
#include <cstdio>

using namespace std;


string board[9];
string validPieces[2] = {"X", "O"};
int boardSize = sizeof(board)/sizeof(board[0]);
int emptyFields = boardSize;
bool gameFinished = false;

// evaluator array
string *eval[8][3] = {
    {&board[0], &board[1], &board[2]},
    {&board[3], &board[4], &board[5]},
    {&board[6], &board[7], &board[8]},
    {&board[0], &board[3], &board[6]},
    {&board[1], &board[4], &board[7]},
    {&board[2], &board[5], &board[8]},
    {&board[0], &board[4], &board[8]},
    {&board[2], &board[4], &board[6]}
};

// constant access array
string **fieldEvals[9][4][3] = {
    {eval[0], eval[3], eval[6], nullptr},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
};

// method prototyping
void clearBoard();
void printBoard();
void placePiece(int index, string piece);
int checkBoard();

int main() {
    clearBoard();
    printBoard();

    placePiece(5, validPieces[0]);
    placePiece(9, validPieces[1]);

    printBoard();

    cout << *eval[1][1] << endl;

    return 0;
}

void clearBoard() {
    for (int index = 0; index < boardSize; index++)
        board[index] += " ";
    int emptyFields = boardSize;
}

void printBoard() {
    printf("+-+-+-+\n|%s|%s|%s|\n+-+-+-+\n|%s|%s|%s|\n+-+-+-+\n|%s|%s|%s|\n+-+-+-+\n",
        board[0].c_str(), board[1].c_str(), board[2].c_str(),
        board[3].c_str(), board[4].c_str(), board[5].c_str(),
        board[6].c_str(), board[7].c_str(), board[8].c_str()
    );
}

void placePiece(int index, string piece) {
    board[index - 1] = piece;
}

int checkBoard() {
    string winner;

    return -1;
}
