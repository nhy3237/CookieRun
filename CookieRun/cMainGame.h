#pragma once
#pragma comment(lib, "msimg32.lib")

#include "framework.h"
#include "cPlayer.h"
#include "cMap.h"
#include "string"
#include "iostream"

using namespace std;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HBITMAP hSceneImg;
	BITMAP bitScene;

	HBITMAP hDoubleBufferImg;
	RECT rectView;

	cPlayer cookie;
	cMap map;

	enum { RUN, JUMP, SLIDE };

	int playerHealth;
	int score;

	// °¡»ó ÁÂÇ¥
	int vScreenMinX;
	int vScreenMaxX;
	RECT vPlayerRect;

public:
	void LoadScreen(HDC hdc);
	void StartScreen(HDC hdc);
	void EndScreen(HDC hdc);

	void Setup(HWND hWnd);
	void Update(HWND hWnd);
	void Render(HDC hdc);

	void UpdateMove();
	void UpdateHealth();

	bool GetHealth();
};