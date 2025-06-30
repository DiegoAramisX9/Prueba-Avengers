#include "src/Game.h"
#include <cstdlib>  // srand and rand
#include <ctime>    // time

int main() {
    // Seed the random generator
    srand(time(0));
    Game game;
    game.start();
    return 0;
}
