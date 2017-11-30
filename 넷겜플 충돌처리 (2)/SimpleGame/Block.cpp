#include "stdafx.h"
#include "Block.h"

Block::Block() {}

Block::~Block() {}

void Block::SetType(ObjType tType) {
	if (tType == OBJ_BLOCK1) {
		Object::SetType(OBJ_BLOCK1);
	}
	else if (tType == OBJ_BLOCK2) {
		Object::SetType(OBJ_BLOCK2);
	}
	else if (tType == OBJ_BLOCK3) {
		Object::SetType(OBJ_BLOCK3);
	}
	else if (tType == OBJ_BLOCK4) {
		Object::SetType(OBJ_BLOCK4);
	}
	else if (tType == OBJ_BLOCK5) {
		Object::SetType(OBJ_BLOCK5);
	}
}

void Block::update(float elapsedTime) {
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	xy.x += Vxy.x * elapsedTimeInSecond;
	xy.y += Vxy.y * elapsedTimeInSecond;

	if (xy.y < -WINDOWSIZEY / 2) {
		SetDead();
	}
}