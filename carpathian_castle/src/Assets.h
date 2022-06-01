#pragma once
#include <SFML/Graphics.hpp>

class Assets {
public:
	bool operator==(const Assets&) const = default;
	Assets();
	sf::Texture bookBlue;
	const std::map<std::string, sf::Texture>& getTexturesMap() const;
	void addToMap(std::string label);
private:
	std::map<std::string, sf::Texture> textures;
};