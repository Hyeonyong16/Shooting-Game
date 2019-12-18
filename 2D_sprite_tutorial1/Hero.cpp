#include "Hero.h"

void Hero::init(float x, float y)
{
	moveSpeed = 8;
	isDash = false;
	x_pos = x;
	y_pos = y;

}

void Hero::setDash(bool dash) {
	isDash = dash;
}

bool Hero::getDash() {
	return isDash;
}

void Hero::setSpeed(int speed) {
	moveSpeed = speed;
}

int Hero::getSpeed() {
	return moveSpeed;
}

void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_LEFT:
		if (x_pos < 0) x_pos = 0;
		else
			x_pos -= moveSpeed;
		break;


	case MOVE_RIGHT:
		if (x_pos > 576) x_pos = 576;
		else
			x_pos += moveSpeed;
		break;

	}

}