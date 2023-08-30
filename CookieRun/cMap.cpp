#include "cMap.h"

cMap::cMap()
{
    backCurFrame = 0;
    bridgeCurFrame = 0;

    ptBridge.y = 622;

    cntScreenObj = 0;
    Death = false;
}

cMap::~cMap()
{
    for (int i = 0; i < cntObjImg; ++i) {
        if (ObjImg[i]->hObjImg) {
            DeleteObject(ObjImg[i]->hObjImg);
        }
    }
    ObjImg.clear();
    obj.clear();
}

void cMap::CreateBg()
{
    // Background
    hBackImg = (HBITMAP)LoadImage(NULL, TEXT("images/Background.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hBackImg, sizeof(BITMAP), &bitBack);

    // Bridge
    hBridgeImg = (HBITMAP)LoadImage(NULL, TEXT("images/Bg_Bridge.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hBridgeImg, sizeof(BITMAP), &bitBridge);
}

void cMap::CreateUI()
{
    // Gauge
    hGaugeImg = (HBITMAP)LoadImage(NULL, TEXT("images/UI_Gauge.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hGaugeImg, sizeof(BITMAP), &bitGauge);

    // Heart
    hHeartImg = (HBITMAP)LoadImage(NULL, TEXT("images/UI_HeartLife.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hHeartImg, sizeof(BITMAP), &bitHeart);

    AddFontResourceEx(L"font/CookieRun Regular.ttf", FR_PRIVATE, NULL);
}

void cMap::CreateObject()
{
    const TCHAR* imageFiles[] = {
        TEXT("images/Jelly_Basic.bmp"),
        TEXT("images/Jelly_Basic2.bmp"),
        TEXT("images/Jelly_Rainbow.bmp"),
        TEXT("images/Jelly_Apple.bmp"),
        TEXT("images/Jelly_Cherry.bmp"),
        TEXT("images/Jelly_Flower.bmp"),
        TEXT("images/Jelly_Star.bmp"),
        TEXT("images/Barrier_Bottom.bmp"),
        TEXT("images/Barrier_Bottom2.bmp"),
        TEXT("images/Barrier_Bottom3.bmp"),
        TEXT("images/Barrier_Top1.bmp"),
        TEXT("images/Barrier_Top2.bmp"),
        TEXT("images/Item_HP2.bmp"),
        TEXT("images/Item_Speed.bmp")
    };

    cntObjImg = sizeof(imageFiles) / sizeof(imageFiles[0]);

    for (int i = 0; i < cntObjImg; ++i) {
        newObjImg = new ObjImageInfo(LoadObjImgInfo(imageFiles[i]));
        ObjImg.push_back(newObjImg);
    }
    
    // 파일 입출력
    std::ifstream inFile("object_data.txt");

    if (!inFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
    }
    
    string header;
    getline(inFile, header);

    string line;

    while (std::getline(inFile, line)) 
    {
        std::istringstream iss(line);

        int tempX, tempY, tempDamage, tempScore, tempIdx;

        char delimiter;
        if (iss >> tempX >> delimiter >> tempY >> delimiter >> tempDamage >> delimiter >> tempScore >> delimiter >> tempIdx)
        {
            newObj = new Object{ { tempX, tempY }, tempDamage, tempScore, tempIdx };
            obj.push_back(newObj);
        }
    }
}

void cMap::DrawBitmap(HDC hdc, int health, int vScreenMinX, int vScreenMaxX, RECT playerRect)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    this->playerRect = playerRect;

    // Background
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImg);
        
	TransparentBlt(hdc, 0, 0, (bitBack.bmWidth - backCurFrame) * 2, bitBack.bmHeight * 2,
        hMemDC, backCurFrame, 0, bitBack.bmWidth - backCurFrame, bitBack.bmHeight, NULL);
        
    TransparentBlt(hdc, (bitBack.bmWidth - backCurFrame) * 2, 0, bitBack.bmWidth * 2, bitBack.bmHeight * 2,
        hMemDC, 0, 0, bitBack.bmWidth, bitBack.bmHeight, NULL);
       
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

    // Bridge
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBridgeImg);

    for (int i = 0; i < 15; i++)
    {
        ptBridge.x = bitBridge.bmWidth * i - bridgeCurFrame;

        TransparentBlt(hdc, ptBridge.x, ptBridge.y, bitBridge.bmWidth, bitBridge.bmHeight,
            hMemDC, 0, 0, bitBridge.bmWidth, bitBridge.bmHeight, NULL);
    }

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    // Object
    cntScreenObj = 0;

    for (int i = 0; i < obj.size(); i++)
    {
        if (obj[i]->ptObj.x > vScreenMaxX) break;

        if (obj[i]->ptObj.x >= vScreenMinX - 100)
        {
            hMemDC = CreateCompatibleDC(hdc);
            hOldBitmap = (HBITMAP)SelectObject(hMemDC, ObjImg[obj[i]->idxObjImg]->hObjImg);

            TransparentBlt(hdc, obj[i]->ptObj.x - vScreenMinX, obj[i]->ptObj.y,
                ObjImg[obj[i]->idxObjImg]->bitObjImg.bmWidth, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmHeight,
                hMemDC, 0, 0, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmWidth, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmHeight, NULL);
            
            cntScreenObj++;

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }
        else if (obj[i]->ptObj.x < vScreenMinX)
        {
            obj.erase(obj.begin() + i);
        }
    }
    OnCollision();
    
    // Gauge
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hGaugeImg);
   
    TransparentBlt(hdc, 450, 20, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health) - damage, bitGauge.bmHeight,
        hMemDC, 0, 0, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health) - damage, bitGauge.bmHeight, NULL);

    if (bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health) - damage < -50) Death = true;

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"CookieRun Regular");

    SetTextColor(hdc, RGB(255, 255, 255));
    SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);

    wstringstream stream;
    stream << L"SCORE : " << score;
    wstring text = stream.str();
    TextOut(hdc, 750 - ((text.length() - 9) * 5), 75, text.c_str(), text.length());

    ReleaseDC(NULL, hdc);

    // Heart
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hHeartImg);

    TransparentBlt(hdc, 420, 20, bitHeart.bmWidth, bitHeart.bmHeight,
        hMemDC, 0, 0, bitHeart.bmWidth, bitHeart.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

ObjImageInfo cMap::LoadObjImgInfo(const TCHAR* filename)
{
    ObjImageInfo imageInfo = { NULL };

    imageInfo.hObjImg = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (imageInfo.hObjImg) {
        GetObject(imageInfo.hObjImg, sizeof(BITMAP), &imageInfo.bitObjImg);
    }
    return imageInfo;
}

void cMap::UpdateFrame()
{
    backCurFrame++;
    if ((bitBack.bmWidth - backCurFrame) * 2 <= 0)
        backCurFrame = 0;

    if (bitBridge.bmWidth - bridgeCurFrame <= 0)
        bridgeCurFrame = 17;
    else
        bridgeCurFrame += 13;
}

int cMap::GetDamage()
{
    return damage;
}

int cMap::GetScore()
{
    return score;
}

bool cMap::GetDeath()
{
    return Death;
}

void cMap::OnCollision()
{
    for (int i = 0; i < cntScreenObj; i++)
    {
        if (obj[i]->ptObj.x >= playerRect.left && obj[i]->ptObj.x <= playerRect.right
            && obj[i]->ptObj.y >= playerRect.top && obj[i]->ptObj.y <= playerRect.bottom)
        {
            score += obj[i]->score;
            damage += obj[i]->damage;

            if(obj[i]->damage == 0)
                obj.erase(obj.begin() + i);
        }
    }
}
