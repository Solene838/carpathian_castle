#pragma once
#include "Object.h"
#include <vector>
#include <iostream>
#include "SFMLOrthogonalLayer.h"

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
	void goLeft(MapLayer& ground);
	void goRight(MapLayer& ground);
	void goUp(MapLayer& ground);
	void goDown(MapLayer& ground);
	bool isNearDoor(MapLayer& doors);
};
