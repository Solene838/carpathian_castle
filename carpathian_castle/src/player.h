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
	int health;
	std::vector<Pickable> inventory;
public:
	bool operator==(const Player&) const = default;
	Player(int x, int y, int health);
	int getX() const;
	int getY() const;
	int getHealth() const;
	void setHealth(int new_health);
	std::vector<Pickable>& getInventory();
	void goLeft(MapLayer& ground);
	void goRight(MapLayer& ground);
	void goUp(MapLayer& ground);
	void goDown(MapLayer& ground);
	bool isNearDoor(MapLayer& doors) const;
	bool isOnPeaks(MapLayer& peaks) const;
	bool doEnigma() const;
};
