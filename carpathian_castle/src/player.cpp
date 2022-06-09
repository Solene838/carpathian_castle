#include "Player.h"
#include "Textbox.h"

Player::Player(int x, int y, int health) :
	x(x),
	y(y),
	health(health)
{
}

int Player::getX() const {
	return x;
}

int Player::getY() const {
	return y;
}

int Player::getHealth() const {
	return health;
}

void Player::setHealth(int new_health) {
	health = new_health;
}

std::vector<Pickable>& Player::getInventory() {
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

bool Player::isOnPeaks(MapLayer& peaks) const {
	int x_tile = int(x / 16) + 1;
	int y_tile = int(y / 16) + 1;
	tmx::TileLayer::Tile tile = peaks.getTile(x_tile, y_tile);
	if (tile.ID != NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::doEnigma() const {
	std::cerr << "In enigma function of player" << std::endl;
	std::cerr << "This object is locked : you need to resolve an enigma" << std::endl;
	sf::RenderWindow window(sf::VideoMode(450, 550), "Enigma window");

	sf::Font script;
	script.loadFromFile("resources/Alexbrush-Regular.ttf");
	sf::Font arial;
	arial.loadFromFile("resources/arial.ttf");


	Textbox textbox(20, sf::Color::Red, false);
	textbox.setFont(arial);
	textbox.setPosition({ 100, 300 });
	textbox.setLimit(true, 10);
	textbox.setRect(100, 300, 30, 200);

	sf::RectangleShape inputBox;
	inputBox.setSize({ 200, 30 });
	inputBox.setPosition(100, 300);
	inputBox.setFillColor(sf::Color::White);


	bool is_resolved = false;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				return is_resolved;

			case sf::Event::TextEntered:
				textbox.typedOn(event);

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Return) {
					if (textbox.getText() == "un marron") {
						is_resolved = true;
						return is_resolved;
					}
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					textbox.setSelected(false);
				}
			}

			if(event.type == sf::Event::MouseButtonPressed) {
				int pos_x = event.mouseButton.x;
				int pos_y = event.mouseButton.y;
				if (textbox.getRect().contains(pos_x, pos_y)) {
					std::cerr << "in containing loop" << std::endl;
					textbox.setSelected(true);
				}
				else {
					textbox.setSelected(false);
				}
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
			for (int i = 0; i < 23; i++) {
				result = result + current[i];
			}
			result = result + "\n";
			std::string tmp;
			for (int j = 23; j < current.size(); j++) {
				tmp = tmp + current[j];
			}
			current = tmp;
		}
		result = result + current;

		enigma.setString(result);

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(enigma);
		window.draw(inputBox);
		textbox.drawTo(window);
		window.display();
	}
}
