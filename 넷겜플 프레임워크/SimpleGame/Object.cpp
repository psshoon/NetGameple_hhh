#include "stdafx.h"
#include "Object.h"

Object::Object() {

}

Object::~Object() {

}


void Object::SetPosition(float x1, float y1, float z1, float size1) {
	x = x1;
	y = y1;
	z = z1;
	size = size1;
}

void Object::SetVector(float x1, float y1, float z1)
{
	vx = x1;
	vy = y1;
	vz = z1;
}

void Object::SetColor(float r1, float g1, float b1, float a1) {
	r = r1;
	b = b1;
	g = g1;
	a = a1;
}

void Object::SetLife(float Llife) {
	life = Llife;
}

void Object::SetType(ObjType tType) {
	if (tType == OBJ_PLAYER) {
		type = OBJ_PLAYER;
	}
	else if (tType == OBJ_BULLET) {
		type = OBJ_BULLET;
	}
	else if (tType == OBJ_BLOCK) {
		type = OBJ_BLOCK;
	}
	else if (tType == OBJ_ITEM) {
		type = OBJ_ITEM
	}
}
