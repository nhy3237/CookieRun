#pragma once
#pragma comment(lib, "msimg32.lib")
#include "framework.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Object
{
	POINT ptObj;
	int damage;
	int score;
	int idxObjImg;
};

struct ObjImageInfo
{
	HBITMAP hObjImg;
	BITMAP bitObjImg;
};

class cMap
{
private:
	HBITMAP hBackImg;
	BITMAP bitBack;
	HBITMAP hBridgeImg;
	BITMAP bitBridge;

	vector <Object*> obj;
	Object* newObj;
	vector <ObjImageInfo*> ObjImg;
	ObjImageInfo* newObjImg;
	int objImgCnt;

	HBITMAP hGaugeImg;
	BITMAP bitGauge;
	HBITMAP hGaugeBgImg;
	BITMAP bitGaugeBg;
	HBITMAP hHeartImg;
	BITMAP bitHeart;

	POINT ptBridge;
	int backCurFrame;
	int bridgeCurFrame;
	int cntObject;

	int damage;
	int score;

public:
	cMap();
	~cMap();

	void CreateBg();
	void CreateUI();
	void CreateObject();
	void DrawBitmap(HDC hdc, int health, int vScreenMinX, int vScreenMaxX);
	ObjImageInfo LoadObjImgInfo(const TCHAR* filename);

	void UpdateFrame();
	void OnCollision();
	int GetDamage();
	int GetScore();
};