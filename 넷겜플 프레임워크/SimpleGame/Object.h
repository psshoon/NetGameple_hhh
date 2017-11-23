#pragma once
#include "Define.h"

class Object
{
public:
	Object();
	virtual ~Object();

private:
	float x, y, z;			// ��ǥ��
	float size, r, g, b, a;	// ũ��� ����
	float vx, vy, vz;		// �ӵ�
	float life;				// ����
	ObjType type;

private:
	virtual void SetPosition(float x, float y, float z, float size);
	virtual void SetVector(float vx, float vy, float v);
	virtual void SetType(ObjType tType);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetLife(float Llife);

	virtual void update(float elapsedTime);
};