#pragma once
#include "GameState.h"

class GameStates {
public:
	static MenuOpenState menu_open;
	static Room1OpenState room1_open;
	static Room2OpenState room2_open;
	static NoRoomOpenState no_room_open;
	static PauseMenuOpenState pause_menu;
};