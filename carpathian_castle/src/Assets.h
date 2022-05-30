#pragma once
#include <SFML/Graphics.hpp>

class Assets {
public:
	bool operator==(const Assets&) const = default;
	Assets();
	sf::Texture bookBlue;
	sf::Texture bookGreen;
	sf::Texture bookRed;
	sf::Texture largePosterBottom;
	sf::Texture largePosterTop;
	sf::Texture poster;
	sf::Texture purse;
	sf::Texture skull;
};