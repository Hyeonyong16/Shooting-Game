#include "EnemyBullet.h"


void EnemyBullet::init(float x, float y) {
	x_pos = x;
	y_pos = y;
	bShow = true;
}

void EnemyBullet::move(float x, float y) {
	x_pos += x;
	y_pos += y;
}

//총알의 한번에 이동할 x, y값 설정
void EnemyBullet::setMovePos(float x, float y) {
	movePos.x = x;
	movePos.y = y;
}