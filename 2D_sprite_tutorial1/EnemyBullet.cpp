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

//�Ѿ��� �ѹ��� �̵��� x, y�� ����
void EnemyBullet::setMovePos(float x, float y) {
	movePos.x = x;
	movePos.y = y;
}