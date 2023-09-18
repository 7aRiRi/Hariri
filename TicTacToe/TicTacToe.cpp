#include <iostream>
#include <climits>
using namespace std;

const int SIZE = 3;
char HUMAN, COMPUTER;

struct Move {
    int row, col;
};

// Function to initialize the board
void initializeBoard(char board[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board
void printBoard(char board[SIZE][SIZE]) {
    cout << "-------------" << endl;
    for(int i = 0; i < SIZE; i++) {
        cout << "| ";
        for(int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        cout << "-------------" << endl;
    }
}

// Function to check if the move is valid
bool isValidMove(int row, int col, char board[SIZE][SIZE]) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function to check if the board is full
bool isBoardFull(char board[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function to check if there is a winner
char checkWinner(char board[SIZE][SIZE]) {
    // Check rows
    for(int i = 0; i < SIZE; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    // Check columns
    for(int i = 0; i < SIZE; i++) {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';
}

// Function to evaluate the board
int evaluate(char board[SIZE][SIZE]) {
    char winner = checkWinner(board);
    if (winner == COMPUTER) {
        return 10;
    } else if (winner == HUMAN) {
        return -10;
    }
    return 0;
}

// Minimax function with alpha-beta pruning
int minimax(char board[SIZE][SIZE], int depth, bool isMax, int alpha, int beta) {
    if (isBoardFull(board) || depth == 0) {
        return evaluate(board);
    }

    if (isMax) {
        int maxEval = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int eval = minimax(board, depth - 1, false, alpha, beta);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    board[i][j] = ' ';
                    if (beta <= alpha) break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = HUMAN;
                    int eval = minimax(board, depth - 1, true, alpha, beta);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    board[i][j] = ' ';
                    if (beta <= alpha) break;
                }
            }
        }
        return minEval;
    }
}

// Function to find the best move using minimax with alpha-beta pruning
Move findBestMove(char board[SIZE][SIZE]) {
    int bestVal = INT_MIN;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, SIZE * SIZE, false, INT_MIN, INT_MAX);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    cout << "Do you want to play first? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        HUMAN = 'O';
        COMPUTER = 'X';

        // Computer's move if user chose to play second
        Move bestMove = findBestMove(board);
        board[bestMove.row][bestMove.col] = COMPUTER;
    } else {
        HUMAN = 'X';
        COMPUTER = 'O';
    }

    while (true) {
        // Print the board
        printBoard(board);

        // Human's move
        int row, col;
        cout << "Enter row (0-2) and column (0-2) separated by space: ";
        cin >> row >> col;

        if (isValidMove(row, col, board)) {
            board[row][col] = HUMAN;
            if (checkWinner(board) == HUMAN) {
                printBoard(board);
                cout << "Congratulations! You win!" << endl;
                break;
            } else if (isBoardFull(board)) {
                printBoard(board);
                cout << "It's a draw!" << endl;
                break;
            }
        } else {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        // Computer's move
        Move bestMove = findBestMove(board);
        board[bestMove.row][bestMove.col] = COMPUTER;
        if (checkWinner(board) == COMPUTER) {
            printBoard(board);
            cout << "Computer wins! Better luck next time." << endl;
            break;
        } else if (isBoardFull(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
