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

// ���� <-> Ŭ�� ��Ŷ������ ����

class CFromServerData
{
private:
	int GameStateInfo;      // ���� ������ ��Ȳ�� �˷��ִ� ����
	int BulletCnt;         // ȭ���� �Ѿ� ����
	int BlockCnt;         // ȭ���� �� ����
	int ItemCnt;         // ȭ���� ������ ����
	float Time;            //�귯�� �ð��� �����ϴ� ����
	//Player PlayerInfo[3];          // �÷��̾��� ����
	//Bullet BulletInfo[BulletCnt];   // ���� ȭ�鿡 �׷����� �Ѿ��� ����
	//Block BlockInfo[BlockCnt];      // ���� ȭ�鿡 �׷����� ���� ����
	//Item ItemInfo[ItemCnt];         // ���� ȭ�鿡 �׷����� �������� ����
};

class CFromClientData // �� Ŭ���̾�Ʈ���� �浹üũ �� ����ȭ�� ���Ͽ� ����� �� �Ѿ��� ���� ������ �Ѱ�   �� �� ���Ǵ� ����ü.
{
	string ID; // �÷��̾��� ���̵�
	int BulletCnt; // �Ѿ��� ����
	//Player PlayerInfo; // �÷��̾��� ����
	//Bullet BulletInfo[BulletCnt]; // �Ѿ��� ����
};

class CRankingData // ������ ���� �� ��ŷ�� ��/���� �� �� ���Ǵ� ����ü
{
	int RankCnt; // ��ŷ�� ��ϵ� ��ŷ ����
	//Time time; // ��ŷ�� ��ϵ� �ð�
	//string Name[RankCnt][3] // ��ŷ�� ����� ���̵� ����
};