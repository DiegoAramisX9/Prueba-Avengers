#include <windows.h> 
#include <iostream>
#include "src/Game.h"
#include "src/MemoryGame.h"
#include "src/ReactionGame.h"
#include "src/MixLaboratory.h"
#include "src/Encrypted.h"
#include "src/OddOneGame.h"
#include "src/mathDuel.h"
#include "src/galactic_escape.h"
#include "src/Utils.h"


using namespace std;



void Game::start() {
    showMainMenu();

    // Array of planets to visit
    string planets[] = {"Mercury", "Venus", "Mars", "Jupiter", "Neptune"};
    int totalPlanets = 5;
    int currentPlanet = 0;

    // Visit each planet in sequence
    while (player.isAlive() && currentPlanet < totalPlanets) {
        cout << "\n=== PLANET " << (currentPlanet + 1) << " OF " << totalPlanets << " ===" << endl;
        bool success = visitPlanet(planets[currentPlanet]);
        
        if (success) {
            cout << "\nCongratulations! You've completed " << planets[currentPlanet] << "!" << endl;
            currentPlanet++;
            
            if (currentPlanet < totalPlanets) {
                cout << "Preparing to travel to " << planets[currentPlanet] << "..." << endl;
            }
        } else {
            cout << "Try again...\n";
        }
    }

    if (!player.isAlive()) {
        cout << "\nYou have no lives left. Game over." << endl;
    } else {
        cout << "\n🎉 CONGRATULATIONS! 🎉" << endl;
        cout << "You've completed your journey through all " << totalPlanets << " planets!" << endl;
        cout << "Final score: " << player.getMoney() << " coins" << endl;
    }
}

void Game::showMainMenu() {
    system("chcp 65001 > nul"); // Change to UTF-8
    system("cls"); // clean the window.

    setColor(11); // Blue
    cout << "╔════════════════════════════════╗" << endl;
    cout << "║        🌌 STAR GUARDIAN       ║" << endl;
    cout << "╠════════════════════════════════╣" << endl;
    cout << "║  1. 🚀 Start Adventure         ║" << endl;
    cout << "║  2. ❌ Exit                    ║" << endl;
    cout << "╚════════════════════════════════╝" << endl;
    setColor(7); // come back to grey color

    cout << "Choose an option: ";

    int option;
    cin >> option;

    if (option == 1) {
        cout << "\nStarting your galactic mission..." << endl;
        Sleep(1000); 
    } else {
        cout << "\nGoodbye, Guardian." << endl;
        exit(0); 
    }
}

bool Game::visitPlanet(const string& planetName) {
    
    cout << "\nArriving at planet: " << planetName << endl;
    
    // Different descriptions for each planet
    if (planetName == "Mercury") {
        cout << "The closest planet to the sun. Extreme temperatures await..." << endl;
    } else if (planetName == "Venus") {
        cout << "The hottest planet in our solar system. Acid rain falls from toxic clouds..." << endl;
    } else if (planetName == "Mars") {
        cout << "The red planet. Ancient ruins and mysterious signals detected..." << endl;
    } else if (planetName == "Jupiter") {
        cout << "The largest planet. Massive storms rage across its surface..." << endl;
    }
    
    cout << "You must choose a path:" << endl;
    
    // Different path options for each planet
    if (planetName == "Mercury") {
        cout << "1. Path through solar flares (leads to Memory Game)" << endl;
        cout << "2. Path through meteor shower (leads to Reaction Game)" << endl;
    } else if (planetName == "Venus") {
        cout << "1. Path through acid rain (leads to Memory Game)" << endl;
        cout << "2. Path through toxic clouds (leads to Reaction Game)" << endl;
    } else if (planetName == "Mars") {
        cout << "1. Path through sandstorm (leads to Memory Game)" << endl;
        cout << "2. Path through ancient ruins (leads to Reaction Game)" << endl;
    } else if (planetName == "Jupiter") {
        cout << "1. Path through the Great Red Spot (leads to Memory Game)" << endl;
        cout << "2. Path through gas storms (leads to Reaction Game)" << endl;
    }
    
    cout << "Choose your path (1 or 2): ";

    int choice;
    cin >> choice;

    bool result = false;

    if (choice == 1) {
        // Different entry messages for each planet
        if (planetName == "Mercury") {
            cout << "You navigate through intense solar flares..." << endl;
         result = memoryGame();
        } else if (planetName == "Venus") {
            cout << "You brave the corrosive acid rain..." << endl;
            result= PlayMixLaboratory();
        } else if (planetName == "Mars") {
            cout << "You push through the blinding sandstorm..." << endl;
            result = oddOneGame();
        } else if (planetName == "Jupiter") {
            cout << "You enter the massive Great Red Spot..." << endl;
            result = galactic_escape_play();
        }
        

    } else if (choice == 2) {
        // Different entry messages for each planet
        if (planetName == "Mercury") {
            cout << "You dodge through the meteor shower..." << endl;
            result = reactionGame();
        } else if (planetName == "Venus") {
            cout << "You fly through the toxic cloud layers..." << endl;
             result = encryptedGame();

        } else if (planetName == "Mars") {
            cout << "You explore the mysterious ancient ruins..." << endl;
            result = MathDuel();
        } else if (planetName == "Jupiter") {
            cout << "You navigate through the violent gas storms..." << endl;
        }else if (planetName == "Neptune") {
           cout << "\n🌌 Welcome to Neptune... the Final Frontier." << endl;
           cout << "This is your last challenge. No second chances." << endl;
           cout << "Are you ready for the final challenge? Press X to begin..." << endl;

           char input;
           cin >> input;
           if (input != 'x' && input != 'X') {
               cout << "You hesitated. The challenge fades away..." << endl;
                return false;
            }

           // Final challenge minigame
          //result = finalBossMinigame(); // In this part you will put the minigame 
}
       // read this: Connect the real reaction game function here
        
    } else {
        cout << "Invalid choice. You hesitate and lose a turn." << endl;
        player.loseLife();
        return false;
    }

    if (result) {
        // Different rewards for each planet
        int reward = 50;
        if (planetName == "Venus") reward = 75;
        else if (planetName == "Mars") reward = 100;
        else if (planetName == "Jupiter") reward = 150;
        
        // Player won the minigame
        player.earnMoney(reward);
        cout << "You won the challenge! +" << reward << " coins." << endl;
        return true; // Allow to continue to next planet
    } else {
        // Player lost the minigame
        player.loseLife();
        cout << "You failed the challenge. -1 life." << endl;
        return false; // Stay on the same planet and retry
    }
}
