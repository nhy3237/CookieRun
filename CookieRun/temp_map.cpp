#include "cMap.h"

cMap::cMap()
{
    backCurFrame = 0;
    bridgeCurFrame = 0;

    ptBridge.y = 622;

    cntObject = 0;
    xObject = 1630;
}

cMap::~cMap()
{
    for (int i = 0; i < imageCnt; ++i) {
        if (Img[i]->hImage) {
            DeleteObject(Img[i]->hImage);
        }
    }

    Img.clear();
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

    imageCnt = sizeof(imageFiles) / sizeof(imageFiles[0]);

    for (int i = 0; i < imageCnt; ++i) {
        newImg = new ImageInfo(LoadImageInfo(imageFiles[i]));
        Img.push_back(newImg);
    }

    // 파일 입출력
    std::ofstream  outFile("object_data.txt");

    for (int i = 0; i < 7; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        obj.push_back(newObj);
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3)
            newObj = new Object{ { xObject += 60, 440 }, 0, 20, jRain };
        else
            newObj = new Object{ { xObject += 60, 390 }, 0, 30, jApple };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 21; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3)
            newObj = new Object{ { xObject += 60, 440 }, 0, 20, jRain };
        else
            newObj = new Object{ { xObject += 60, 390 }, 0, 30, jApple };

        obj.push_back(newObj);
    }


    for (int i = 0; i < 11; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        obj.push_back(newObj);
    }

    xObject += 140;

    for (int i = 0; i < 20; i++)
    {
        switch (i % 4)
        {
        case 0:
            newObj = new Object{ { xObject, 450 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject - 15, 390 - 5 }, 0, 30, jApple };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 330 }, 0, 10, jBasic };
            obj.push_back(newObj);
            break;

        case 1:
            newObj = new Object{ { xObject, 450 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 390 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 330 }, 0, 10, jBasic };
            obj.push_back(newObj);
            break;

        case 2:
            newObj = new Object{ { xObject - 15, 450 - 5 }, 0, 30, jApple };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 390 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 330 }, 0, 10, jBasic };
            obj.push_back(newObj);
            break;

        case 3:
            newObj = new Object{ { xObject, 450 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject, 390 }, 0, 10, jBasic };
            obj.push_back(newObj);

            newObj = new Object{ { xObject - 15, 330 - 5 }, 0, 30, jApple };
            obj.push_back(newObj);
            break;
        }
        xObject += 70;
    }

    xObject += 140;

    for (int i = 0; i < 16; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        obj.push_back(newObj);
    }

    // 하단 장애물
    for (int i = 0; i < 5; i++)
    {
        if (i == 0 || i == 4)
            newObj = new Object{ { xObject += 60, 440 }, 0, 20, jRain };
        else if (i == 2)
            newObj = new Object{ { xObject - 20, 500 }, 10, 0, bBottom };
        else
            newObj = new Object{ { xObject += 60, 390 }, 0, 30, jApple };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 16; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

        obj.push_back(newObj);
    }

    // 하단 장애물
    for (int i = 0; i < 5; i++)
    {
        if (i == 0 || i == 4)
            newObj = new Object{ { xObject += 60, 440 }, 0, 20, jRain };
        else if (i == 2)
            newObj = new Object{ { xObject - 20, 500 }, 10, 0, bBottom };
        else
            newObj = new Object{ { xObject += 60, 390 }, 0, 30, jApple };

        obj.push_back(newObj);
    }


    for (int i = 0; i < 6; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

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
                newObj = new Object{ {xObject += 35, 370}, 0, 10, jBasic };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 420}, 0, 10, jBasic2 };

                break;
            case 1:
                newObj = new Object{ {xObject += 35, 340}, 0, 10, jBasic2 };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 450}, 0, 10, jBasic };
                break;
            case 2:
                if (i % 2 == 0)
                    newObj = new Object{ {xObject += 30, 390}, 0, 50, jFlower };
                else
                    newObj = new Object{ {xObject += 20, 390}, 0, 40, jCherry };
                obj.push_back(newObj);
                xObject += 15;
                break;
            case 3:
                newObj = new Object{ {xObject += 35, 340}, 0, 10, jBasic };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 450}, 0, 10, jBasic2 };
                break;
            case 4:
                newObj = new Object{ {xObject += 35, 370}, 0, 10, jBasic2 };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 420}, 0, 10, jBasic };
                break;
            }

            obj.push_back(newObj);
        }

        xObject += 300;
    }


    for (int i = 0; i < 16; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

        obj.push_back(newObj);

    }

    // 하단 장애물 - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
            newObj = new Object{ { xObject += 60, 380 }, 0, 20, jRain };
        else if (i == 1 || i == 5)
            newObj = new Object{ { xObject += 60, 260 }, 0, 20, jRain };
        else if (i == 2 || i == 4)
            newObj = new Object{ { xObject += 60, 200 }, 0, 30, jApple };
        else if (i == 3)
            newObj = new Object{ { xObject - 20, 375 }, 20, 0, bBottom2 };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 16; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

        obj.push_back(newObj);
    }

    // 하단 장애물 - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
            newObj = new Object{ { xObject += 60, 380 }, 0, 20, jRain };
        else if (i == 1 || i == 5)
            newObj = new Object{ { xObject += 60, 260 }, 0, 20, jRain };
        else if (i == 2 || i == 4)
            newObj = new Object{ { xObject += 60, 200 }, 0, 30, jApple };
        else if (i == 3)
            newObj = new Object{ { xObject - 20, 375 }, 20, 0, bBottom2 };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 11; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };

        obj.push_back(newObj);
    }

    xObject += 250;

    // 하단 장애물X - 더블 점프
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
        {
            newObj = new Object{ { xObject += 40, 410 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 365 }, 0, 10, jBasic2 };
        }
        else if (i == 1 || i == 5)
        {
            newObj = new Object{ { xObject += 40, 365 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 320 }, 0, 10, jBasic2 };
        }
        else if (i == 2 || i == 4)
        {
            newObj = new Object{ { xObject += 40, 320 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 275 }, 0, 10, jBasic2 };
        }
        else if (i == 3)
        {
            newObj = new Object{ { xObject += 55, 220 }, 0, 50, jFlower };
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
            newObj = new Object{ { xObject += 40, 410 }, 0, 10, jBasic };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 365 }, 0, 10, jBasic };
        }
        else if (i == 1 || i == 5)
        {
            newObj = new Object{ { xObject += 40, 365 }, 0, 10, jBasic };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 320 }, 0, 10, jBasic };
        }
        else if (i == 2 || i == 4)
        {
            newObj = new Object{ { xObject += 40, 320 }, 0, 10, jBasic };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 275 }, 0, 10, jBasic };
        }
        else if (i == 3)
        {
            newObj = new Object{ { xObject += 55, 220 }, 0, 40, jCherry };
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
            newObj = new Object{ { xObject += 40, 410 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 365 }, 0, 10, jBasic2 };
        }
        else if (i == 1 || i == 5)
        {
            newObj = new Object{ { xObject += 40, 365 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 320 }, 0, 10, jBasic2 };
        }
        else if (i == 2 || i == 4)
        {
            newObj = new Object{ { xObject += 40, 320 }, 0, 10, jBasic2 };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 275 }, 0, 10, jBasic2 };
        }
        else if (i == 3)
        {
            newObj = new Object{ { xObject += 40, 220 }, -20, 0, iHP2 };
            xObject += 50;
        }
        obj.push_back(newObj);
    }


    newObj = new Object{ { xObject += 540, 480 }, 0, 0, iSpeed };
    obj.push_back(newObj);

    xObject += 200;

    for (int i = 0; i < 2; i++)
    {
        newObj = new Object{ { xObject, 375 }, 20, 0, bBottom2 };
        obj.push_back(newObj);

        xObject += 110;

        for (int j = 0; j < 5; j++)
        {
            newObj = new Object{ { xObject += 60, 470 }, 0, 30, jApple };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 520 }, 0, 30, jApple };
            obj.push_back(newObj);
        }
        xObject += 80;
    }

    newObj = new Object{ { xObject, 375 }, 30, 0, bBottom3 };
    obj.push_back(newObj);

    newObj = new Object{ { xObject += 250, 480 }, 0, 0, iSpeed };
    obj.push_back(newObj);

    newObj = new Object{ { xObject += 250, 375 }, 20, 0, bBottom2 };
    obj.push_back(newObj);

    for (int i = 0; i < 2; i++)
    {
        newObj = new Object{ { xObject += 250, 500 }, 10, 0, bBottom };
        obj.push_back(newObj);
    }

    for (int i = 0; i < 6; i++)
    {
        newObj = new Object{ {xObject - 230 + (60 * i), 400}, 0, 10, jBasic };
        obj.push_back(newObj);

        if (i == 1 || i == 4)
        {
            newObj = new Object{ {xObject - 230 + (60 * i), 350}, 0, 10, jBasic };
            obj.push_back(newObj);
        }
        else if (i == 2)
        {
            newObj = new Object{ {xObject - 230 + (55 * i), 260}, 0, 50, jStar };
            obj.push_back(newObj);
        }
    }

    xObject += 250;

    for (int i = 0; i < 2; i++)
    {
        newObj = new Object{ { xObject, 375 }, 30, 0, bBottom3 };
        obj.push_back(newObj);

        xObject += 110;

        for (int j = 0; j < 5; j++)
        {
            newObj = new Object{ { xObject += 60, 470 }, 0, 30, jApple };
            obj.push_back(newObj);
            newObj = new Object{ { xObject, 520 }, 0, 30, jApple };
            obj.push_back(newObj);
        }
        xObject += 80;
    }

    newObj = new Object{ { xObject, 375 }, 30, 0, bBottom3 };
    obj.push_back(newObj);

    xObject += 500;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j % 2 == 1)
            {
                newObj = new Object{ {xObject += 20, 470}, 0, 10, jBasic };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 570}, 0, 10, jBasic };
            }
            else
            {
                newObj = new Object{ {xObject += 20, 520}, 0, 10, jBasic };
            }
            obj.push_back(newObj);
        }

        xObject += 20;

        for (int j = 0; j < 4; j++)
        {
            if (j % 2 == 0)
            {
                newObj = new Object{ {xObject += 20, 470}, 0, 20, jBasic2 };
                obj.push_back(newObj);
                newObj = new Object{ {xObject, 570}, 0, 20, jBasic2 };
            }
            else
            {
                newObj = new Object{ {xObject += 20, 520}, 0, 20, jBasic2 };
            }
            obj.push_back(newObj);
        }

        if (i != 2)
        {
            newObj = new Object{ {xObject += 60, 360}, 0, 50, jStar };
            obj.push_back(newObj);
        }
        xObject += 120;
    }


    for (int i = 0; i < 9; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        obj.push_back(newObj);
    }

    for (int i = 0; i < 14; i++)
    {
        if (i == 0 || i == 13)
            newObj = new Object{ {xObject += 70, 550}, 0, 10, jBasic };
        else if (i == 1 || i == 12)
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic };
        else if (i == 4)
            newObj = new Object{ {xObject - 50, -130}, 30, 0, bTop1 };
        else if (i == 9)
            newObj = new Object{ {xObject - 50, -130}, 30, 0, bTop2 };
        else
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic2 };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            newObj = new Object{ {xObject += 80, 430}, 0, 50, jStar };
            xObject += 90;
        }
        else
        {
            newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        }
        obj.push_back(newObj);
    }

    for (int i = 0; i < 19; i++)
    {
        if (i == 0 || i == 18)
            newObj = new Object{ {xObject += 70, 550}, 0, 10, jBasic };
        else if (i == 1 || i == 17)
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic };
        else if (i == 4 || i == 9 || i == 14)
            newObj = new Object{ {xObject - 50, -130}, 30, 0, bTop2 };
        else
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic2 };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 7; i++)
    {
        if (i == 3)
        {
            newObj = new Object{ {xObject += 70, 480}, 0, 50, iHP2 };
            xObject += 50;
        }
        else
        {
            newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        }
        obj.push_back(newObj);
    }

    for (int i = 0; i < 14; i++)
    {
        if (i == 0 || i == 13)
            newObj = new Object{ {xObject += 70, 550}, 0, 10, jBasic };
        else if (i == 1 || i == 12)
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic };
        else if (i == 4)
            newObj = new Object{ {xObject - 50, -130}, 30, 0, bTop1 };
        else if (i == 9)
            newObj = new Object{ {xObject - 50, -130}, 30, 0, bTop2 };
        else
            newObj = new Object{ {xObject += 60, 570}, 0, 10, jBasic2 };

        obj.push_back(newObj);
    }

    for (int i = 0; i < 6; i++)
    {
        newObj = new Object{ {xObject += 70, 500}, 0, 10, jBasic };
        obj.push_back(newObj);
    }

    // 파일 입출력
    if (!outFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    outFile << "ptObj.x|ptObj.y|damage|score|idxObjImg\n";

    for (int i = 0; i < obj.size(); i++)
    {
        outFile << obj[i]->ptObj.x << "|" << obj[i]->ptObj.y << "|" << obj[i]->damage << "|" << obj[i]->score << "|" << obj[i]->idxObjImg << "\n";
    }

    outFile.close();

    std::cout << "Objects have been saved to 'objects.txt'." << std::endl;

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
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, Img[obj[i]->idxObjImg]->hImage);

        TransparentBlt(hdc, obj[i]->ptObj.x - cntObject, obj[i]->ptObj.y,
            Img[obj[i]->idxObjImg]->bitImage.bmWidth, Img[obj[i]->idxObjImg]->bitImage.bmHeight,
            hMemDC, 0, 0, Img[obj[i]->idxObjImg]->bitImage.bmWidth, Img[obj[i]->idxObjImg]->bitImage.bmHeight, NULL);

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }


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

    cntObject += 13;
}

ImageInfo cMap::LoadImageInfo(const TCHAR* filename) {
    ImageInfo imageInfo = { NULL };

    imageInfo.hImage = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (imageInfo.hImage) {
        GetObject(imageInfo.hImage, sizeof(BITMAP), &imageInfo.bitImage);
    }
    return imageInfo;
}