#include "player.h"

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

void Player::goLeft() {
	x += -10;
}

void Player::goRight() {
	x += 10;
}
