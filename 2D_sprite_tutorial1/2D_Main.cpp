// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include "TimeMgr.h"
#include "Entity.h"
#include "Hero.h"
#include "EntityBulletMoveTransform.h"
#include "EnemyBullet.h"
#include <list>

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//#define ENEMY_NUM 1 


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface



// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero_happy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero_fail;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_gameoverText;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_background;    // the pointer to the sprite



// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


//enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

//시간값을 계산하기 위한 클래스
//class CTimeMgr {
//	clock_t start;
//	clock_t end;
//	double curTime;
//
//public:
//	void InitTime();
//	void UpdateTime();
//	double getTime();
//};
//
//void CTimeMgr::InitTime() {
//	curTime = 0;
//	start = clock();
//}
//
//void CTimeMgr::UpdateTime() {
//	end = clock();
//	curTime += (double)(end - start);
//
//	start = clock();
//}
//
//double CTimeMgr::getTime() {
//	return curTime;
//}


//기본 클래스 
//class entity {
//
//public:
//	float x_pos;
//	float y_pos;
//	int status;
//	int HP;
//
//};
//
//class entityBulletMoveTransform {
//public:
//	float x;
//	float y;
//};


//주인공 클래스 
//class Hero :public Entity {
//	bool isDash;
//	int moveSpeed;
//public:
//	void move(int i);
//	void setDash(bool dash);
//	bool getDash();
//
//	void setSpeed(int speed);
//	int getSpeed();
//
//	void init(float x, float y);
//
//
//};
//
//void Hero::init(float x, float y)
//{
//	moveSpeed = 8;
//	isDash = false;
//	x_pos = x;
//	y_pos = y;
//
//}
//
//void Hero::setDash(bool dash) {
//	isDash = dash;
//}
//
//bool Hero::getDash() {
//	return isDash;
//}
//
//void Hero::setSpeed(int speed) {
//	moveSpeed = speed;
//}
//
//int Hero::getSpeed() {
//	return moveSpeed;
//}
//
//void Hero::move(int i)
//{
//	switch (i)
//	{
//	case MOVE_LEFT:
//		if (x_pos < 0) x_pos = 0;
//		else
//			x_pos -= moveSpeed;
//		break;
//
//
//	case MOVE_RIGHT:
//		if (x_pos > 576) x_pos = 576;
//		else
//			x_pos += moveSpeed;
//		break;
//
//	}
//
//}




// 적 클래스 
//class Enemy :public Entity {
//
//public:
//	void fire();
//	void init(float x, float y);
//	void move();
//
//};
//
//void Enemy::init(float x, float y)
//{
//
//	x_pos = x;
//	y_pos = y;
//
//}
//
//void Enemy::move()
//{
//	y_pos += 2;
//
//}






// 총알 클래스 
//class Bullet :public Entity {
//
//public:
//	bool bShow;
//
//	void init(float x, float y);
//	void move();
//	bool show();
//	void hide();
//	void active();
//
//};
//
//void Bullet::init(float x, float y)
//{
//	x_pos = x;
//	y_pos = y;
//
//}
//
//bool Bullet::show()
//{
//	return bShow;
//
//}
//
//void Bullet::active()
//{
//	bShow = true;
//
//}
//
//void Bullet::move()
//{
//	y_pos -= 8;
//}
//
//void Bullet::hide()
//{
//	bShow = false;
//
//}


//탄막 구조체
//class EnemyBullet
//{
//public:
//	bool bShow;
//	float x_pos;
//	float y_pos;
//	EntityBulletMoveTransform movePos;
//
//	void init(float x, float y);
//	void move(float x, float y);
//	void setMovePos(float x, float y);
//};
//
//void EnemyBullet::init(float x, float y) {
//	x_pos = x;
//	y_pos = y;
//	bShow = true;
//}
//
//void EnemyBullet::move(float x, float y) {
//	x_pos += x;
//	y_pos += y;
//}
//
////총알의 한번에 이동할 x, y값 설정
//void EnemyBullet::setMovePos(float x, float y) {
//	movePos.x = x;
//	movePos.y = y;
//}

//객체 생성 
TimeMgr timeMgr;

Hero hero;
//Enemy enemy[ENEMY_NUM];
//Bullet bullet; 
list<EnemyBullet> enemyBullet;

Entity shootPosition{ 200, 0 };		//총알이 날아가기 시작할 위치

//float moveXPos = 2;		//shootPosition의 x좌표 이동값
//float moveYPos = 8;		//shootPosition의 y좌표 이동값


bool pattern1 = true;
//bool pattern2 = false;
//bool pattern3 = false;

