#include <iostream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;


/**
    Tictactoe Game (Optimized Algorithm)
    Group #2: Team Purple
    Members:
    • Bernal, Nivea Rea
    • Cabigat, Ernest John
    • Castillo, Allen Glenn E.
    • Garcia, Sebastian Raphael
 */



string winner;
string board[9];
string validPieces[2] = {"X", "O"};
int boardSize = sizeof(board)/sizeof(board[0]);
int emptyFields = boardSize, turn = 0, game = 0;
int scores[3] = {0, 0, 0};
bool gameFinished = false, playerAI = false;

// evaluator array
string *eval[8][3] = {
    // horizontal
    {&board[0], &board[1], &board[2]},
    {&board[3], &board[4], &board[5]},
    {&board[6], &board[7], &board[8]},

    // vertical
    {&board[0], &board[3], &board[6]},
    {&board[1], &board[4], &board[7]},
    {&board[2], &board[5], &board[8]},

    // diagonal
    {&board[0], &board[4], &board[8]},
    {&board[2], &board[4], &board[6]}
};

// constant access array
int indexFields[9][4] = {
    {0, 3,  6, -1}, // 1 or index 0
    {0, 4, -1, -1}, // 2
    {0, 5,  7, -1}, // 3
    {1, 3, -1, -1}, // 4
    {1, 4,  6,  7}, // 5
    {1, 5, -1, -1}, // 6
    {2, 3,  7, -1}, // 7
    {2, 4, -1, -1}, // 8
    {2, 5,  6, -1}  // 9
};

// method prototyping
void clearBoard();
void printBoard();
bool placePiece(int index, string piece);
void boardEvaluation(int boardIndex, string piece);

int main() {
    printf( "\n"
        "\tooooooooooooo  o8o                .                           .\n"
        "\t8'   888   `8  `\"'              .o8                         .o8\n"
        "\t     888      oooo   .ooooo.  .o888oo  .oooo.    .ooooo.  .o888oo  .ooooo.   .ooooo.\n"
        "\t     888      `888  d88' `\"Y8   888   `P  )88b  d88' `\"Y8   888   d88' `88b d88' `88b\n"
        "\t     888       888  888         888    .oP\"888  888         888   888   888 888ooo888\n"
        "\t     888       888  888   .o8   888 . d8(  888  888   .o8   888 . 888   888 888    .o\n"
        "\t     o888o     o888o `Y8bod8P'   \"888\" `Y888\"\"8o `Y8bod8P'   \"888\" `Y8bod8P' `Y8bod8P'\n\n"
        "\n\n\t\t\t\tPress <Enter> to continue.."
        , ""
    );
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool gameRunning = true;
    while (gameRunning) {
        clearBoard();
        game++;
        // This is for player-2-player
        while (!gameFinished) {

            printBoard();

            int move;
            printf("\t\t[%s] Enter move index: ", validPieces[turn].c_str());
            cin >> move;

            placePiece(move, validPieces[turn]);
        }

        printBoard();
        if (winner.compare("X") == 0) {
            cout << "\t\tPlayer 1 Wins!" << endl;
            scores[0]++;
        } else if (winner.compare("O") == 0) {
            cout << "\t\tPlayer 2 Wins!" << endl;
            scores[1]++;
        } else {
            cout << "\t\tIt's a draw!" << endl;
            scores[2]++;
        }

        string confirm;
        cout << "\n\t\tEnter any key to continue, type \"Quit\" to exit the game.\n\t\t> ";
        cin >> confirm;

        transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
        if (confirm.compare("quit") == 0) gameRunning = false;
    }

    return 0;
}

void clearBoard() {
    for (int index = 0; index < boardSize; index++)
        board[index] = " ";
    emptyFields = boardSize;
    gameFinished = false;
    winner = "";
    turn = 0;

}

void printBoard() {
    system("cls");
    printf(
        "\n\n\n\t\t Tic-Tac-Toe\t    GUIDE\t      Game %02d\n"
        "\t\t+---+---+---+\t+---+---+---+\n"
        "\t\t| %s | %s | %s |\t| 1 | 2 | 3 |\tPlayer 1: %3d points\n"
        "\t\t+---+---+---+\t+---+---+---+\n"
        "\t\t| %s | %s | %s |\t| 4 | 5 | 6 |\tPlayer 2: %3d points\n"
        "\t\t+---+---+---+\t+---+---+---+\n"
        "\t\t| %s | %s | %s |\t| 7 | 8 | 9 |\tDraws:    %3d rounds\n"
        "\t\t+---+---+---+\t+---+---+---+\n\n", game,
        board[0].c_str(), board[1].c_str(), board[2].c_str(), scores[0],
        board[3].c_str(), board[4].c_str(), board[5].c_str(), scores[1],
        board[6].c_str(), board[7].c_str(), board[8].c_str(), scores[2]
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

    if (emptyFields == 0 && winner == "") {
        winner = "draw";
        gameFinished = true;
    }
}
