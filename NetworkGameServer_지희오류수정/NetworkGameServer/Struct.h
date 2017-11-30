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
	int		life;		// 생명
	ObjType      Type;

	ObjInfo() {}

	ObjInfo(Vec2 _pos, float _size, Vec2 _dir, int _life, ObjType _objType)
		: Pos(_pos), Size(_size), Dir(_dir), life(_life), Type(_objType) { }
};

// 서버 <-> 클라간 패킷데이터 정의

class CFromClientData // 각 클라이언트에서 충돌체크 및 동기화를 위하여 사용자 및 총알의 정보 서버로 넘겨  줄 때 사용되는 구조체.
{
public:
	// string ID; // 플레이어의 아이디
	ObjInfo				PlayerInfo; // 플레이어 정보 변수
	vector<ObjInfo>		VecBulletInfo; // 총알 정보 변수
};

class CRankingData // 게임이 끝난 후 랭킹을 송/수신 할 때 사용되는 구조체
{
public:
	int RankCnt; // 랭킹에 기록된 랭킹 개수
				 //Time time; // 랭킹에 기록된 시간
				 //string Name[RankCnt][3] // 랭킹을 기록한 아이디 나열
};

class CFromServerData // 플레이어 별 정보를 서버에서 저장하고 클라이언트로 보내주는 클래스
{
public:
	ObjInfo			PlayerInfo; // 플레이어 정보 변수
	vector<ObjInfo>	VecBulletInfo; // 총알 정보 변수
};