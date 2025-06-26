#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <random>
using namespace std;
// Platform-specific includes for non-blocking input
#ifdef _WIN32
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
#else
#include <termios.h> // For terminal settings
#include <unistd.h>  // For usleep() and STDIN_FILENO
#include <fcntl.h>   // For fcntl()
#endif

// --- Platform-specific non-blocking input functions ---
char getch_non_blocking()
{
#ifdef _WIN32
    if (_kbhit())
    {
        return _getch();
    }
    return 0; // No key pressed
#else
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr ~1");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 0;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ~2");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~3");
    return buf;
#endif
}

// --- Console clearing function ---
void clear_screen()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize, charsWritten;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, {0, 0}, &charsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, {0, 0}, &charsWritten);
    SetConsoleCursorPosition(hConsole, {0, 0});
#else
    // Para Linux/Mac
    cout << "\033[2J\033[1;1H";
#endif
}

// --- Game Constants ---
const int GAME_WIDTH = 40;
const int GAME_HEIGHT = 20;
const int PLAYER_START_POS_X = GAME_WIDTH / 2;
const int PLAYER_START_POS_Y = GAME_HEIGHT - 2;
const string PLAYER_CHAR = "/^\\";
const char OBSTACLE_CHAR = '#';
const char ROAD_CHAR = '.';
const long long distance_limit = 300;

// --- Game State ---
int player_x = PLAYER_START_POS_X;
vector<string> game_map(GAME_HEIGHT, string(GAME_WIDTH, ROAD_CHAR));
long long score = 0;
bool game_over = false;

// Random number generator
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

// --- Functions ---

void initialize_game()
{
    player_x = PLAYER_START_POS_X;
    score = 0;
    game_over = false;
    for (int i = 0; i < GAME_HEIGHT; ++i)
    {
        for (int j = 0; j < GAME_WIDTH; ++j)
        {
            game_map[i][j] = ROAD_CHAR;
        }
    }
}

void draw_game()
{
    clear_screen();

    for (int y = 0; y < GAME_HEIGHT; ++y)
    {
        for (int x = 0; x < GAME_WIDTH; ++x)
        {
            // Player
            if (y == PLAYER_START_POS_Y && x == player_x)
            {
                cout << PLAYER_CHAR;
                x += PLAYER_CHAR.length() - 1;
            }
            else
            {
                cout << game_map[y][x];
            }
        }
        cout << '\n';
    }

    cout << "Score: " << score << '\n';
    cout << "Controls: A (Left), D (Right), Q (Quit)" << '\n';
    if (game_over)
    {
        cout << "GAME OVER! Your final score: " << score << '\n';
    }
}

void update_obstacles()
{
    // Move existing obstacles down
    for (int y = GAME_HEIGHT - 1; y > 0; --y)
    {
        for (int x = 0; x < GAME_WIDTH; ++x)
        {
            game_map[y][x] = game_map[y - 1][x];
        }
    }

    // Clear the top row
    for (int x = 0; x < GAME_WIDTH; ++x)
    {
        game_map[0][x] = ROAD_CHAR;
    }

    // Generate new obstacles on the top row
    uniform_int_distribution<int> obstacle_dist(0, GAME_WIDTH - 1);
    if (rng() % 4 == 0)
    {                                                                 // Random chance to spawn obstacles
        int num_obstacles = uniform_int_distribution<int>(3, 5)(rng); // 3 to 5 obstacles
        for (int i = 0; i < num_obstacles; ++i)
        {
            int pos = obstacle_dist(rng);
            game_map[0][pos] = OBSTACLE_CHAR;
        }
    }
}

void check_collision()
{
    if (game_map[PLAYER_START_POS_Y][player_x] == OBSTACLE_CHAR)
    {
        game_over = true;
    }
}

void handle_input()
{
    char key = getch_non_blocking();

    // Normal letters
    switch (key)
    {
    case 'a':
    case 'A':
        if (player_x > 0)
        {
            player_x--;
        }
        break;
    case 'd':
    case 'D':
        if (player_x < GAME_WIDTH - PLAYER_CHAR.length())
        {
            player_x++;
        }
        break;
    case 'q':
    case 'Q':
        game_over = true;
        break;
    }
}

int main()
{
    initialize_game();

    // Hide cursor
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
#endif

    clear_screen();
    cout << "Welcome to Console Racer!" << endl;
    cout << "Press any key to start..." << endl;
    getch_non_blocking(); // Consume any initial key press

    // Waiting for the player to press something
    while (getch_non_blocking() == 0)
    {
#ifdef _WIN32
        Sleep(100); // milliseconds
#else
        usleep(100000); // microsegundos
#endif
    }

    // Start game loop
    while (!game_over && score < distance_limit)
    {
        handle_input();
        update_obstacles();
        check_collision();
        draw_game();
        score++;

#ifdef _WIN32
        Sleep(100); // Adjusts for game speed
#else
        usleep(100000);
#endif
    }

// Show cursor again at the end
#ifdef _WIN32
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
#endif

    draw_game(); // Draw final state with "GAME OVER" message

    if (score >= distance_limit && !game_over)
    {
        cout << "Cheers, you got away!!! \n";
    }

    return 0;
}