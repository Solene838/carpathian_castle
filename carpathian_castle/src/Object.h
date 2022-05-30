#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

class Object {
private:
	int x;
	int y;
	std::string label;
	sf::IntRect boxCollider;
	sf::Sprite sprite;

public:
	bool operator==(const Object&) const = default;
	Object(int x, int y, const std::string& label);
	void setSprite(const std::string& name, const Assets& gameAssets);
	sf::Sprite getSprite() const;
	std::string getLabel() const;
	sf::IntRect getBoxCollider() const;
	int getX() const;
	int getY() const;
};