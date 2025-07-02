#include "gravity_game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "Utils.h"

using namespace std;

int playerX = 0, playerY = 0;
int warnings = 0;
char maze[5][5];

void selectRandomMaze() {
    srand(time(0)); // Random seed
    int option = rand() % 3 + 1; // Random number between 1 and 3

    switch (option) {
        case 1: {
            char map1[maze_size][maze_size] = {
                {'>', 'v', '>', 'v', '>'},
                {'^', '>', 'v', '<', 'v'},
                {'^', '^', '>', 'v', '>'},
                {'v', '>', '^', '>', 'v'},
                {'^', '^', '>', '^', '>'}
            };
            memcpy(maze, map1, sizeof(map1));
            break;
        }
        case 2: {
            char map2[maze_size][maze_size] = {
                {'v', '>', '>', 'v', 'v'},
                {'v', '^', '<', '^', '>'},
                {'>', '>', 'v', '<', 'v'},
                {'^', '^', '>', 'v', '>'},
                {'^', '>', '^', '>', '>'}
            };
            memcpy(maze, map2, sizeof(map2));
            break;
        }
        case 3: {
            char map3[maze_size][maze_size] = {
                {'>', '>', 'v', '<', 'v'},
                {'v', '>', 'v', 'v', '>'},
                {'^', '^', '>', '>', 'v'},
                {'^', 'v', '<', 'v', '<'},
                {'^', '>', '<', '>', '>'}
            };
            memcpy(maze, map3, sizeof(map3));
            break;
        }
    }
}

void showMaze() {
    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            if (i == playerX && j == playerY)
                cout << 'G' << ' '; // G = Guardian
            else
                cout << maze[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "\nWarnings: " << warnings << "/" << MAX_WARNINGS << "\n";
}

bool isValidMove(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX < 0 || newX >= maze_size || newY < 0 || newY >= maze_size)
        return false;

    char gravity = maze[playerX][playerY];

    switch (gravity) {
        case '^': return dx == -1 && dy == 0;
        case 'v': return dx == 1 && dy == 0;
        case '<': return dx == 0 && dy == -1;
        case '>': return dx == 0 && dy == 1;
        default: return false;
    }
}

void movePlayer(int dx, int dy) {
    if (isValidMove(dx, dy)) {
        playerX += dx;
        playerY += dy;
        cout << "You moved correctly...\n";
    } else {
        cout << "Invalid move. You're sent back to the start.\n";
        playerX = 0;
        playerY = 0;
        warnings++;
    }
}

bool gravityMaze() {
    setColor(12); // Red
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    setColor(14); // Blue
    cout << R"(
                                                    
 _____             _ _          _____               
|   __|___ ___ _ _|_| |_ _ _   |   __|___ _____ ___ 
|  |  |  _| .'| | | |  _| | |  |  |  | .'|     | -_|
|_____|_| |__,|\_/|_|_| |_  |  |_____|__,|_|_|_|___|
                        |___|                       
)" << endl;
    setColor(12); // red
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    setColor(7); // Reset

    cout << "You have fallen into a gravitational maze, and you must escape. \n";
    cout << "Figure out the path to the other side of the maze. The bottom-right corner (4,4).\n";
    cout << "Remember that you must follow the direction of gravity, or you will return to the starting point.\n";
    cout << "Gravity: ^ (up), v (down), < (left), > (right)\n";
    cout << "Do not move against gravity...\n\n";

    selectRandomMaze();
    
    showMaze();

    do {
        cout << "\nMove: (w = up, s = down, a = left, d = right)\n";
        char option;
        cin >> option;

        switch(option) {
            case 'w': movePlayer(-1, 0); break;
            case 's': movePlayer(1, 0); break;
            case 'a': movePlayer(0, -1); break;
            case 'd': movePlayer(0, 1); break;
            default: cout << "Invalid command.\n";
        }

        showMaze(); // Show after each move

        if (warnings >= MAX_WARNINGS) {
            cout << "\nToo many failed attempts. You are expelled from the maze.\n";
            return false;
        }

    } while (playerX != 4 || playerY != 4);

    cout << "\n You've escaped the Gravity Maze!\n";
    return true;
}


