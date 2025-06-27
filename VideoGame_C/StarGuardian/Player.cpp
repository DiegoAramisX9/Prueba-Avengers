#include "src/Player.h"

Player::Player() {
    lives = 3;
    money = 0;
}

void Player::loseLife() {
    if (lives > 0) lives--;
}

void Player::earnMoney(int amount) {
    money += amount;
}

void Player::loseMoney(int amount) {
    if (money >= amount) money -= amount;
    else money = 0;
}

int Player::getLives() const {
    return lives;
}

int Player::getMoney() const {
    return money;
}

bool Player::isAlive() const {
    return lives > 0;
}
