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
#include "src/FinalBattle.h"

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
        cout << "\nPreparing the ship for your galactic mission, fasten your seatbelts and get ready..." << endl;
        Sleep(1000); 
    } else {
        cout << "\nGoodbye Guardian, see you on your next space mission.." << endl;
        exit(0); 
    }
}

bool Game::visitPlanet(const string& planetName) {
    
    cout << "\nArriving at planet: " << planetName << endl;
    bool result = false;
    // === SPECIAL FINAL PLANET: NEPTUNE ===
    if (planetName == "Neptune") {
        cout << "\n🌌 Finally, you reach Neptune... the final frontier. Here, you will put everything you've learned on your journey to the test. The fate of the universe depends on you. If you can overcome this challenge, order will be restored, and your name will be remembered as the Guardian who saved the galaxy. We trust in you, Guardian." << endl;
        cout << "This is your final challenge; your spacesuit is about to break. There are no second chances." << endl;
        cout << "Ready for the final challenge? It's the step to complete your mission. Be very careful, there's a lot to be learned at this point. Press X to begin..." << endl;

        char input;
        cin >> input;

        if (input != 'x' && input != 'X') {
            cout << "You hesitated. The challenge fades away..." << endl;
            player.loseLife();
            return false;
        }

        // Final minigame execution
          result = finalBattle();

        if (result) {
            int reward = 200;
            player.earnMoney(reward);
            cout << "Congratulations, Guardian! You've won the final challenge! Your name will be remembered throughout space for a lifetime. +200 coins." << endl;
            return true;
        } else {
            player.loseLife();
            cout << "You failed the final battle. -1 life." << endl;
            return false;
        }
    }

    // Different descriptions for each planet
    if (planetName == "Mercury") {
        cout << "The universe is in danger, and only a Guardian can restore order. Your mission begins on Mercury, where extreme heat challenges your resolve and marks the beginning of your journey for galactic peace." << endl;
    } else if (planetName == "Venus") {
        cout << "After passing Mercury, you reach Venus. Toxic clouds and acid rain test your ingenuity as you advance in your mission to restore harmony to the cosmos." << endl;
    } else if (planetName == "Mars") {
        cout << "On Mars, ancient ruins and mysterious signs remind you that chaos threatens even lost civilizations. Your courage and purpose grow stronger with every step." << endl;
    } else if (planetName == "Jupiter") {
        cout << "Jupiter, the storm giant, is your last stop before your final destination. Here, the challenges are colossal, but your Guardian spirit shines brighter than ever in defense of universal balance." << endl;
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

    

    if (choice == 1) {
        // Different entry messages for each planet
        if (planetName == "Mercury") {
            cout << "In one corner of the universe, balance is at stake. As a Space Ranger, your mission is to restore order and protect galactic peace. Your journey begins on Mercury, the fiery sentinel of the solar system. The extreme heat tests your ship and your courage, but you know that every mission begins with a brave first step." << endl;
         result = memoryGame();
        } else if (planetName == "Venus") {
            cout << "After overcoming the trials of Mercury, you arrive on Venus. Toxic clouds and acid rain hide ancient secrets. Here, the Guardian must rely on their wits to navigate the beauty and danger, while the forces of chaos lurk in the shadows." << endl;
            result= PlayMixLaboratory();
        } else if (planetName == "Mars") {
            cout << "The journey takes you to Mars, the red planet. Amidst forgotten ruins and mysterious signs, you feel you are not alone. Every step reveals fragments of a lost civilization and unexpected challenges, but your determination to restore order does not waver." << endl;
            result = oddOneGame();
        } else if (planetName == "Jupiter") {
            cout << "Your ship is approaching Jupiter, the giant of eternal storms. Colossal lightning and winds threaten your mission, but the hope of restoring harmony to the universe drives you forward, facing your greatest dangers yet." << endl;
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
        }
       // read this: Connect the real reaction game function here
        
    }else {
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
