#pragma once

constexpr int maze_size = 5;
constexpr int MAX_WARNINGS = 3;
extern int playerX, playerY;
extern int warnings;
extern char maze[maze_size][maze_size];

void selectRandomMaze();
void showMaze();
bool gravityMaze();