#include "Player.h"

Player::Player(int x, int y) :
	x(x),
	y(y)
{
}

int Player::getX() const {
	return x;
}

int Player::getY() const {
	return y;
}

std::vector<Object>& Player::getInventory() {
	return inventory;
}

void Player::goLeft(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_left = ground.getTile(x_tile - 1, y_tile);
	if (tile_left.ID != NULL) {
		x += -10;
	}
}

void Player::goRight(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_right = ground.getTile(x_tile + 1, y_tile);
	if (tile_right.ID != NULL) {
		x += 10;
	}
}

void Player::goUp(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_up = ground.getTile(x_tile, y_tile - 1);
	if (tile_up.ID != NULL) {
		y += -10;
	}
}

void Player::goDown(MapLayer& ground) {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile_down = ground.getTile(x_tile, y_tile + 1);
	if (tile_down.ID != NULL) {
		y += 10;
	}
}

bool Player::isNearDoor(MapLayer& doors) const {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile = doors.getTile(x_tile, y_tile);
	tmx::TileLayer::Tile tile_left = doors.getTile(x_tile - 1, y_tile);
	tmx::TileLayer::Tile tile_right = doors.getTile(x_tile + 1, y_tile);
	tmx::TileLayer::Tile tile_up = doors.getTile(x_tile, y_tile - 1);
	tmx::TileLayer::Tile tile_down = doors.getTile(x_tile, y_tile + 1);
	if (tile.ID != NULL || tile_left.ID != NULL || tile_right.ID != NULL || tile_up.ID != NULL || tile_down.ID != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void Player::doEnigma() const {
	std::cerr << "In enigma function of player" << std::endl;
	std::cerr << "This object is locked : you need to resolve an enigma" << std::endl;
	sf::RenderWindow window(sf::VideoMode(450, 550), "Enigma window");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Sprite sprite;
		sf::Texture texture;
		texture.loadFromFile("resources/Sprite/parchemin.png");
		sprite.setTexture(texture);
		sprite.setScale(0.1, 0.1);

		sf::Font script;
		script.loadFromFile("resources/Alexbrush-Regular.ttf");
		sf::Text enigma;
		enigma.setString("Qu'est-ce qui est petit et marron ?");
		enigma.setFont(script);
		enigma.setCharacterSize(40);
		enigma.setStyle(sf::Text::Regular);
		enigma.setFillColor(sf::Color::Red);
		enigma.setPosition(80, 100);

		//Check if the text is too wide for the screen
		size_t size = enigma.getString().getSize();
		int nb_char = 550 / 40;
		std::cerr << "size of string : " << size << std::endl;
		for (int i = 0; i < (int)size; i++) {
			size_t index = i;
			std::cerr << "index : " << index << std::endl;
			if (enigma.findCharacterPos(index).x >= 23) {
				std::cerr << "in if loop" << std::endl;
				std::string tmp = enigma.getString();
				std::cerr << "tmp before insert : " << tmp << std::endl;
				tmp.insert(index, "\n");
				std::cerr << "tmp after insert : " << tmp << std::endl;
				enigma.setString(tmp);
				break;
			}
		}

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(enigma);
		window.display();
	}
}
