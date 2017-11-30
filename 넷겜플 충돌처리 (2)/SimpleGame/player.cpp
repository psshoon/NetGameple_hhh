#include "stdafx.h"
#include "player.h"
#include "SceneMgr.h"
#include "Bullet.h"

Player::Player() {

}

Player::~Player() {

}

void Player::SetID(string idd) {
	ID = idd;
}

void Player::update(float elapsedTime) {
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	
	xy.x += Vxy.x * elapsedTimeInSecond;
	xy.y += Vxy.y * elapsedTimeInSecond;

	if (xy.x > WINDOWSIZEX / 2) {
		xy.x = WINDOWSIZEX / 2;
	}

	if (xy.x < -WINDOWSIZEX / 2) {
		xy.x = -WINDOWSIZEX / 2;
	}

	if (xy.y > WINDOWSIZEY / 2) {
		xy.y = WINDOWSIZEY / 2;
	}

	if (xy.y < -WINDOWSIZEY / 2) {
		xy.y = -WINDOWSIZEY / 2;
	}
	cout << xy.x << "\t" << xy.y << endl;
}

void Player::GetKey(unsigned char key) {
	if (key == 'a' || key == 'A') {
		Vxy.x = -PLAYERSPEED;
	}
	if (key == 's' || key == 'S') {
		Vxy.y = -PLAYERSPEED;
	}
	if (key == 'd' || key == 'D') {
		Vxy.x = PLAYERSPEED;
	}
	if (key == 'w' || key == 'W') {
		Vxy.y = +PLAYERSPEED;
	}
}

void Player::GetKeyUp(unsigned char key) {
	if (key == 'a' || key == 'A') {
		Vxy.x = 0;
	}
	if (key == 'd' || key == 'D') {
		Vxy.x = 0;
	}
	if (key == 's' || key == 'S') {
		Vxy.y = 0;
	}
	if (key == 'w' || key == 'W') {
		Vxy.y = 0;
	}
	if (key == 'k' || key == 'K') {
		AddBullet();
	}
}

void Player::AddBullet()
{
	Object* pObj = new Bullet;
	pObj->SetPosition(xy);
	pObj->SetVector(Vec2(0.f, BULLETSPEED));
	pObj->SetInfo(1, 5, Vec4(0.f, 200.f, 140.f, 255.f));
	pObj->SetType(OBJ_BULLET1);

	SceneMgr::GetInstance()->GetvecObj(OBJ_BULLET1).push_back(pObj);
}