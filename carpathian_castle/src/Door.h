#pragma once
#include "Object.h"

class Door : public Object {
private:
	int room;

public:
	Door(int x, int y, const std::string& label, const std::string& category, int room);
	explicit Door(const pugi::xml_node& node);
	int getRoom() override;
};