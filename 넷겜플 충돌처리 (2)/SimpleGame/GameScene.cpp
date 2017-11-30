#include "stdafx.h"
#include "GameScene.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Block.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

HRESULT GameScene::Initialize()
{
	//Scene::Initialize();
	//InitStartInfo();
	//--------------------------임시-------------------------//
	Object* pObj = new Player;
	pObj->SetPosition(Vec2(10.f, 10.f));
	pObj->SetVector(Vec2(0.f, 0.f));
	pObj->SetInfo(1, 20, Vec4(255.f, 0.f, 0.f, 255.f));
	pObj->SetType(OBJ_PLAYER);

	m_vecObj[OBJ_PLAYER].push_back(pObj);

	//--------------------------임시-------------------------//

	AddBlock();

	return S_OK;
}

void GameScene::Update(float elapsedTime)
{
	RecvServerInfo();

	for (int i = 0; i < OBJ_END; ++i)
	{
		
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			auto iter = m_vecObj[i].begin();
			iter++;
			if (!m_vecObj[i][j]->IsDead())
				m_vecObj[i][j]->update(elapsedTime);
			else {
				Object* a = m_vecObj[i][j];
				m_vecObj[i].erase(--iter);
				delete a;
			}
		}
	}

	SendClientInfo();
	collider();
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::Release()
{

}

void GameScene::InitStartInfo()
{
	// > WaitScene에서 받았던 정보로 씬을 동기화 해준다.
	// > 
}

void GameScene::RecvServerInfo()
{
	int retval;
	CFromServerData SeverData[3];

	// > CFromServerData 구조체 recv()
	//while (1) 
	//{
		// 데이터 받기
		retval = recv(sock, (char*)&SeverData, sizeof(SeverData) * 3, 0);
		if (retval == SOCKET_ERROR)
		{
			//err_display("recv()");
			return;
		}
		else if (retval == 0)
			return;


		// 데이터 보내기
		retval = send(sock, (char*)&SeverData, retval, 0);
		if (retval == SOCKET_ERROR)
		{
			//err_display("send()");
			return;
		}
	//}
	// > 자신의 플레이어 HP가 0이면 '관전'상태 
	// > 모든 플레이어가 0인지 확인 후 GameOverScene으로 넘김

	//bool isGameOver = false;
	//vector<Object*> vecPlayer = SceneMgr::GetInstance()->GetvecObj(OBJ_PLAYER);
	//for (size_t i = 0; i < vecPlayer.size(); ++i)
	//{
	//	if (vecPlayer[i]->IsDead)
	//	{
	//		isGameOver = false;
	//		break;
	//	}
	//}

	//if (isGameOver == true)
	//	SceneMgr::GetInstance()->ChangeScene(SCENE_OVER);
}

void GameScene::SendClientInfo()
{
	// > FromClientData 구조체 send();
	int retval;
	//while (1)
	//{
		CFromClientData ClientData;
		ClientData.PlayerInfo = SceneMgr::GetInstance()->GetvecObj(OBJ_PLAYER)[0]->GetObjInfo();
		size_t bulletSize = SceneMgr::GetInstance()->GetvecObj(OBJ_BULLET1).size();
		for (size_t i = 0; i < bulletSize; ++i)
		{
			ClientData.VecBulletInfo[i] = SceneMgr::GetInstance()->GetvecObj(OBJ_BULLET1)[i]->GetObjInfo();
		}

		retval = send(sock, (char*)&ClientData, sizeof(ClientData), 0);
		if (retval == SOCKET_ERROR)
		{
			//err_display("send()");
			return;
		}

		retval = recvn(sock, (char*)&ClientData, retval, 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
			return;
		}
		else if (retval == 0)
			return;
	//}


}

void GameScene::AddBlock() {
	Object* pObj = new Block;
	pObj->SetPosition(Vec2(0, WINDOWSIZEY));
	pObj->SetVector(Vec2(0.f, BLOCKSPEED));
	pObj->SetInfo(1, 50, Vec4(0.f, 0.f, 100.f, 200.f));
	pObj->SetType(OBJ_BLOCK1);

	m_vecObj[OBJ_BLOCK1].push_back(pObj);
}


void GameScene::collider() {
	int collisionCount = 0;

	for (size_t i = 0; i < m_vecObj[OBJ_BLOCK1].size(); ++i)
	{
		for (size_t j = 0; j < m_vecObj[OBJ_BULLET1].size(); ++j)
		{

			float minX, minY;
			float maxX, maxY;

			float minX1, minY1;
			float maxX1, maxY1;

			minX = m_vecObj[OBJ_BLOCK1][i]->GetPosition().x - (m_vecObj[OBJ_BLOCK1][i]->GetObjInfo().Size / 2);
			maxX = m_vecObj[OBJ_BLOCK1][i]->GetPosition().x + (m_vecObj[OBJ_BLOCK1][i]->GetObjInfo().Size / 2);
			minY = m_vecObj[OBJ_BLOCK1][i]->GetPosition().y - (m_vecObj[OBJ_BLOCK1][i]->GetObjInfo().Size / 2);
			maxY = m_vecObj[OBJ_BLOCK1][i]->GetPosition().y + (m_vecObj[OBJ_BLOCK1][i]->GetObjInfo().Size / 2);

			minX1 = m_vecObj[OBJ_BULLET1][j]->GetPosition().x - (m_vecObj[OBJ_BULLET1][j]->GetObjInfo().Size / 2);
			maxX1 = m_vecObj[OBJ_BULLET1][j]->GetPosition().x + (m_vecObj[OBJ_BULLET1][j]->GetObjInfo().Size / 2);
			minY1 = m_vecObj[OBJ_BULLET1][j]->GetPosition().y - (m_vecObj[OBJ_BULLET1][j]->GetObjInfo().Size / 2);
			maxY1 = m_vecObj[OBJ_BULLET1][j]->GetPosition().y + (m_vecObj[OBJ_BULLET1][j]->GetObjInfo().Size / 2);

			if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
			{
				collisionCount++;
				m_vecObj[OBJ_BLOCK1][i]->SetDead();
				m_vecObj[OBJ_BULLET1][j]->SetDead();
			}
		}
	}
}

bool GameScene::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}

// 사용자 정의 데이터 수신 함수
int GameScene::recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}