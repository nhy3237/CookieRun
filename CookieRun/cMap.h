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

struct ImageInfo
{
	HBITMAP hImage;
	BITMAP bitImage;
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
	HBITMAP hJelly2Img;
	BITMAP bitJelly2;
	HBITMAP hRJellyImg;
	BITMAP bitRJelly;
	HBITMAP hAJellyImg;
	BITMAP bitAJelly;
	HBITMAP hCJellyImg;
	BITMAP bitCJelly;
	HBITMAP hFJellyImg;
	BITMAP bitFJelly;

	HBITMAP hBBarrier;
	BITMAP bitBBarrier;
	HBITMAP hB2Barrier;
	BITMAP bitB2Barrier;
	HBITMAP hTBarrier1;
	BITMAP bitTBarrier1;
	HBITMAP hTBarrier2;
	BITMAP bitTBarrier2;

	HBITMAP hHpItem;
	BITMAP bitHpItem;
	HBITMAP hHp2Item;
	BITMAP bitHp2Item;

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