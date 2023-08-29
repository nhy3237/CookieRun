#pragma once
#pragma comment(lib, "msimg32.lib")

#include "framework.h"
#include "cPlayer.h"
#include "cMap.h"
#include "string"

#define TIMER 123

using namespace std;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HBITMAP hLoadImg;
	BITMAP bitLoad;

	HBITMAP hDoubleBufferImg;
	RECT rectView;

	cPlayer cookie;
	cMap map;

	enum { RUN, JUMP, SLIDE };

	int playerHealth;

public:
	void Load(HDC hdc);

	void Setup(HWND hWnd);
	void Update(HWND hWnd);
	void Render(HDC hdc);

	void UpdateMove();
	void UpdateHealth();
};