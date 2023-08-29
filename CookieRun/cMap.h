#pragma once
#pragma comment(lib, "msimg32.lib")
#include "framework.h"
#include <vector>

using namespace std;

struct Object
{
	POINT ptObj;
	int damage;
	int score;
	HBITMAP hObjImg;
	BITMAP bitObj;
};

class cMap
{
private:
	Object newObj;
	vector <Object> obj;

	HBITMAP hBackImg;
	BITMAP bitBack;
	HBITMAP hBridgeImg;
	BITMAP bitBridge;

	HBITMAP hJellyImg;
	BITMAP bitJelly;
	HBITMAP hRJellyImg;
	BITMAP bitRJelly;
	HBITMAP hAJellyImg;
	BITMAP bitAJelly;
	HBITMAP hCJellyImg;
	BITMAP bitCJelly;

	HBITMAP hBBarrier;
	BITMAP bitBBarrier;
	HBITMAP hTBarrier1;
	BITMAP bitTBarrier1;
	HBITMAP hTBarrier2;
	BITMAP bitTBarrier2;

	HBITMAP hGaugeImg;
	BITMAP bitGauge;
	HBITMAP hGaugeBgImg;
	BITMAP bitGaugeBg;
	HBITMAP hHeartImg;
	BITMAP bitHeart;

	int backCurFrame;
	int bridgeCurFrame;

	POINT ptBridge;
	
	int xObject;
	int cntObject;

public:
	cMap();
	~cMap();

	void CreateBg();
	void CreateUI();
	void CreateObject();
	void DrawBitmap(HDC hdc, int health);

	void UpdateFrame();
};