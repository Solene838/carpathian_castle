#include "Player.h"

Player::Player(int x, int y) :
	x(x),
	y(y)
{
}

int Player::getX() const {
	return x;
}

int Player::getY() const {
	return y;
}

std::vector<Object>& Player::getInventory() {
	return inventory;
}

void Player::goLeft() {
	if ((x - 10) >= 0) {
		x += -10;
	}
}

void Player::goRight() {
	if ((x + 10) <= 620) {
		x += 10;
	}
}

void Player::goUp() {
	if ((y - 10) >= 0) {
		y += -10;
	}
}

void Player::goDown() {
	if ((y + 10) <= 320) {
		y += 10;
	}
}
