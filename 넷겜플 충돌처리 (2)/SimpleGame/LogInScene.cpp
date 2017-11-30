#include "stdafx.h"
#include "LogInScene.h"
#include "Player.h"
#include "ErrorFunc.h"

LogInScene::LogInScene()
{
	Initialize();
}

LogInScene::~LogInScene()
{
}

HRESULT LogInScene::Initialize()
{
	int retval;
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("서버 연결 실패");

	return S_OK;
}

void LogInScene::Update(float elapsedTime)
{

}

void LogInScene::Render()
{
	//Scene::Render();
	//glColor4f(1, 0, 0, 1.0f);
	//glBegin(GL_POLYGON); // 사각형 그리기
	//glVertex2d(0, 0);
	//glVertex2d(100, 0);
	//glVertex2d(100, 100);
	//glVertex2d(0, 100);
	//glEnd();
}

void LogInScene::Release()
{
	
}