#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "OddOneGame.h"

using namespace std;

bool oddOneGame() {
    const int size = 25;
    int commonNum = rand() % 9 + 1;
    int oddNum;
    do {
        oddNum = rand() % 9 + 1;
    } while (oddNum == commonNum);

    vector<vector<int>> grid(size, vector<int>(size, commonNum));
    int oddRow = rand() % size;
    int oddCol = rand() % size;
    grid[oddRow][oddCol] = oddNum;

    cout << "Find the different number on the matrix" << endl;
    for (const auto& row : grid) {
        for (int n : row) cout << n << " ";
        cout << endl;
    }

    int rowGuess, colGuess;
    cout << "Enter the row (1-" << size << ") and the column (1-" << size << "): ";
    cin >> rowGuess >> colGuess;

    if (rowGuess - 1 == oddRow && colGuess - 1 == oddCol) {
        cout << " Correct! You have found the different number." << endl;
        return true;
    } else {
        cout << "Wrong, the correct position was (" << oddRow + 1 << ", " << oddCol + 1 << ")." << endl;
        return false;
    }
}
