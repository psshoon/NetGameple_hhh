#include "Define.h"

#define SERVERPORT 9000
#define BUFSIZE    512

// �ִ� ���Ӱ��� Ŭ���̾�Ʈ ��
const int MaxClientNum = 3;
// ������ Ŭ���̾�Ʈ ��
int ClientNum = 0;
// ���� ���� �̺�Ʈ
HANDLE GameStart;
// �÷��̾� ��� �̺�Ʈ
HANDLE AcceptMorePlayer;
// �Ӱ� ���� ����
CRITICAL_SECTION cs;

//�������� Ŭ���̾�Ʈ�� ���� ��Ŷ������ (�̿ϼ�)
ObjInfo		PlayerInfo; // �÷��̾� ���� ����

// Ŭ���̾�Ʈ�� ���� ���� ��Ŷ������
CFromClientData ClientPacket;

// ������ ����� �÷��̾� ������
CFromServerData ServerPacket[PlayerEnd];

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	// �÷��̾� ���� ��ȣ
	int PlayerID = 0;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	// �÷��̾� ���� ���� ���Ϳ� �ֱ�
	// �Ӱ� ���� ���� (�ʱ� ������ ����)
	EnterCriticalSection(&cs);
	PlayerInfo.Pos = Vec2(-100.0f + 100.0f * (ClientNum-1), -150.0f); 	// 1P ���� 2P ��� 3P ������
	PlayerInfo.Dir = (Vec2(0.f, 0.f));
	PlayerInfo.life = 1;
	PlayerInfo.Size = 20;

	if (ClientNum == 1)
		PlayerID = Player1; 	// �÷��̾�� ���� �ٸ��� ����
	else if (ClientNum == 2)
		PlayerID = Player2;
	else if (ClientNum == 3)
		PlayerID = Player3;
	PlayerInfo.Type = OBJ_PLAYER;
	ServerPacket[PlayerID].PlayerInfo = PlayerInfo;
	LeaveCriticalSection(&cs);

	// ���ӽ��� ��ȣ ���� ������ ��ٸ�
	WaitForSingleObject(GameStart, INFINITE);

	printf("����\n");

	// ���� ���� ��ȣ Ŭ���̾�Ʈ�� �����ֱ�
	retval = send(client_sock, (char *)&ServerPacket, sizeof(ServerPacket)*3, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	while (1) {
		// ������ �ޱ�
		retval = recv(client_sock, (char *)&ClientPacket, sizeof(CFromClientData), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		//else if (retval == 0) // ���� �����̸� ����� ����
		//	break;

		// �浹ó��

		// �Ӱ� ���� ���� (������ ����)
		EnterCriticalSection(&cs);
		ServerPacket[PlayerID].PlayerInfo = ClientPacket.PlayerInfo;
		ServerPacket[PlayerID].VecBulletInfo = ClientPacket.VecBulletInfo;

		// ������ ������
		retval = send(client_sock, (char *)&ServerPacket, sizeof(ServerPacket)*3, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		LeaveCriticalSection(&cs);
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char *argv[])
{
	// �Ӱ� ���� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	

	// �̺�Ʈ ����
	GameStart = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (GameStart == NULL) return 1;
	AcceptMorePlayer = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (AcceptMorePlayer == NULL) return 1;

	while (1) {
		HANDLE hThread;
		WaitForSingleObject(AcceptMorePlayer, INFINITE); // �ο����� ������ �� �̻� accept() X

		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));


		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);


		if (hThread == NULL) { closesocket(client_sock); }
		else {
			CloseHandle(hThread);
			++ClientNum;
			if (ClientNum >= MaxClientNum)
				SetEvent(GameStart); // Ŭ���̾�Ʈ ���� �����Ǹ� ���� ���۾˸�
			else
				SetEvent(AcceptMorePlayer); // Ŭ���̾�Ʈ �� �����ϸ� Accept ���·� 
		}
	}

	// �̺�Ʈ ����
	CloseHandle(GameStart);
	CloseHandle(AcceptMorePlayer);

	// �Ӱ迵�� ����
	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}

