#include <iostream>
#include <vector>
using namespace std;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>> &grid)
{
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            cout << "------+-------+------" << endl;
        }
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                cout << "| ";
            }
            if (grid[row][col] == 0)
            {
                cout << ". ";
            }
            else
            {
                cout << grid[row][col] << " ";
            }
        }
        cout << endl;
    }
}

// Check if a number can be placed at given position
bool isSafe(vector<vector<int>> &grid, int row, int col, int num)
{
    // Check row
    for (int x = 0; x < 9; x++)
    {
        if (grid[row][x] == num)
            return false;
    }

    // Check column
    for (int x = 0; x < 9; x++)
    {
        if (grid[x][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Main backtracking solver function
bool solveSudoku(vector<vector<int>> &grid)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            // Find empty cell
            if (grid[row][col] == 0)
            {
                // Try numbers 1-9
                for (int num = 1; num <= 9; num++)
                {
                    if (isSafe(grid, row, col, num))
                    {
                        grid[row][col] = num;

                        // Recursively solve next cell
                        if (solveSudoku(grid))
                        {
                            return true;
                        }

                        // Backtrack if solution fails
                        grid[row][col] = 0;
                    }
                }
                return false; // No valid number found
            }
        }
    }
    return true; // All cells filled
}

int main()
{
    // Initialize Sudoku grid (0 represents empty cell)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    cout << "Original Sudoku Puzzle:" << endl;
    printGrid(grid);
    cout << "\nSolving...\n"
         << endl;

    if (solveSudoku(grid))
    {
        cout << "Solution Found:" << endl;
        printGrid(grid);
    }
    else
    {
        cout << "No solution exists" << endl;
    }

    return 0;
}