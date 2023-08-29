#include "cMap.h"

cMap::cMap()
{
    backCurFrame = 0;
    bridgeCurFrame = 0;

    ptBridge.y = 622;

    cntObject = 0;
    xObject = 1630;

    const TCHAR* imageFiles[] = {
        TEXT("images/Jelly_Basic.bmp"),
        TEXT("images/Jelly_Basic2.bmp"),
        TEXT("images/Jelly_Rainbow.bmp"),
        TEXT("images/Jelly_Apple.bmp"),
        TEXT("images/Jelly_Cherry.bmp"),
        TEXT("images/Jelly_Flower.bmp"),
        TEXT("images/Barrier_Bottom.bmp"),
        TEXT("images/Barrier_Top1.bmp"),
        TEXT("images/Barrier_Top2.bmp")
    };
}

cMap::~cMap()
{
    DeleteObject(hBackImg);
    DeleteObject(hBridgeImg);
    DeleteObject(hJellyImg);
    DeleteObject(hGaugeImg);
    DeleteObject(hGaugeBgImg);
    DeleteObject(hHeartImg);
    
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
    // Jelly
    hJellyImg = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Basic.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hJellyImg, sizeof(BITMAP), &bitJelly);

    // Jelly2
    hJelly2Img = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Basic2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hJelly2Img, sizeof(BITMAP), &bitJelly2);

    // RainbowJelly
    hRJellyImg = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Rainbow.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hRJellyImg, sizeof(BITMAP), &bitRJelly);

    // AppleJelly
    hAJellyImg = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Apple.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hAJellyImg, sizeof(BITMAP), &bitAJelly);

    // CherryJelly
    hCJellyImg = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Cherry.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hCJellyImg, sizeof(BITMAP), &bitCJelly);

    // FlowerJelly
    hFJellyImg = (HBITMAP)LoadImage(NULL, TEXT("images/Jelly_Flower.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hFJellyImg, sizeof(BITMAP), &bitFJelly);

    // Barrier_Bottom
    hBBarrier = (HBITMAP)LoadImage(NULL, TEXT("images/Barrier_Bottom.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hBBarrier, sizeof(BITMAP), &bitBBarrier);

    // Barrier_Bottom2
    hB2Barrier = (HBITMAP)LoadImage(NULL, TEXT("images/Barrier_Bottom2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hB2Barrier, sizeof(BITMAP), &bitB2Barrier);

    // Barrier_Top1
    hTBarrier1 = (HBITMAP)LoadImage(NULL, TEXT("images/Barrier_Top1.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hTBarrier1, sizeof(BITMAP), &bitTBarrier1);

    // Barrier_Top2
    hTBarrier2 = (HBITMAP)LoadImage(NULL, TEXT("images/Barrier_Top2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hTBarrier2, sizeof(BITMAP), &bitTBarrier2);

    // Item_BigHP
    hHpItem = (HBITMAP)LoadImage(NULL, TEXT("images/Item_HP.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hHpItem, sizeof(BITMAP), &bitHpItem);

    // Item_SmallHP
    hHp2Item = (HBITMAP)LoadImage(NULL, TEXT("images/Item_HP2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hHp2Item, sizeof(BITMAP), &bitHp2Item);

    /*for (int i = 0; i < 7; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };
        obj.push_back(newObj);
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3)
            newObj = { { xObject += 60, 440 }, 0, 20, hRJellyImg, bitRJelly };
        else
            newObj = { { xObject += 60, 390 }, 0, 30, hAJellyImg, bitAJelly };
        
        obj.push_back(newObj);
    }

    for (int i = 0; i < 21; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3)
            newObj = { { xObject += 60, 440 }, 0, 20, hRJellyImg, bitRJelly };
        else
            newObj = { { xObject += 60, 390 }, 0, 30, hAJellyImg, bitAJelly };

        obj.push_back(newObj);
    }
    

    for (int i = 0; i < 11; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };
        obj.push_back(newObj);
    }

    xObject += 140;

    for (int i = 0; i < 20; i++)
    {
        switch (i % 4)
        {
        case 0:
            newObj = { { xObject, 450 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject - 15, 390 - 5 }, 0, 30, hAJellyImg, bitAJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 330 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            break;

        case 1:
            newObj = { { xObject, 450 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 390 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 330 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            break;

        case 2:
            newObj = { { xObject - 15, 450 - 5 }, 0, 30, hAJellyImg, bitAJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 390 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 330 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            break;

        case 3:
            newObj = { { xObject, 450 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject, 390 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);

            newObj = { { xObject - 15, 330 - 5 }, 0, 30, hAJellyImg, bitAJelly };
            obj.push_back(newObj);
            break;
        }
        xObject += 70;
    }

    xObject += 140;
    
    for (int i = 0; i < 16; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };
        obj.push_back(newObj);
    }

    // 하단 장애물
    for (int i = 0; i < 5; i++)
    {
        if (i == 0 || i == 4)
            newObj = { { xObject += 60, 440 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 2)
            newObj = { { xObject - 20, 500 }, 10, 0, hBBarrier, bitBBarrier };
        else
            newObj = { { xObject += 60, 390 }, 0, 30, hAJellyImg, bitAJelly };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 16; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);
    }

    // 하단 장애물
    for (int i = 0; i < 5; i++)
    {
        if (i == 0 || i == 4)
            newObj = { { xObject += 60, 440 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 2)
            newObj = { { xObject - 20, 500 }, 10, 0, hBBarrier, bitBBarrier };
        else
            newObj = { { xObject += 60, 390 }, 0, 30, hAJellyImg, bitAJelly };

        obj.push_back(newObj);
    }
    
    
    for (int i = 0; i < 6; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);
    }

    xObject += 140;
    
    // 둥근 모양
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            switch (j)
            {
            case 0:
                newObj = { {xObject += 35, 370}, 0, 10, hJellyImg, bitJelly };
                obj.push_back(newObj);
                newObj = { {xObject, 420}, 0, 10, hJelly2Img, bitJelly2 };

                break;
            case 1:
                newObj = { {xObject += 35, 340}, 0, 10, hJelly2Img, bitJelly2 };
                obj.push_back(newObj);
                newObj = { {xObject, 450}, 0, 10, hJellyImg, bitJelly };
                break;
            case 2:
                if (i % 2 == 0)
                    newObj = { {xObject += 30, 390}, 0, 50, hFJellyImg, bitFJelly };
                else
                    newObj = { {xObject += 20, 390}, 0, 40, hCJellyImg, bitCJelly };
                obj.push_back(newObj);
                xObject += 15;
                break;
            case 3:
                newObj = { {xObject += 35, 340}, 0, 10, hJellyImg, bitJelly };
                obj.push_back(newObj);
                newObj = { {xObject, 450}, 0, 10, hJelly2Img, bitJelly2 };
                break;
            case 4:
                newObj = { {xObject += 35, 370}, 0, 10, hJelly2Img, bitJelly2 };
                obj.push_back(newObj);
                newObj = { {xObject, 420}, 0, 10, hJellyImg, bitJelly };
                break;
            }

            obj.push_back(newObj);
        }

        xObject += 300;
    }
    

    for (int i = 0; i < 16; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);

    }

    // 하단 장애물 - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
            newObj = { { xObject += 60, 380 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 1 || i == 5)
            newObj = { { xObject += 60, 260 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 2 || i == 4)
            newObj = { { xObject += 60, 200 }, 0, 30, hAJellyImg, bitAJelly };
        else if (i == 3)
            newObj = { { xObject - 20, 370 }, 10, 0, hB2Barrier, bitB2Barrier };

        obj.push_back(newObj);
    }
    
    for (int i = 0; i < 16; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);
    }

    // 하단 장애물 - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
            newObj = { { xObject += 60, 380 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 1 || i == 5)
            newObj = { { xObject += 60, 260 }, 0, 20, hRJellyImg, bitRJelly };
        else if (i == 2 || i == 4)
            newObj = { { xObject += 60, 200 }, 0, 30, hAJellyImg, bitAJelly };
        else if (i == 3)
            newObj = { { xObject - 20, 370 }, 20, 0, hB2Barrier, bitB2Barrier };

        obj.push_back(newObj);
    }
    
    for (int i = 0; i < 11; i++)
    {
        newObj = { {xObject += 70, 500}, 0, 10, hJellyImg, bitJelly };

        obj.push_back(newObj);
    }

    xObject += 250;
    */

    // 하단 장애물X - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
        {
            newObj = { { xObject += 40, 410 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 365 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 1 || i == 5)
        {
            newObj = { { xObject += 40, 365 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 320 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 2 || i == 4)
        {
            newObj = { { xObject += 40, 320 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 275 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 3)
        {
            newObj = { { xObject += 55, 220 }, 0, 50, hFJellyImg, bitFJelly };
            xObject += 40;
        }

        obj.push_back(newObj);
    }

    xObject += 200;

    // 하단 장애물X - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
        {
            newObj = { { xObject += 40, 410 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            newObj = { { xObject, 365 }, 0, 10, hJellyImg, bitJelly };
        }
        else if (i == 1 || i == 5)
        {
            newObj = { { xObject += 40, 365 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            newObj = { { xObject, 320 }, 0, 10, hJellyImg, bitJelly };
        }
        else if (i == 2 || i == 4)
        {
            newObj = { { xObject += 40, 320 }, 0, 10, hJellyImg, bitJelly };
            obj.push_back(newObj);
            newObj = { { xObject, 275 }, 0, 10, hJellyImg, bitJelly };
        }
        else if (i == 3)
        {
            newObj = { { xObject += 55, 220 }, 0, 40, hCJellyImg, bitCJelly };
            xObject += 40;
        }

        obj.push_back(newObj);
    }

    xObject += 200;

    // 하단 장애물X - 더블 점프 + 체력
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
        {
            newObj = { { xObject += 40, 410 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 365 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 1 || i == 5)
        {
            newObj = { { xObject += 40, 365 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 320 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 2 || i == 4)
        {
            newObj = { { xObject += 40, 320 }, 0, 10, hJelly2Img, bitJelly2 };
            obj.push_back(newObj);
            newObj = { { xObject, 275 }, 0, 10, hJelly2Img, bitJelly2 };
        }
        else if (i == 3)
        {
            newObj = { { xObject += 40, 220 }, -20, 0, hHp2Item, bitHp2Item};
            xObject += 50;
        }

        obj.push_back(newObj);
    }
}

void cMap::DrawBitmap(HDC hdc, int health)
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
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, obj[i].hObjImg);

        TransparentBlt(hdc, obj[i].ptObj.x - cntObject, obj[i].ptObj.y, obj[i].bitObj.bmWidth, obj[i].bitObj.bmHeight,
            hMemDC, 0, 0, obj[i].bitObj.bmWidth, obj[i].bitObj.bmHeight, NULL);

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }
    cntObject += 13;

    // Gauge
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hGaugeImg);
   
    TransparentBlt(hdc, 450, 20, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health), bitGauge.bmHeight,
        hMemDC, 0, 0, bitGauge.bmWidth - bitGauge.bmWidth / 100 * (100 - health), bitGauge.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    // Heart
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hHeartImg);

    TransparentBlt(hdc, 420, 20, bitHeart.bmWidth, bitHeart.bmHeight,
        hMemDC, 0, 0, bitHeart.bmWidth, bitHeart.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
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
