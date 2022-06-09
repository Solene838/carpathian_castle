#include "GameState.h"
#include <iostream>


PlayerState::PlayerState() : stateName{ "gameState" } {}

void PlayerState::stateExecute(Player* player, sf::RenderWindow* window) {}


//-----------------------------------

MenuOpenState::MenuOpenState() : stateName{ "menuOpenState" } {}

void MenuOpenState::stateExecute(Player* player, sf::RenderWindow* window)
{
	std::cout << "Menu open state\n";
}

//-----------------------------------

Room1OpenState::Room1OpenState() : stateName{ "room1OpenState" } {}

void Room1OpenState::stateExecute(Player* player, sf::RenderWindow* window)
{
	std::cout << "Room 1 open state\n";
}

//-----------------------------------

Room2OpenState::Room2OpenState() : stateName{ "room2OpenState" } {}

void Room2OpenState::stateExecute(Player* player, sf::RenderWindow* window)
{
	std::cout << "Room 2 open state\n";
}

//-----------------------------------

NoRoomOpenState::NoRoomOpenState() : stateName{ "noRoomOpenState" } {}

void NoRoomOpenState::stateExecute(Player* player, sf::RenderWindow* window)
{
	std::cout << "No room open state\n";
}

//-----------------------------------

PauseMenuOpenState::PauseMenuOpenState() : stateName{ "pauseMenuOpenState" } {}

void PauseMenuOpenState::stateExecute(Player* player, sf::RenderWindow* window)
{
	std::cout << "Pause menu open state\n";
}