#include "stdafx.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

HRESULT GameOverScene::Initialize()
{
	Scene::Initialize();

	return S_OK;
}

void GameOverScene::Update(float elapsedTime)
{
	RankingProcessing();
}

void GameOverScene::Render()
{
	Scene::Render();
}

void GameOverScene::Release()
{
}

void GameOverScene::RankingProcessing()
{
	// > RankingData을 recv() 하여 데이터를 업데이트 해주고 통신을 종료한다.
}
