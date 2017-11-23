#include "stdafx.h"
#include "WaitScene.h"

WaitScene::WaitScene()
{
}

WaitScene::~WaitScene()
{
}

HRESULT WaitScene::Initialize()
{
	int retval;
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		return E_FAIL;

	return S_OK;
}

int WaitScene::Update()
{
	printf("WaitScene Scene");
	return 0;
}

void WaitScene::Render()
{
}

void WaitScene::Release()
{
}
