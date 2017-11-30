#include "stdafx.h"
#include "Object.h"

Object::Object() {

}

Object::~Object() {

}


void Object::SetPosition(Vec2 xy1) {
	xy.x = xy1.x;
	xy.y = xy1.y;
}

void Object::SetVector(Vec2 Vxy1)
{
	Vxy.x = Vxy1.x;
	Vxy.y = Vxy1.y;
}

void Object::SetInfo(int life1, float size1, Vec4 color1) {
	life = life1;
	size = size1;
	color = color1;
}

void Object::SetType(ObjType tType) {
	type = tType;
}

Vec2 Object::GetPosition() {
	return xy;
}

Vec2 Object::GetVector() {
	return Vxy;
}

void Object::SetDead() {
	life = 0;
}

bool Object::IsDead() {
	if (life < 1)
		return TRUE;
	else
		return FALSE;
}

ObjType Object::GetType() {
	return type;
}

ObjInfo Object::GetObjInfo() {
	return ObjInfo(xy, size, Vxy, color, life, type);
}