#pragma once
#include "Object.h"
#include <vector>

class Player {
private:
	int x;
	int y;
	std::vector<Object> inventory;
public:
	bool operator==(const Player&) const = default;
	Player(int x, int y);
	int getX() const;
	int getY() const;
	std::vector<Object>& getInventory();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};
