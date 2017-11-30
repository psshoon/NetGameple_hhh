#pragma once

class Vec2
{
public:
	float x;
	float y;

	Vec2() {}

	Vec2(float _x, float _y)
		: x(_x), y(_y) {}
};

class Vec4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vec4() {}

	Vec4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w) {}
};

class ObjInfo
{
public:
	Vec2      Pos;
	float      Size;
	Vec2      Dir;
	Vec4      Color;
	int		life;		// ����
	ObjType      objType;

	ObjInfo() {}

	ObjInfo(Vec2 _pos, float _size, Vec2 _dir, Vec4 _color, int _life, ObjType _objType)
		: Pos(_pos), Size(_size), Dir(_dir), Color(_color), life(_life),  objType(_objType) { }
};

// ���� <-> Ŭ�� ��Ŷ������ ����

class CFromClientData // �� Ŭ���̾�Ʈ���� �浹üũ �� ����ȭ�� ���Ͽ� ����� �� �Ѿ��� ���� ������ �Ѱ�  �� �� ���Ǵ� ����ü.
{
public:
	// string ID; // �÷��̾��� ���̵�
	ObjInfo				PlayerInfo; // �÷��̾� ���� ����
	vector<ObjInfo>		VecBulletInfo; // �Ѿ� ���� ����
};

class CRankingData // ������ ���� �� ��ŷ�� ��/���� �� �� ���Ǵ� ����ü
{
public:
	int RankCnt; // ��ŷ�� ��ϵ� ��ŷ ����
				 //Time time; // ��ŷ�� ��ϵ� �ð�
				 //string Name[RankCnt][3] // ��ŷ�� ����� ���̵� ����
};

class CFromServerData // �÷��̾� �� ������ �������� �����ϰ� Ŭ���̾�Ʈ�� �����ִ� Ŭ����
{
public:
	ObjInfo			PlayerInfo; // �÷��̾� ���� ����
	vector<ObjInfo>	VecBulletInfo; // �Ѿ� ���� ����
};