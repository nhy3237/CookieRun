#include "cMainGame.h"

cMainGame::cMainGame()
{
    playerHealth = 100;
    score = 0;
    bgmPlay = false;
}

cMainGame::~cMainGame()
{
    DeleteObject(hSceneImg);
    DeleteObject(hDoubleBufferImg);
}

void cMainGame::LoadScreen(HDC hdc)
{
    hSceneImg = (HBITMAP)LoadImage(NULL, TEXT("images/Load.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSceneImg, sizeof(BITMAP), &bitScene);

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSceneImg);

    TransparentBlt(hdc, 0, 0, bitScene.bmWidth, bitScene.bmHeight,
        hMemDC, 0, 0, bitScene.bmWidth, bitScene.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::StartScreen(HDC hdc)
{
    hSceneImg = (HBITMAP)LoadImage(NULL, TEXT("images/Start.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSceneImg, sizeof(BITMAP), &bitScene);

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSceneImg);

    TransparentBlt(hdc, 0, 0, bitScene.bmWidth, bitScene.bmHeight,
        hMemDC, 0, 0, bitScene.bmWidth, bitScene.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::EndScreen(HDC hdc)
{
    if (!bgmPlay)
    {
        bgmPlay = true;
        PlaySound(TEXT("bgm/Lobby2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT | SND_LOOP);
        }

    hSceneImg = (HBITMAP)LoadImage(NULL, TEXT("images/End2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSceneImg, sizeof(BITMAP), &bitScene);

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSceneImg);

    TransparentBlt(hdc, 0, 0, bitScene.bmWidth, bitScene.bmHeight,
        hMemDC, 0, 0, bitScene.bmWidth, bitScene.bmHeight, NULL);

    HFONT hFont = CreateFont(90, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"CookieRun Bold");

    SetTextColor(hdc, RGB(0, 0, 0));
    SelectObject(hdc, hFont);
    SetBkMode(hdc, RGB(0, 0, 0));

    wstringstream stream;
    stream << L"SCORE : " << score;
    wstring text = stream.str();
    TextOut(hdc, 600 - ((text.length() - 9) * 5), 300, text.c_str(), text.length());

    ReleaseDC(NULL, hdc);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::Setup(HWND hWnd)
{
    GetClientRect(hWnd, &rectView);

    vScreenMinX = rectView.left;
    vScreenMaxX = rectView.right;
    vPlayerRect = cookie.GetPlayerRect();

    cookie.CreateBitmap();
    map.CreateBg();
    map.CreateUI();
    map.CreateObject();

    AddFontResourceEx(L"font/CookieRun Bold.ttf", FR_PRIVATE, NULL);
}

void cMainGame::Update(HWND hWnd)
{
    vScreenMinX += 13;
    vScreenMaxX += 13;

    UpdateMove();
    map.UpdateFrame();
    cookie.UpdateFrame();
    
    vPlayerRect = cookie.GetPlayerRect();
    vPlayerRect.left += vScreenMinX;
    vPlayerRect.right += vScreenMinX;

    InvalidateRect(hWnd, NULL, false);
}

void cMainGame::Render(HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImg == NULL)
    {
        hDoubleBufferImg = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImg);

    if (score > 0)
        EndScreen(hMemDC);
    else
    {
        map.DrawBitmap(hMemDC, playerHealth, vScreenMinX, vScreenMaxX, vPlayerRect);
        cookie.DrawBitmap(hMemDC);
    }

    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom,
        hMemDC, 0, 0, rectView.right, rectView.bottom,
        RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::UpdateMove()
{
    //if (score > 0) cookie.Move(DEATH);
    if (GetKeyState('J') & 0x8000)
    {
        cookie.Move(JUMP);
    }
    else if (GetKeyState('S') & 0x8000)
    {
        cookie.Move(SLIDE);
    }
    else
    {
        cookie.Move(RUN);
    }
}

void cMainGame::UpdateHealth()
{
    playerHealth = cookie.GetHealth();
}

bool cMainGame::GetHealth()
{
    if (map.GetDeath())
    {
        score = map.GetScore();
        return true;
    }
    else
        return false;
}
