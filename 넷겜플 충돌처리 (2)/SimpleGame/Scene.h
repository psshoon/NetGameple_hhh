#pragma once

class Object;

class Scene
{
public:
	Scene();
	virtual ~Scene();

protected:
	vector<Object*>			m_vecObj[OBJ_END];

public:
	virtual HRESULT Initialize();
	virtual void Update(float elapsedTime) = 0;
	virtual void Render();
	virtual void Release();

	void GetKey(unsigned char key);
	void GetKeyUp(unsigned char key);
	void KeyCheck(unsigned char key);

public:
	vector<Object*>&	GetvecObj(ObjType type)
	{
		return m_vecObj[type];
	}
};
