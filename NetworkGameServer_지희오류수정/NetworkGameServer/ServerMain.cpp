#include "Define.h"

#define SERVERPORT 9000
#define BUFSIZE    512

// 최대 접속가능 클라이언트 수
const int MaxClientNum = 3;
// 접속한 클라이언트 수
int ClientNum = 0;
// 게임 시작 이벤트
HANDLE GameStart;
// 플레이어 대기 이벤트
HANDLE AcceptMorePlayer;
// 임계 영역 선언
CRITICAL_SECTION cs;

//서버에서 클라이언트로 보낼 패킷데이터 (미완성)
ObjInfo		PlayerInfo; // 플레이어 정보 변수

// 클라이언트로 부터 받을 패킷데이터
CFromClientData ClientPacket;

// 서버에 저장될 플레이어 데이터
CFromServerData ServerPacket[PlayerEnd];

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	// 플레이어 구분 번호
	int PlayerID = 0;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR *)&clientaddr, &addrlen);

	// 플레이어 정보 만들어서 벡터에 넣기
	// 임계 영역 설정 (초기 데이터 갱신)
	EnterCriticalSection(&cs);
	PlayerInfo.Pos = Vec2(-100.0f + 100.0f * (ClientNum-1), -150.0f); 	// 1P 왼쪽 2P 가운데 3P 오른쪽
	PlayerInfo.Dir = (Vec2(0.f, 0.f));
	PlayerInfo.life = 1;
	PlayerInfo.Size = 20;

	if (ClientNum == 1)
		PlayerID = Player1; 	// 플레이어마다 색깔 다르게 설정
	else if (ClientNum == 2)
		PlayerID = Player2;
	else if (ClientNum == 3)
		PlayerID = Player3;
	PlayerInfo.Type = OBJ_PLAYER;
	ServerPacket[PlayerID].PlayerInfo = PlayerInfo;
	LeaveCriticalSection(&cs);

	// 게임시작 신호 받을 때까지 기다림
	WaitForSingleObject(GameStart, INFINITE);

	printf("서버\n");

	// 게임 시작 신호 클라이언트에 보내주기
	retval = send(client_sock, (char *)&ServerPacket, sizeof(ServerPacket)*3, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	while (1) {
		// 데이터 받기
		retval = recv(client_sock, (char *)&ClientPacket, sizeof(CFromClientData), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		//else if (retval == 0) // 게임 오버이면 종료로 수정
		//	break;

		// 충돌처리

		// 임계 영역 설정 (데이터 갱신)
		EnterCriticalSection(&cs);
		ServerPacket[PlayerID].PlayerInfo = ClientPacket.PlayerInfo;
		ServerPacket[PlayerID].VecBulletInfo = ClientPacket.VecBulletInfo;

		// 데이터 보내기
		retval = send(client_sock, (char *)&ServerPacket, sizeof(ServerPacket)*3, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		LeaveCriticalSection(&cs);
	}

	// closesocket()
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char *argv[])
{
	// 임계 영역 초기화
	InitializeCriticalSection(&cs);

	int retval;

	// 윈속 초기화
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

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	

	// 이벤트 생성
	GameStart = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (GameStart == NULL) return 1;
	AcceptMorePlayer = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (AcceptMorePlayer == NULL) return 1;

	while (1) {
		HANDLE hThread;
		WaitForSingleObject(AcceptMorePlayer, INFINITE); // 인원수가 다차면 더 이상 accept() X

		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));


		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);


		if (hThread == NULL) { closesocket(client_sock); }
		else {
			CloseHandle(hThread);
			++ClientNum;
			if (ClientNum >= MaxClientNum)
				SetEvent(GameStart); // 클라이언트 수가 충족되면 게임 시작알림
			else
				SetEvent(AcceptMorePlayer); // 클라이언트 수 부족하면 Accept 상태로 
		}
	}

	// 이벤트 제거
	CloseHandle(GameStart);
	CloseHandle(AcceptMorePlayer);

	// 임계영역 삭제
	DeleteCriticalSection(&cs);

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

