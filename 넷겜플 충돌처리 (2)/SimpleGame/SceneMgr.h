#pragma once

class Scene;
class Object;
class Renderer;

class SceneMgr
{
	CREATE_SINGLETON(SceneMgr)
private:
	SceneMgr();
public:
	~SceneMgr();

private:
	Scene*			m_Scene;		// �� ������ ���� ��
	SceneType		m_CurSceneType;
	Renderer*		m_Renderer;		// �����츦 �׸������� ������

public:
	void Initialize();
	void Update(float elapsedTime);
	void Render();
	void Release();

public:
	void SetScene(SceneType _SceneType);
	void ChangeScene(SceneType _SceneType);
	void GetKey(unsigned char key);
	void GetKeyUp(unsigned char key);

public:
	vector<Object*>& GetvecObj(ObjType type);
	void setRenderer(Renderer* _Renderer)
	{
		m_Renderer = _Renderer;
	}
	SceneType GetCurSceneType()
	{
		return m_CurSceneType;
	}
};