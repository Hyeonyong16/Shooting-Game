#pragma once
#include "Entity.h"

enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

class Hero :public Entity {
	bool isDash;
	int moveSpeed;
public:
	void move(int i);
	void setDash(bool dash);
	bool getDash();

	void setSpeed(int speed);
	int getSpeed();

	void init(float x, float y);
};

