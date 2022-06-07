#pragma once
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>

class Text {
private :
	std::string label;
	sf::Text text;

public:
	explicit Text(std::string label);
	void setParameters(std::string display, sf::Font font, int characterSize, sf::Text::Style style, sf::Color color);
	std::string& getLabel();
	sf::Text& getText();
};