#pragma once

class Renderer;

class MainGame
{
public:
	MainGame();
	~MainGame();

private:
	Renderer*			m_Renderer;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();
};