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
	int cntObjImg;
	int cntScreenObj;

	HBITMAP hGaugeImg;
	BITMAP bitGauge;
	HBITMAP hGaugeBgImg;
	BITMAP bitGaugeBg;
	HBITMAP hHeartImg;
	BITMAP bitHeart;

	POINT ptBridge;
	int backCurFrame;
	int bridgeCurFrame;

	int damage;
	int score;
	RECT playerRect;
	bool Death;

public:
	cMap();
	~cMap();

	void CreateBg();
	void CreateUI();
	void CreateObject();
	void DrawBitmap(HDC hdc, int health, int vScreenMinX, int vScreenMaxX, RECT playerRect);
	ObjImageInfo LoadObjImgInfo(const TCHAR* filename);

	void UpdateFrame();
	int GetDamage();
	int GetScore();
	bool GetDeath();

	void OnCollision();
};