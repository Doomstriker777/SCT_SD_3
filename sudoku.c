#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

// Function to print the Sudoku board
void printGrid(int grid[SIZE][SIZE]) {
    printf("\nSolved Sudoku:\n");
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if it's safe to place num in grid[row][col]
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;
    bool emptyFound = false;

    // Find the next empty cell
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                emptyFound = true;
                goto found;
            }
        }
    }

found:
    if (!emptyFound)
        return true; // No empty cells, puzzle solved

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; // Backtrack
        }
    }

    return false; // Trigger backtracking
}

int main() {
    int grid[SIZE][SIZE];

    printf("Enter the Sudoku puzzle (use 0 for empty cells):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    if (solveSudoku(grid))
        printGrid(grid);
    else
        printf("No solution exists for the given Sudoku.\n");

    return 0;
}
