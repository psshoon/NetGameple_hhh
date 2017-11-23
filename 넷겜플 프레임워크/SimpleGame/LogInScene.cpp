#include "stdafx.h"
#include "LogInScene.h"

LogInScene::LogInScene()
{
}

LogInScene::~LogInScene()
{
}

HRESULT LogInScene::Initialize()
{
	m_testString = "Login Scene";

	return S_OK;
}

int LogInScene::Update()
{
	glRasterPos2f(100.f, 100.f);
	int len = (int)strlen(m_testString);

	glColor3f(0.f, 0.f, 1.f);

	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m_testString[i]);
	}

	

	return 0;
}

void LogInScene::Render()
{
	printf("Login Scene");
}

void LogInScene::Release()
{
}
