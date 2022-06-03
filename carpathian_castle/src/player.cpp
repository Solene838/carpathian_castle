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

	sf::Font script;
	script.loadFromFile("resources/Alexbrush-Regular.ttf");
	sf::Font arial;
	arial.loadFromFile("resources/arial.ttf");
	sf::String playerInput;
	sf::Text playerText;
	playerText.setFont(arial);
	playerText.setCharacterSize(40);
	playerText.setStyle(sf::Text::Regular);
	playerText.setFillColor(sf::Color::Black);
	playerText.setPosition(80, 300);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				playerInput += event.text.unicode;
				playerText.setString(playerInput);
			}
		}

		sf::Sprite sprite;
		sf::Texture texture;
		texture.loadFromFile("resources/Sprite/parchemin.png");
		sprite.setTexture(texture);
		sprite.setScale(0.1, 0.1);


		sf::Text enigma;
		enigma.setString("Qu'est-ce qui est petit et marron ?");
		enigma.setFont(script);
		enigma.setCharacterSize(40);
		enigma.setStyle(sf::Text::Regular);
		enigma.setFillColor(sf::Color::Black);
		enigma.setPosition(80, 100);

		//Test of data
		/*int size_window_px = 450;
		int size_window_char = size_window_px / enigma.getCharacterSize();
		std::cerr << "Taille fenetre pixel : " << size_window_px << std::endl;
		std::cerr << "Taille fenetre nb char : " << size_window_char << std::endl;*/

		//Check if the text is too wide for the screen
		std::string result;
		std::string current = enigma.getString();
		while (current.size() > 23) {
			//std::cerr << "Size of current string : " << current.size() << std::endl;
			for (int i = 0; i < 23; i++) {
				result = result + current[i];
				//std::cerr << "result : " << result << std::endl;
			}
			result = result + "\n";
			std::string tmp;
			for (int j = 23; j < current.size(); j++) {
				tmp = tmp + current[j];
				//std::cerr << "tmp : " << tmp << std::endl;
			}
			current = tmp;
		}
		result = result + current;

		enigma.setString(result);

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(enigma);
		window.draw(playerText);
		window.display();
	}
}
