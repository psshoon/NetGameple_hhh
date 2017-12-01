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

// 서버 <-> 클라간 패킷데이터 정의

class CFromServerData
{
private:
	int GameStateInfo;      // 현재 게임의 상황을 알려주는 변수
	int BulletCnt;         // 화면의 총알 개수
	int BlockCnt;         // 화면의 블럭 개수
	int ItemCnt;         // 화면의 아이템 개수
	float Time;            //흘러간 시간을 저장하는 변수
	//Player PlayerInfo[3];          // 플레이어의 정보
	//Bullet BulletInfo[BulletCnt];   // 현재 화면에 그려지는 총알의 정보
	//Block BlockInfo[BlockCnt];      // 현재 화면에 그려지는 블럭의 정보
	//Item ItemInfo[ItemCnt];         // 현재 화면에 그려지는 아이템의 정보
};

class CFromClientData // 각 클라이언트에서 충돌체크 및 동기화를 위하여 사용자 및 총알의 정보 서버로 넘겨   줄 때 사용되는 구조체.
{
	string ID; // 플레이어의 아이디
	int BulletCnt; // 총알의 개수
	//Player PlayerInfo; // 플레이어의 정보
	//Bullet BulletInfo[BulletCnt]; // 총알의 정보
};

class CRankingData // 게임이 끝난 후 랭킹을 송/수신 할 때 사용되는 구조체
{
	int RankCnt; // 랭킹에 기록된 랭킹 개수
	//Time time; // 랭킹에 기록된 시간
	//string Name[RankCnt][3] // 랭킹을 기록한 아이디 나열
};