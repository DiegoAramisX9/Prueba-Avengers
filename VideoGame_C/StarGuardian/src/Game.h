#ifndef GAME_H
#define GAME_H

#include <string>
#include "Player.h"


using namespace std;

class Game {
private:
    Player player;

public:
    void start();
    void showMainMenu();
    bool visitPlanet(const string& planetName);
};

#endif
