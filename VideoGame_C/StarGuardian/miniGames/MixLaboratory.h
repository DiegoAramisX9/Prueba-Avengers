#ifndef MIX_LABORATORY_H
#define MIX_LABORATORY_H

// Control the formula size and number of attempts
#define FORMULA_SIZE 3     // Number of ingredients in the formula
#define MAX_ATTEMPTS 5     // Maximum number of player attempts

// Function prototypes (declarations)
void generateSecretFormula(int formula[]);
// Generates a random formula with ingredients between 1 and 5

void askPlayerMix(int mix[]);
// Asks the player to enter a sequence of ingredients

bool compareFormulas(const int formula[], const int mix[]);
// Compares the secret formula with the player's mix and returns true if they match

void showFeedback(const int formula[], const int mix[]);
// Gives a message according to the error detected in the player's mix

bool PlayMixLaboratory(); // Declaration of the main minigame function

#endif