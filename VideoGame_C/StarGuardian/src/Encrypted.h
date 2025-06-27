#ifndef ENCRYPTED_H
#define ENCRYPTED_H

#include <string>
#include <vector>

std::string getRandomWord(const std::vector<std::string>& wordList);
std::string shuffleLetters(const std::string& word);
bool checkAnswer(const std::string& original, const std::string& answer);
bool encryptedGame();

#endif