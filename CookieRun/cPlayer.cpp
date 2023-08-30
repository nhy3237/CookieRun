#include "cPlayer.h"

cPlayer::cPlayer()
{
    runFrameMax = 0;
    runFrameMin = 0;
    numCurFrame = runFrameMin;
    frameRow = 0;
    ptFrame = { 0,0 };

    ptCookie = { 100, cookieHeight };
    cookieState = RUN;

    curJump = false;
    curDblJump = false;
    dblJumpFlg = false;
    cntJump = 0;

    health = 100;
}

cPlayer::~cPlayer()
{
    DeleteObject(hCookieImg);
}

void cPlayer::CreateBitmap()
{
    hCookieImg = (HBITMAP)LoadImage(NULL, TEXT("images/Cookie_Apple.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hCookieImg, sizeof(BITMAP), &bitCookie);

    cookieState = RUN;
    frameRow = 1;
    runFrameMin = 0; 
    runFrameMax = 3;
    numCurFrame = runFrameMin;
}

void cPlayer::DrawBitmap(HDC hdc)
{
    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hCookieImg);

    ptFrame = { numCurFrame * ptSize.x + 2, frameRow * ptSize.y + 2 };

    TransparentBlt(hdc, ptCookie.x, ptCookie.y, ptSize.x, ptSize.y, 
                    hMemDC, ptFrame.x, ptFrame.y, ptSize.x - 2, ptSize.y - 2, NULL);
    
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, 270, 460, 370, 620); // run

    Rectangle(hdc, 270 - 40, 460 + 60, 370, 620); // slide
    
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void cPlayer::Move(int cookieState)
{
    if (cookieState != JUMP && ptCookie.y != cookieHeight)
    {
        dblJumpFlg = true;
        return;
    }

    switch (cookieState)
    {
    case RUN:
        if (this->cookieState != RUN)
        {
            frameRow = 1;
            runFrameMin = 0;
            runFrameMax = 3;
            numCurFrame = runFrameMin;

            this->cookieState = RUN;

            curJump = false;
            curDblJump = false;
            dblJumpFlg = false;

            ptCookie.x = 100;
        }
        break;

    case JUMP:
        if (this->cookieState != JUMP)
        {
            frameRow = 0;
            runFrameMin = 7;
            runFrameMax = 8;
            numCurFrame = runFrameMin;

            cntJump = 0;
            curJump = true;
            ptCookie.x += 20;
            curDblJump = false;
            dblJumpFlg = false;

            this->cookieState = JUMP;
        }
        else if (this->cookieState == JUMP)
        {
            if (ptCookie.y == cookieHeight && curJump)
            {
                frameRow = 1;
                runFrameMin = 0;
                runFrameMax = 3;
                numCurFrame = runFrameMin;

                curJump = false;
                ptCookie.x = 100;
            }
            else if (ptCookie.y != cookieHeight && dblJumpFlg && !curDblJump)
            {
                runFrameMin = 0;
                runFrameMax = 4;
                numCurFrame = runFrameMin;

                cntJump = 0;
                curDblJump = true;
            }
        }
        break;

    case SLIDE:
        if (this->cookieState != SLIDE)
        {
            frameRow = 0;
            runFrameMin = 9;
            runFrameMax = 10;
            numCurFrame = runFrameMin;

            this->cookieState = SLIDE;
            
            curJump = false;
            curDblJump = false;
            dblJumpFlg = false;

            ptCookie.x = 100;
        }
        break;
    }
}

void cPlayer::UpdateFrame()
{
    numCurFrame++;
    if (numCurFrame > runFrameMax)
    {
        numCurFrame = runFrameMin;
    }
    

    if (cookieState == JUMP)
    {
        if (cntJump < 13)
            ptCookie.y -= 12;
        else if (cntJump > 13 && ptCookie.y != cookieHeight)
        {
            ptCookie.y += 12;
            if (curDblJump) numCurFrame = 5;
            if (ptCookie.y == cookieHeight) numCurFrame = 6;
        }
        cntJump++;
    }
}

int cPlayer::GetHealth()
{
    return health -= 1;
}

int cPlayer::GetPlayerX()
{
    return ptCookie.x;
}
