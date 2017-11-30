#pragma once
#include "Scene.h"

class GameScene
	: public Scene
{
public:
	GameScene();
	~GameScene();

public:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Release();

private:
	void InitStartInfo();
	void RecvServerInfo();
	void SendClientInfo();

public:
	void AddBlock();
	void collider();
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	int recvn(SOCKET s, char *buf, int len, int flags);
};