#include <iostream>

using namespace std;


string winner;
string board[9];
string validPieces[2] = {"X", "O"};
int boardSize = sizeof(board)/sizeof(board[0]);
int emptyFields = boardSize, turn = 0;
bool gameFinished = false, playerAI = false;

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
int indexFields[9][4] = {
    {0, 3,  6, -1},
    {0, 4, -1, -1},
    {0, 5,  7, -1},
    {1, 3, -1, -1},
    {1, 4,  6,  7},
    {1, 5, -1, -1},
    {2, 3,  7, -1},
    {2, 4, -1, -1},
    {2, 5,  6, -1}
};

// method prototyping
void clearBoard();
void printBoard();
bool placePiece(int index, string piece);
void boardEvaluation(int boardIndex, string piece);
int findBestMove();
string boardEvaluation();
int minimax(string board, bool isMax, int &alpha, int &beta, int &depth);



int main() {
    clearBoard();
//    // This is for player-2-player
//    while (!gameFinished) {
//        printBoard();
//
//        int move;
//        cout << "Enter move: " << endl;
//        cin >> move;
//
//        placePiece(move, validPieces[turn]);
//    }
    playerAI = true;
    while (!gameFinished) {
        printBoard();

        int move;
        if (turn == 1) {
            move = findBestMove();
            placePiece(move, validPieces[turn]);

            cout << "Computer moved at index " << move << endl;
            cout << "Enter any button to continue." << endl;

            cin.ignore();
            cin.get();
        } else {
            cout << "Human move: " << endl;
            cin >> move;

            placePiece(move, validPieces[turn]);
        }
    }
    printBoard();
    cout << "Result: " << winner << endl;


    return 0;
}

void clearBoard() {
    for (int index = 0; index < boardSize; index++)
        board[index] = " ";
    emptyFields = boardSize;
    gameFinished = false;
    winner = "";

}

void printBoard() {
    system("cls");
    printf(
       "+---+---+---+\n"
       "| %s | %s | %s |\n"
       "+---+---+---+\n"
       "| %s | %s | %s |\n"
       "+---+---+---+\n"
       "| %s | %s | %s |\n"
       "+---+---+---+\n",
        board[0].c_str(), board[1].c_str(), board[2].c_str(),
        board[3].c_str(), board[4].c_str(), board[5].c_str(),
        board[6].c_str(), board[7].c_str(), board[8].c_str()
    );
}

/** \brief Place piece algorithm for non-ai players
 *
 * \param index = visual key index starting from 1-9
 * \param piece = the visual representation of board piece
 * \return true if the move is valid else false
 */
bool placePiece(int index, string piece) {
    int boardIndex = index - 1;
    if (board[boardIndex] != " " || boardIndex > 8) return false;

    board[boardIndex] = piece;
    emptyFields--;

    boardEvaluation(boardIndex, piece);
    turn = (turn == 0) ? 1: 0;
    return true;
}

void boardEvaluation(int boardIndex, string piece) {
    for (int evalIndex : indexFields[boardIndex]) {
        if (evalIndex != -1) {
            string
            first = *eval[evalIndex][0],
            second = *eval[evalIndex][1],
            third = *eval[evalIndex][2];

            int
            firstCompare = piece.compare(*eval[evalIndex][0]),
            secondCompare = piece.compare(*eval[evalIndex][1]),
            thirdCompare = piece.compare(*eval[evalIndex][2]);

            if (firstCompare == secondCompare && secondCompare == thirdCompare) {
                winner = piece;
                gameFinished = true;
            }
        }
    }

    if (emptyFields == 0) {
        winner = "draw";
        gameFinished = true;
    }
}

string boardEvaluation() {
    return "G";
}

int findBestMove() {
    string boardCopy[9];
    for (int copyIndex = 0; copyIndex < boardSize; copyIndex++) {
        boardCopy[copyIndex] = board[copyIndex];
    }

}

int minimax(string board, bool isMax, int &alpha, int &beta, int &depth) {

}










