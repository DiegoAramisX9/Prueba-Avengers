#ifndef FINAL_BATTLE_H
#define FINAL_BATTLE_H

#include <string>


std::string generateDirection();
void displayEnergy(int energy);
bool processShot(const std::string& enemyDirection, const std::string& shot);
bool finalBattle();

#endif