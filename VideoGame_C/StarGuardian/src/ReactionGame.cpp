#include <iostream>
#include "ReactionGame.h"
#include <cstdlib>  // for rand
#include <ctime>    // for time
#include <chrono>   // for timing
#include <windows.h>
#include "Utils.h"

using namespace std;



bool reactionGame()
{
    system("cls"); // clear console
     setColor(9); // Blue
cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    setColor(10);
    cout << R"(
 __________                      __  .__                  ________                       
\______   \ ____ _____    _____/  |_|__| ____   ____    /  _____/_____    _____   ____  
 |       _// __ \\__  \ _/ ___\   __\  |/  _ \ /    \  /   \  ___\__  \  /     \_/ __ \ 
 |    |   \  ___/ / __ \\  \___|  | |  (  <_> )   |  \ \    \_\  \/ __ \|  Y Y  \  ___/ 
 |____|_  /\___  >____  /\___  >__| |__|\____/|___|  /  \______  (____  /__|_|  /\___  >
        \/     \/     \/     \/                    \/          \/     \/      \/     \/ 
)" << endl;
setColor(9); // Blue
cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    setColor(7);

    
    cout << "Welcome to Mercury, My little friend..." << endl;
    cout << "This is the reaction game! Try to win..." << endl;

    // Generate 3 random uppercase letters
    char target = 'A' + rand() % 26;
    char l2 = 'A' + rand() % 26;
    char l3 = 'A' + rand() % 26;

    // === LEVEL 1 ===
    cout << "You must type the following letter correctly: [" << target << "]" << endl;
    cout << "Enter the letter: ";

    char press;
    auto start1 = chrono::steady_clock::now();
    cin >> press;
    auto end1 = chrono::steady_clock::now();

    chrono::duration<double> elapsed1 = end1 - start1;
    if (elapsed1.count() > 3.0) {
        cout << "Too slow! You took " << elapsed1.count() << " seconds." << endl;
        return false;
    }

    if (press >= 'a' && press <= 'z') {
        press -= 32;
    }

    if (press != target) {
        cout << "Wrong key!" << endl;
        return false;
    }
    
    setColor(10);
    cout << "Correct!" << endl;
    setColor(7);

    // === LEVEL 2 ===
    cout << "Now the next letter!" << endl;
    cout << "You must type the following letter correctly: [" << l2 << "]" << endl;
    cout << "Enter the letter: ";

    char press2;
    auto start2 = chrono::steady_clock::now();
    cin >> press2;
    auto end2 = chrono::steady_clock::now();

    chrono::duration<double> elapsed2 = end2 - start2;
    if (elapsed2.count() > 3.0) {
        cout << "Too slow! You took " << elapsed2.count() << " seconds." << endl;
        return false;
    }

    if (press2 >= 'a' && press2 <= 'z') {
        press2 -= 32;
    }

    if (press2 != l2) {
        cout << "Wrong key!" << endl;
        return false;
    }

    cout << "Correct!" << endl;

    // === LEVEL 3 ===
    cout << "You are fast! Final letter!" << endl;
    cout << "You must type the following letter correctly: [" << l3 << "]" << endl;
    cout << "Enter the letter: ";

    char press3;
    auto start3 = chrono::steady_clock::now();
    cin >> press3;
    auto end3 = chrono::steady_clock::now();

    chrono::duration<double> elapsed3 = end3 - start3;
    if (elapsed3.count() > 3.0) {
        cout << "Too slow! You took " << elapsed3.count() << " seconds." << endl;
        return false;
    }

    if (press3 >= 'a' && press3 <= 'z') {
        press3 -= 32;
    }

    if (press3 != l3) {
        cout << "Wrong key!" << endl;
        return false;
    }

    cout << "Correct key! You win this minigame... Congratulations!" << endl;
    return true;
}
