#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include "Button.h"

class GameState {
private:
	std::string stateName;

public:
    GameState();
    virtual void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room);
    std::string getName() const { return stateName; };
};

//main menu is open
class MenuOpenState : public GameState {
private:
    std::string stateName;
public:
    MenuOpenState();
    void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) override;
};

//main menu is close, and room1 is open
class Room1OpenState : public GameState {
private:
    std::string stateName;
public:
    Room1OpenState();
    void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) override;
};

//main menue is close, and room2 is open
class Room2OpenState : public GameState {
private:
    std::string stateName;
public:
    Room2OpenState();
    void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) override;
};

//main menu is close, and no room is open
class NoRoomOpenState : public GameState {
private:
    std::string stateName;
public:
    NoRoomOpenState();
    void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) override;
};

//main menu is close, and pause menu is open
class PauseMenuOpenState : public GameState {
private:
    std::string stateName;
public:
    PauseMenuOpenState();
    void stateExecute(Player* player, sf::RenderWindow* window, sf::View* view, Button* btn, int* id_room) override;
};