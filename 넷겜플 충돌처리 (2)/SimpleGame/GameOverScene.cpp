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
	// > RankingData�� recv() �Ͽ� �����͸� ������Ʈ ���ְ� ����� �����Ѵ�.
}
