#pragma once
#include "Scene.h"
#include "Dependencies\glew.h"
#include "Dependencies\glut.h"

class WaitScene
	: public Scene
{
public:
	WaitScene();
	virtual ~WaitScene();

private:
	GLubyte*			m_TexBits;
	char*				m_testString;

private:
	virtual HRESULT Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();
};
