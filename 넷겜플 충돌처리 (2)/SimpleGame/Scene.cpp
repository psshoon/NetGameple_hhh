#include "stdafx.h"
#include "Scene.h"
#include "SceneMgr.h"
#include"player.h"

Scene::Scene()
{
	Initialize();
}

Scene::~Scene()
{
	Release();
}

HRESULT Scene::Initialize()
{
	return S_OK;
}

void Scene::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!m_vecObj[i][j]->IsDead()) {
				glColor4d(m_vecObj[i][j]->GetObjInfo().Color.x, m_vecObj[i][j]->GetObjInfo().Color.y, m_vecObj[i][j]->GetObjInfo().Color.z, m_vecObj[i][j]->GetObjInfo().Color.w);
				glBegin(GL_POLYGON);
				glVertex2d(m_vecObj[i][j]->GetObjInfo().Pos.x - m_vecObj[i][j]->GetObjInfo().Size / 2, m_vecObj[i][j]->GetObjInfo().Pos.y - m_vecObj[i][j]->GetObjInfo().Size / 2);
				glVertex2d(m_vecObj[i][j]->GetObjInfo().Pos.x + m_vecObj[i][j]->GetObjInfo().Size / 2, m_vecObj[i][j]->GetObjInfo().Pos.y - m_vecObj[i][j]->GetObjInfo().Size / 2);
				glVertex2d(m_vecObj[i][j]->GetObjInfo().Pos.x + m_vecObj[i][j]->GetObjInfo().Size / 2, m_vecObj[i][j]->GetObjInfo().Pos.y + m_vecObj[i][j]->GetObjInfo().Size / 2);
				glVertex2d(m_vecObj[i][j]->GetObjInfo().Pos.x - m_vecObj[i][j]->GetObjInfo().Size / 2, m_vecObj[i][j]->GetObjInfo().Pos.y + m_vecObj[i][j]->GetObjInfo().Size / 2);
				glEnd();                      
			}
		}
	}
}

void Scene::GetKey(unsigned char key) {		
	for (size_t j = 0; j < m_vecObj[OBJ_PLAYER].size(); ++j)
	{
		dynamic_cast<Player*>(m_vecObj[OBJ_PLAYER][j])->GetKey(key);
	}
}

void Scene::GetKeyUp(unsigned char key) {
	for (size_t j = 0; j < m_vecObj[OBJ_PLAYER].size(); ++j)
	{
		dynamic_cast<Player*>(m_vecObj[OBJ_PLAYER][j])->GetKeyUp(key);
	}
	KeyCheck(key);
}

void Scene::KeyCheck(unsigned char key)
{
	if (key == 'l')
	{
		SceneType curScene = SceneMgr::GetInstance()->GetCurSceneType();
		SceneMgr::GetInstance()->ChangeScene(SceneType(curScene + 1));
	}
}

void Scene::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (m_vecObj[i][j])
				delete(m_vecObj[i][j]);
		}
	}
}