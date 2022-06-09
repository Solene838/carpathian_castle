#include "GameState.h"
#include "Button.h"
#include "Door.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "SFMLOrthogonalLayer.h"


GameState::GameState() : stateName{ "gameState" } {}

void GameState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) {}


//-----------------------------------

MenuOpenState::MenuOpenState() : stateName{ "menuOpenState" } {}

void MenuOpenState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room)
{
	view->setCenter(390, 176);
	window->clear(sf::Color::Black);
	std::cout << "Menu open state\n";
}

//-----------------------------------

Room1OpenState::Room1OpenState() : stateName{ "room1OpenState" } {}

void Room1OpenState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room)
{
    if (player->getY() > 330) {
        id_room = (int*)1;
        view->setCenter(390, 500);
    }

    if (player->getY() < 350) {
        id_room = (int*)2;
        view->setCenter(390, 176);
    }
	std::cout << "Room 1 open state\n";
}

//-----------------------------------

Room2OpenState::Room2OpenState() : stateName{ "room2OpenState" } {}

void Room2OpenState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room)
{
	std::cout << "Room 2 open state\n";
}

//-----------------------------------

NoRoomOpenState::NoRoomOpenState() : stateName{ "noRoomOpenState" } {}

void NoRoomOpenState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room)
{
	std::cout << "No room open state\n";
}

//-----------------------------------

PauseMenuOpenState::PauseMenuOpenState() : stateName{ "pauseMenuOpenState" } {}

void PauseMenuOpenState::stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room)
{
	std::cout << "Pause menu open state\n";
}