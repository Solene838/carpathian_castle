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

void Player::goLeft(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_left = ground.getTile(x_tile - 1, y_tile);
	if (tile_left.ID != NULL) {
		x += -10;
	}
}

void Player::goRight(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_right = ground.getTile(x_tile + 1, y_tile);
	if (tile_right.ID != NULL) {
		x += 10;
	}
}

void Player::goUp(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_up = ground.getTile(x_tile, y_tile - 1);
	if (tile_up.ID != NULL) {
		y += -10;
	}
}

void Player::goDown(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_down = ground.getTile(x_tile, y_tile + 1);
	if (tile_down.ID != NULL) {
		y += 10;
	}
}
