#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include "MixLaboratory.h"

using namespace std;

// Generates a random secret formula
void generateSecretFormula(int formula[]) {
    srand(time(0)); // Initialize random seed
    for (int i = 0; i < FORMULA_SIZE; ++i) {
        formula[i] = rand() % 5 + 1; // Ingredients between 1 and 5
    }
}

// Asks the player to enter their mix
void askPlayerMix(int mix[]) {
    cout << "\nEnter your mix of " << FORMULA_SIZE << " ingredients (from 1 to 5):\n";
    for (int i = 0; i < FORMULA_SIZE; ++i) {
        cout << "Ingredient " << i + 1 << ": ";
        cin >> mix[i];
    }
}

// Compares the player's mix with the secret formula
bool compareFormulas(const int formula[], const int mix[]) {
    for (int i = 0; i < FORMULA_SIZE; ++i) {
        if (mix[i] != formula[i]) {
            return false;
        }
    }
    return true;
}

// Shows an error message depending on the failure
void showFeedback(const int formula[], const int mix[]) {
    for (int i = 0; i < FORMULA_SIZE; ++i) {
        if (mix[i] != formula[i]) {
            switch (i) {
                case 0:
                    cout << "Error in the first ingredient: the mix exploded!\n" << endl;
                    break;
                case 1:
                    cout << "Second ingredient incorrect: mysterious smoke appears!" << endl;
                    break;
                case 2:
                    cout << "Third ingredient failed: unstable mix!" << endl;
                    break;
                default:
                    cout << "Incorrect mix." << endl ;
            }
            return;
        }
    }
}

// Main function of the minigame to call from your main game
bool PlayMixLaboratory() {
    int formula[FORMULA_SIZE];
    int mix[FORMULA_SIZE];
    int attempts = 0;

    cout << " Welcome to the Mix Laboratory: Secret Formulas! \n";

    generateSecretFormula(formula);

    while (attempts < MAX_ATTEMPTS) {
        cout << "\nAttempt #" << (attempts + 1) << " of " << MAX_ATTEMPTS << ":\n";
        askPlayerMix(mix);

        if (compareFormulas(formula, mix)) {
            cout << "Correct formula! You win!\n";
            return true;
        } else {
            showFeedback(formula, mix);
            attempts++;
        }
    }

    cout << "You've used all your attempts!\n";
    cout << "The secret formula was: ";
    for (int i = 0; i < FORMULA_SIZE; ++i) {
        cout << formula[i] << " ";
    }
    cout << "\nBetter luck next time!\n";
    return false;
}