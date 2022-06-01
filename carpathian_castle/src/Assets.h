#pragma once
#include <SFML/Graphics.hpp>

class Assets {
public:
	bool operator==(const Assets&) const = default;
	Assets();
	const std::map<std::string, sf::Texture>& getTexturesMap() const;
	void addToMap(std::string label);
	/*sf::Texture bookBlue;
	sf::Texture bookGreen;
	sf::Texture bookRed;
	sf::Texture largePosterBottom;
	sf::Texture largePosterTop;
	sf::Texture poster;
	sf::Texture purse;
	sf::Texture skull;*/
private:
	std::map<std::string, sf::Texture> textures;
};