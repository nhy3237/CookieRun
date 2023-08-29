#include "cMainGame.h"

cMainGame::cMainGame()
{
    playerHealth = 100;
}

cMainGame::~cMainGame()
{
    DeleteObject(hLoadImg);
    DeleteObject(hDoubleBufferImg);
}

void cMainGame::Load(HDC hdc)
{
    hLoadImg = (HBITMAP)LoadImage(NULL, TEXT("images/Load.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hLoadImg, sizeof(BITMAP), &bitLoad);

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLoadImg);

    TransparentBlt(hdc, 0, 0, bitLoad.bmWidth, bitLoad.bmHeight,
        hMemDC, 0, 0, bitLoad.bmWidth, bitLoad.bmHeight, NULL);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::Setup(HWND hWnd)
{
    GetClientRect(hWnd, &rectView);

    cookie.CreateBitmap();
    map.CreateBg();
    map.CreateUI();
    map.CreateObject();
}

void cMainGame::Update(HWND hWnd)
{
    UpdateMove();
    cookie.UpdateFrame();
    map.UpdateFrame();

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

    map.DrawBitmap(hMemDC, playerHealth);
    cookie.DrawBitmap(hMemDC);

    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom,
        hMemDC, 0, 0, rectView.right, rectView.bottom,
        RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cMainGame::UpdateMove()
{
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
