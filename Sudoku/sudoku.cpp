#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9;

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "---------------------\n";
        }
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            if (grid[i][j] == 0) {
                cout << "_ ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;

    if (!findEmptyLocation(grid, row, col)) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

bool isValidMove(int userGrid[N][N], int computerSolution[N][N], int row, int col, int num) {
    int tempGrid[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tempGrid[i][j] = userGrid[i][j];
        }
    }

    if (tempGrid[row][col] != 0) {
        return false;
    }

    if (!isSafe(tempGrid, row, col, num)) {
        return false;
    }

    tempGrid[row][col] = num;

    return solveSudoku(tempGrid);
}

void generateRandomSudoku(int grid[N][N]) {
    srand(time(0));

    for (int i = 0; i < N; i += 3) {
        for (int num = 1; num <= 9; num++) {
            int row = rand() % 3 + i;
            int col = rand() % 3 + i;
            while (!isSafe(grid, row, col, num)) {
                row = rand() % 3 + i;
                col = rand() % 3 + i;
            }
            grid[row][col] = num;
        }
    }

    solveSudoku(grid);

    int numToRemove = rand() % 21 + 40;
    for (int i = 0; i < numToRemove; i++) {
        int row = rand() % N;
        int col = rand() % N;
        while (grid[row][col] == 0) {
            row = rand() % N;
            col = rand() % N;
        }
        grid[row][col] = 0;
    }
}

int main() {
    int grid[N][N] = {0};
    int computerSolution[N][N];

    generateRandomSudoku(grid);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            computerSolution[i][j] = grid[i][j];
        }
    }

    cout << "Welcome to Sudoku!\n";
    cout << "Enter row (1-9) and column (1-9) and the number you want to place (e.g., 3 5 7)\n";
    cout << "Enter -1 to quit.\n\n";

    while (true) {
        printGrid(grid);

        int row, col, num;
        cout << "Enter row, column, and number (or -1 to quit): ";
        cin >> row;

        if (row == -1) {
            break;
        }

        cin >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (!isValidMove(grid, computerSolution, row - 1, col - 1, num)) {
            cout << "Invalid move. Please try again.\n";
            continue;
        }

        grid[row - 1][col - 1] = num;
        cout << "Continue playing...\n";
    }

    return 0;
}
