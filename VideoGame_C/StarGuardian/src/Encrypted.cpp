#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Encrypted.h"
#include <windows.h>
#include "Utils.h"

// choose a random word from the list 
std::string getRandomWord(const std::vector<std::string>& wordList) {
    return wordList[rand() % wordList.size()];
}

// Mix the letters of the word
std::string shuffleLetters(const std::string& word) {
    std::string shuffled = word;
    for (size_t i = 0; i < shuffled.size(); ++i) {
        int j = rand() % shuffled.size();
        char temp = shuffled[i];
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
    }
    return shuffled;
}

// Compare if the answer is the same as the original
bool checkAnswer(const std::string& original, const std::string& answer) {
    return original == answer;
}

// Main game logic
bool encryptedGame() {  
    srand((unsigned)time(0));
    std::vector<std::string> wordList = {"ASTEROID", "ASTRONAUT", "ATMOSPHERE", "PLANETARY", "ENIGMA", "GUARDIAN"};
    int maxAttempts = 3;
    int level = 1;
    bool exitGame = false;

    setColor(14); // Blue
std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
setColor(12); // Yellow (ASCII)
std::cout << R"(
   __                            _           _     ___                     
  /__\ __   ___ _ __ _   _ _ __ | |_ ___  __| |   / _ \__ _ _ __ ___   ___ 
 /_\| '_ \ / __| '__| | | | '_ \| __/ _ \/ _` |  / /_\/ _` | '_ ` _ \ / _ \
//__| | | | (__| |  | |_| | |_) | ||  __/ (_| | / /_\\ (_| | | | | | |  __/
\__/|_| |_|\___|_|   \__, | .__/ \__\___|\__,_| \____/\__,_|_| |_| |_|\___|
                     |___/|_|                                              
)" << std::endl;
setColor(14); // Blue
std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
setColor(7); // Reset

    std::cout << "Decode the secret word to leave the planet.\n";

    while (!exitGame) {
        // Choose a random word and remove it from the vector to avoid repetition.
        int idx = rand() % wordList.size();
        std::string word = wordList[idx];
        wordList.erase(wordList.begin() + idx);
        std::string encrypted = shuffleLetters(word);
        int attempts = 0;
        std::cout << "\nLevel " << level << ": " << encrypted << std::endl;
        bool correct = false;
        while (attempts < maxAttempts && !correct) {
            std::cout << "Try number " << (attempts + 1) << ": ";
            std::string answer;
            std::cin >> answer;
            for (char& c : answer) c = toupper(c);
            if (checkAnswer(word, answer)) {
                std::cout << "Correct!\n";
                correct = true;
                level++;
            } else {
                std::cout << "Incorrect.\n";
                attempts++;
            }
        }
        if (!correct) {
            std::cout << "You failed. The correct word was: " << word << "\n";
            return false;
        } else if (level > 5 || wordList.empty()) {
            std::cout << "Congratulations! You escape the planet.\n";
            return true;
        }
    }
}




