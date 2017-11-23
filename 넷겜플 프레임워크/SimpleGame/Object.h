#pragma once
#include "Define.h"

class Object
{
public:
	Object();
	virtual ~Object();

private:
	float x, y, z;			// 좌표값
	float size, r, g, b, a;	// 크기와 색깔값
	float vx, vy, vz;		// 속도
	float life;				// 생명
	ObjType type;

private:
	virtual void SetPosition(float x, float y, float z, float size);
	virtual void SetVector(float vx, float vy, float v);
	virtual void SetType(ObjType tType);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetLife(float Llife);

	virtual void update(float elapsedTime);
};