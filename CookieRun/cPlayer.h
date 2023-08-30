#pragma once
#pragma comment(lib, "msimg32.lib")
#include "framework.h"

class cPlayer
{
private:
	HBITMAP hCookieImg;
	BITMAP bitCookie;

	int runFrameMax;
	int runFrameMin;
	int numCurFrame;
	int frameRow;
	POINT ptFrame;

	const POINT ptSize = { 372,372 };
	POINT ptCookie;
	const int cookieHeight = 250;

	enum { RUN, JUMP, SLIDE, DOUBLEJUMP };
	int cookieState;
	int cntJump;
	bool curJump;
	bool curDblJump;
	bool dblJumpFlg;

	int health;

public:
	cPlayer();
	~cPlayer();

	void CreateBitmap();
	void DrawBitmap(HDC hdc);

	void Move(int cookieState);
	void UpdateFrame();

	int GetHealth();
	int GetPlayerX();
};