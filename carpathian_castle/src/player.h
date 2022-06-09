#pragma once
#include "Pickable.h"
#include <vector>
#include <iostream>
#include "SFMLOrthogonalLayer.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Player {
private:
	int x;
	int y;
	std::vector<Pickable> inventory;
public:
	bool operator==(const Player&) const = default;
	Player(int x, int y);
	int getX() const;
	int getY() const;
	std::vector<Pickable>& getInventory();
	void goLeft(MapLayer& ground);
	void goRight(MapLayer& ground);
	void goUp(MapLayer& ground);
	void goDown(MapLayer& ground);
	bool isNearDoor(MapLayer& doors) const;
	bool doEnigma() const;
};
