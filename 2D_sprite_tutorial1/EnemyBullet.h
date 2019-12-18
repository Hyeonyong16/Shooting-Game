#pragma once
#include "EntityBulletMoveTransform.h"

class EnemyBullet
{
public:
	bool bShow;
	float x_pos;
	float y_pos;
	EntityBulletMoveTransform movePos;

	void init(float x, float y);
	void move(float x, float y);
	void setMovePos(float x, float y);
};

