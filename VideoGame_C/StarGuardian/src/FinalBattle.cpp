#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "finalbattle.h"

using namespace std;

// Function Declarations
string generateDirection();
void displayEnergy(int energy);
bool processShot(const string& enemyDirection, const string& shot);


string generateDirection() {
    vector<string> directions = {"N", "S", "E", "W"};
    int index = rand() % directions.size();
    return directions[index];
}

void displayEnergy(int energy) {
    const int maxEnergy = 10;
    cout << "Energy: [";
    for (int i = 0; i < maxEnergy; i++) {
        if (i < energy)
            cout << "#";  
        else
            cout << ".";
    }
    cout << "] " << energy << "/" << maxEnergy << endl;
}



bool processShot(const string& enemyDirection, const string& shot) {
    return enemyDirection == shot;
}

bool finalBattle(){ 
    srand(time(0));

    const int maxEnergy = 10;
    int energy = maxEnergy;
    int dronesDestroyed = 0;
    const int totalDrones = 7;

    cout << "=== FINAL BATTLE: ORBITAL DEFENSE ===\n";
    cout << "It weird, you enter pluton but nobody is here, maybe they set a trap for me\n";
    cout << "I better do this quick\n";
    cout << "You have reached the relic... but IT WAS AN AMBUSH AND ENEMY DRONES ARE ATTACKING!\n";
    cout << "Protect the relic and shoot down incoming threats.\n";
    cout << "Enter direction (N/S/E/W) to fire.\n\n";

    for (int i = 1; i <= totalDrones && energy > 0; i++) {
        string enemyDirection = generateDirection();

        cout << "\nEnemy Drone #" << i << " detected in an unknown direction...\n";
        displayEnergy(energy);
        cout << "Which direction do you shoot? (N/S/E/W): ";

        string shot;
        cin >> shot;
        for (char& c : shot) c = toupper(c);

        if (processShot(enemyDirection, shot)) {
            cout << "Hit! Drone destroyed.\n";
            dronesDestroyed++;
        } else {
            cout << "Missed! The drone was approaching from " << enemyDirection << ".\n";
            energy--;
        }
    }

    cout << "\n=== FINAL RESULTS ===\n";
    cout << "Drones destroyed: " << dronesDestroyed << " out of " << totalDrones << endl;
    if (energy > 0) {
        cout << "Tactical victory! The relic is safe.\n" << endl;
        cout << "CONGRATULATIONS STAR GUARDIAN, you have made it" << endl;
        cout << "The solar system is no longer in danger and the earth is completely grateful for your bravery throughout the story" << endl;
        cout << "You have acquired a trophy" << endl;
        cout << " _-_Cosmic defender_-_ " << endl;
        return true;
    } else {
        cout << "You've lost all energy... The orbit has been breached.\n";
        return false;
    }

    return 0;
}

