#pragma once
#include "Define.h"

class Scene;

class SceneMgr
{
	CREATE_SINGLETON(SceneMgr)
private:
	SceneMgr();
public:
	~SceneMgr();

private:
	Scene*			m_Scene;
	SceneType		m_CurSceneType;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	void SetScene(SceneType _SceneType);
	void ChangeScene(SceneType _SceneType);
};