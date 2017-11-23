#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "LogInScene.h"

INIT_SINGLETON(SceneMgr)

SceneMgr::SceneMgr()
	: m_Scene(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Initialize()
{
}

int SceneMgr::Update()
{
	if (m_Scene)
		m_Scene->Update();

	return 0;
}

void SceneMgr::Render()
{
	if (m_Scene)
		m_Scene->Render();
}

void SceneMgr::Release()
{
}

void SceneMgr::SetScene(SceneType _SceneType)
{
	if (m_Scene)
	{
		delete m_Scene;
		m_Scene = NULL;
	}

	switch (_SceneType)
	{
	case SCENE_LOGIN:
		m_Scene = new LogInScene();
		break;

	case SCENE_WAIT:
		break;

	case SCENE_STAGE:
		break;
	}
	m_Scene->Initialize();
}

void SceneMgr::ChangeScene(SceneType _SceneType)
{
}