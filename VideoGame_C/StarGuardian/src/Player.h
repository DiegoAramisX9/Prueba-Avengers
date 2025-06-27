#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int lives;
    int money;

public:
    Player();
    void loseLife();
    void earnMoney(int amount);
    void loseMoney(int amount);
    int getLives() const;
    int getMoney() const;
    bool isAlive() const;
};

#endif
