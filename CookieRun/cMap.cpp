#include "cMap.h"

cMap::cMap()
{
    backCurFrame = 0;
    bridgeCurFrame = 0;

    ptBridge.y = 622;

    cntObject = 0;
}

cMap::~cMap()
{
    for (int i = 0; i < objImgCnt; ++i) {
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

    objImgCnt = sizeof(imageFiles) / sizeof(imageFiles[0]);

    for (int i = 0; i < objImgCnt; ++i) {
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

void cMap::DrawBitmap(HDC hdc, int health, int vScreenMinX, int vScreenMaxX)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

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
    for (int i = 0; i < obj.size(); i++)
    {
        if (obj[i]->ptObj.x >= vScreenMinX - 100 && obj[i]->ptObj.x <= vScreenMaxX)
        {
            hMemDC = CreateCompatibleDC(hdc);
            hOldBitmap = (HBITMAP)SelectObject(hMemDC, ObjImg[obj[i]->idxObjImg]->hObjImg);

            TransparentBlt(hdc, obj[i]->ptObj.x - cntObject, obj[i]->ptObj.y,
                ObjImg[obj[i]->idxObjImg]->bitObjImg.bmWidth, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmHeight,
                hMemDC, 0, 0, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmWidth, ObjImg[obj[i]->idxObjImg]->bitObjImg.bmHeight, NULL);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }
        else if (obj[i]->ptObj.x < vScreenMinX)
        {
            obj.erase(obj.begin() + i);
        }
    }
    
    // Gauge
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hGaugeImg);
   
    TransparentBlt(hdc, 450, 20, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health), bitGauge.bmHeight,
        hMemDC, 0, 0, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health), bitGauge.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    LPCWSTR text = L"SCORE";
    TextOut(hdc, 10, 10, text, wcslen(text));

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

    cntObject += 13;
}

void cMap::OnCollision()
{

}

int cMap::GetDamage()
{
    return damage;
}

int cMap::GetScore()
{
    return score;
}
