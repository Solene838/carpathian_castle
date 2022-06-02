#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include <pugixml.hpp>

class Object {
private:
	int x;
	int y;
	std::string label;
	std::string category;
	sf::IntRect boxCollider;
	sf::Sprite sprite;
	bool is_locked;

public:
	bool operator==(const Object&) const = default;
	Object(int x, int y, const std::string& label, const std::string& category);
	explicit Object(pugi::xml_node node);
	void setSprite(const sf::Texture& texture);
	sf::Sprite& getSprite();
	std::string getLabel() const;
	sf::IntRect getBoxCollider() const;
	int getX() const;
	int getY() const;
	std::string getCategory() const;
	bool getLock() const;
};