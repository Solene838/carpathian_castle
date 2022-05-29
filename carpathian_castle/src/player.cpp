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
	if ((x - 10) >= 0) {
		x += -10;
	}
}

void Player::goRight() {
	if ((x + 10) <= 620) {
		x += 10;
	}
}
