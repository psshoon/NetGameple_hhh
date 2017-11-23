#include "stdafx.h"
#include "MainGame.h"
#include "Define.h"
#include "Renderer.h"
#include "SceneMgr.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
	m_Renderer = new Renderer(WINCX, WINCY);
	SceneMgr::GetInstance()->Initialize();
	SceneMgr::GetInstance()->SetScene(SCENE_LOGIN);
}

int MainGame::Update()
{
	SceneMgr::GetInstance()->Update();
	return 0;
}

void MainGame::Render()
{
	SceneMgr::GetInstance()->Render();
}

void MainGame::Release()
{
}
