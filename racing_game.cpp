#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <racing_game.h>
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