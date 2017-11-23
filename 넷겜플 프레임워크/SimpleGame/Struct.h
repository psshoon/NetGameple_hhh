#pragma once

typedef struct vector2
{
	float x;
	float y;

	vector2() {}

	vector2(float _x, float _y)
		: x(_x), y(_y) {}
}Vec2;

typedef struct tagObjInfo
{
	Vec2		Pos;
	Vec2		Size;
	int			Type;
	bool		IsDead;

	tagObjInfo() {}

	tagObjInfo(Vec2 _pos, Vec2 _size, int _type, bool _isDead)
		: Pos(_pos), Size(_size), Type(_type), IsDead(_isDead) { }
}ObjInfo;