float circleFellSpeed = 8.0;
int patternRandNum;
int patternDistNum;
bool gameOver = false;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();


		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);




		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Panel3.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"hero.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero_Happy.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_happy);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero_Fail.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_fail);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"enemy.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"gameover.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_gameoverText);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"background.jpg",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_background);    // load to sprite


	return;
}


void init_game(void)
{
	timeMgr.InitTime();

	//객체 초기화 
	hero.init(288, 416);

	//적들 초기화 
	//for (int i = 0; i < ENEMY_NUM; i++)
	//{

	//	enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
	//}

	//총알 초기화 
	//bullet.init(hero.x_pos, hero.y_pos); 


}


void do_game_logic(void)
{
	if (gameOver) {
		enemyBullet.clear();
		circleFellSpeed = 8.0;

		if (KEY_DOWN(0x52)) {
			gameOver = false;
		}
	}

	if (!gameOver) {
		timeMgr.UpdateTime();

		//주인공 처리 
		/*if (KEY_DOWN(VK_UP))
			hero.move(MOVE_UP);

		if (KEY_DOWN(VK_DOWN))
			hero.move(MOVE_DOWN);*/

		if (KEY_DOWN(VK_LEFT))
			hero.move(MOVE_LEFT);

		if (KEY_DOWN(VK_RIGHT))
			hero.move(MOVE_RIGHT);

		if (KEY_DOWN(VK_F1)) {
			enemyBullet.clear();
			pattern1 = true;
			/*pattern2 = false;
			pattern3 = false;*/
		}

		/*if (KEY_DOWN(VK_F2)) {
			enemyBullet.clear();
			pattern1 = false;
			pattern2 = true;
			pattern3 = false;
		}

		if (KEY_DOWN(VK_F3)) {
			enemyBullet.clear();
			pattern1 = false;
			pattern2 = false;
			pattern3 = true;
		}*/

		if (KEY_DOWN(VK_SHIFT)) {
			if (hero.getDash() == false) {
				hero.setDash(true);
				hero.setSpeed(40);
			}
		}

		if (KEY_UP(VK_SHIFT)) {
			if (hero.getDash() == true) {
				hero.setDash(false);
				hero.setSpeed(8);
			}
		}

		//적들 처리 
		//for (int i = 0; i < ENEMY_NUM; i++)
		//{
		//	if (enemy[i].y_pos > 500)
		//		enemy[i].init((float)150, 150/*rand()%300), rand()%200 - 300*/);
		//	//else
		//		//enemy[i].move();
		//}


		//총알 처리 
		/*if(bullet.show() == false)
		{
			if(KEY_DOWN(VK_SPACE))
			{
				bullet.active();
				bullet.init(hero.x_pos, hero.y_pos);
			}


		}*/


		/*if( bullet.show() == true )
		{
			if(bullet.y_pos < -70)
				bullet.hide();
			else
				bullet.move();


		}*/

		//패턴1 드래곤플라이트식 패턴
		if (pattern1) {
			shootPosition = { 200, 0 };
			/*if (timeMgr.getTime() > 500) {
				int it = rand() % 5;
				for (int i = 0; i < 5; i++) {
					if (i != it) {
						EnemyBullet temp;
						temp.init(60 * i, 0);
						enemyBullet.push_back(temp);
					}
				}
				timeMgr.InitTime();
			}*/
			if (timeMgr.getTime() > 400) {
				/*int it = rand() % 5;
				for (int i = 0; i < 5; i++) {
					if (i != it) {
						EnemyBullet temp;
						temp.init(60 * i, 0);
						enemyBullet.push_back(temp);
					}
				}*/
				patternRandNum = rand() % 100;
				patternDistNum = rand() % 20 + 20;
				if (patternRandNum >= 0 && patternRandNum < 70) {
					EnemyBullet temp;
					temp.init(rand() % 336 + 120, -80);
					temp.setMovePos(0, circleFellSpeed);
					enemyBullet.push_back(temp);
				}

				else if (patternRandNum >= 70 && patternRandNum < 80) {
					int mainPos = rand() % 216 + 180;
					for (int i = 0; i < 5; i++) {
						EnemyBullet temp;
						temp.init(mainPos + patternDistNum * i, -80 - 30 * i);
						temp.setMovePos(0, circleFellSpeed);
						enemyBullet.push_back(temp);
					}
				}

				else if (patternRandNum >= 80 && patternRandNum < 90) {
					int mainPos = rand() % 216 + 180;
					for (int i = 0; i < 5; i++) {
						EnemyBullet temp;
						temp.init(mainPos - patternDistNum * i, -80 - 30 * i);
						temp.setMovePos(0, circleFellSpeed);
						enemyBullet.push_back(temp);
					}
				}

				else if (patternRandNum >= 90 && patternRandNum < 100) {
					int mainPos = rand() % 216 + 180;
					for (int i = 0; i < 5; i++) {
						EnemyBullet temp;
						if (i % 2 == 0) {
							temp.init(mainPos + patternDistNum + 40, -80 - 30 * i);
						}
						else {
							temp.init(mainPos, -80 - 30 * i);
						}

						temp.setMovePos(0, circleFellSpeed);
						enemyBullet.push_back(temp);
					}
				}

				timeMgr.InitTime();
			}


			for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++)
			{
				it->move(it->movePos.x, it->movePos.y);
			}
		}

		////패턴2 3방향 좌우로 이동하면서 발사
		//if (pattern2) {
		//	if (timeMgr.getTime() > 250) {
		//		//int it = rand() % 5;
		//		for (int i = 0; i < 3; i++) {
		//			EnemyBullet temp;
		//			temp.init(shootPosition.x_pos, shootPosition.y_pos);
		//			if (i % 3 == 0) temp.setMovePos(-8 * cos(45), 8 * sin(45));
		//			if (i % 3 == 1) temp.setMovePos(0, 8);
		//			if (i % 3 == 2) temp.setMovePos(8 * cos(45), 8 * sin(45));
		//			enemyBullet.push_back(temp);
		//		}
		//		timeMgr.InitTime();
		//	}

		//	shootPosition.x_pos += moveXPos;
		//	if (shootPosition.x_pos < 0) moveXPos *= -1;
		//	if (shootPosition.x_pos > 400) moveXPos *= -1;

		//	for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++)
		//	{
		//		it->move(it->movePos.x, it->movePos.y);
		//	}
		//}

		////패턴3 랜덤하게 사방으로 총알 발사
		//if (pattern3) {
		//	shootPosition = { 200, 0 };
		//	if (timeMgr.getTime() > 100) {
		//		//int it = rand() % 5;
		//		EnemyBullet temp;
		//		temp.init(shootPosition.x_pos, shootPosition.y_pos);
		//		temp.setMovePos(8 * cos(rand() % 140 + 70), 8);
		//		enemyBullet.push_back(temp);
		//		timeMgr.InitTime();
		//	}

		//	for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++)
		//	{
		//		it->move(it->movePos.x, it->movePos.y);
		//	}
		//}



		for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++) {
			if (it->bShow == true) {
				float x_distance = abs(hero.x_pos - it->x_pos);
				float y_distance = abs(hero.y_pos - it->y_pos);
				if (x_distance < 64)	//64 = 가로길이
					if (y_distance < 58) {	//64 = 세로길이
						it->bShow = false;
					}
			}
		}

		if (enemyBullet.size() != 0) {
			for (auto it = enemyBullet.begin(); it != enemyBullet.end();) {
				if (it->y_pos > 500) {
					if (it->bShow == true) { gameOver = true; }
					enemyBullet.erase(it++);
					if (circleFellSpeed < 30)
						circleFellSpeed += 0.5;
				}
				else
					++it;
			}
		}
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window to a deep blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

	//UI 창 렌더링 


	/*
	static int frame = 21;    // start the program on the final frame
	if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
	if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

	// calculate the x-position
	int xpos = frame * 182 + 1;

	RECT part;
	SetRect(&part, xpos, 0, xpos + 181, 128);
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
	*/

	RECT part4;
	SetRect(&part4, 0, 0, 640, 480);
	D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position4(0, 0, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite_background, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));

	//주인공 
	RECT part;
	SetRect(&part, 0, 0, 64, 64);
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
	if (!gameOver) {
		if (hero.getDash() == false) {
			d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (hero.getDash() == true) {
			d3dspt->Draw(sprite_hero_happy, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	if(gameOver)
		d3dspt->Draw(sprite_hero_fail, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

	////총알 
	//if(bullet.bShow == true)
	//{
	//	RECT part1;
	//	SetRect(&part1, 0, 0, 64, 64);
	//	D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	//	D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
	//	d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++) {
		if (it->bShow == true)
		{
			RECT part1;
			SetRect(&part1, 0, 0, 64, 64);
			D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position1(it->x_pos, it->y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}


	////적 
	//RECT part2;
	//SetRect(&part2, 0, 0, 64, 64);
	//D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

	//for (int i = 0; i < ENEMY_NUM; i++)
	//{

	//	D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
	//	d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	if (gameOver == true)
	{
		RECT part3;
		SetRect(&part3, 0, 0, 250, 256);
		D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position3(170, 65, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_gameoverText, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite->Release();
	d3ddev->Release();
	d3d->Release();

	//객체 해제 
	sprite_hero->Release();
	sprite_hero_happy->Release();
	sprite_hero_fail->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();
	sprite_gameoverText->Release();
	sprite_background->Release();

	return;
}