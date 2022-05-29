#pragma once

class Player {
private:
	int x;
	int y;
public:
	bool operator==(const Player&) const = default;
	Player(int x, int y);
	int getX() const;
	int getY() const;
	void goLeft();
	void goRight();
};
