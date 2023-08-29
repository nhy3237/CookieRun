// CookieRun.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "CookieRun.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// >> : Ani
#pragma comment(lib, "msimg32.lib")

// >> : 배경 및 다리
HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hBridgeImage;
BITMAP bitBridge;

double backCurFrame = 0;
double bridgeCurFrame = 0;
// <<

HBITMAP hLandImage;
BITMAP bitLand;

// >> : Ani
HBITMAP hAniImage;
BITMAP bitAni;

const int SPRITE_SIZE_X = 372;
const int SPRITE_SIZE_Y = 372;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;
int cookieCurFrame = RUN_FRAME_MIN;
int by = 0;
int cookieHeight = 250;
int bridgeHeight = 250;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;

int cookieState = 0;
enum { RUN, JUMP, SLIDE };
int cntJump = 0;
// <<

RECT rectView;

void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void Update();
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK BridgeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK BackProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
// << : Ani

// >> : double buffering
HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
//

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COOKIERUN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COOKIERUN));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COOKIERUN);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FE));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1650, 795, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 쿠키
#define timer_ID_1 111
//배경
#define timer_ID_2 222
//다리
#define timer_ID_3 333

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // Ani
    case WM_CREATE:
    {
        CreateBitmap();
        GetClientRect(hWnd, &rectView);
        SetTimer(hWnd, timer_ID_1, 50, AniProc);
        SetTimer(hWnd, timer_ID_2, 10, BackProc);
        SetTimer(hWnd, timer_ID_3, 50, BridgeProc);


    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        DrawBitmapDoubleBuffering(hWnd, hdc);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, timer_ID_1);
        DeleteBitmap();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void CreateBitmap()
{
    // >> : Land
    {
        hLandImage = (HBITMAP)LoadImage(NULL, TEXT("images/landing.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hLandImage, sizeof(BITMAP), &bitLand);
    }
    //

    // >> : Background
    {
        hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/Map1.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    }

    // >> : Bridge
    {
        hBridgeImage = (HBITMAP)LoadImage(NULL, TEXT("images/bridge.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hBridgeImage, sizeof(BITMAP), &bitBridge);
    }

    // >> : Ani
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/AppleCookie.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        // :
        cookieState = RUN;
        by = 1; // 두 번째 줄
        RUN_FRAME_MAX = 3; // 몇 번째까지 할 지
        RUN_FRAME_MIN = 0; // 몇 번째부터 할 지
        cookieCurFrame = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X; // 총 x 몇 줄
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y; // 총 y 몇 줄
    }
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    cookieCurFrame++;
    if (cookieCurFrame > RUN_FRAME_MAX)
    {
        cookieCurFrame = RUN_FRAME_MIN;
    }

    if (cookieState == JUMP)
    {
        cntJump++;
        if (cntJump < 8)
            cookieHeight -= 25;
        else if (cntJump > 8 && cookieHeight != 250)
            cookieHeight += 25;

        /*if(cookieHeight == 250)
            cookieCurFrame = 6;*/
    }
    Update();
    InvalidateRect(hWnd, NULL, false);
}

VOID CALLBACK BackProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    backCurFrame++;
    if ((bitBack.bmWidth - backCurFrame) * 2 <= 0)
    {
        backCurFrame = 0;
    }
    Update();
    InvalidateRect(hWnd, NULL, false);
}

VOID CALLBACK BridgeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (bitBridge.bmWidth - bridgeCurFrame <= 0)
    {
        bridgeCurFrame = 14;
    }
    else
    {
        bridgeCurFrame += 10;
    }
    Update();
    InvalidateRect(hWnd, NULL, false);
}

void UpdateFrame(HWND hWnd)
{
    cookieCurFrame++;
    if (cookieCurFrame > RUN_FRAME_MAX)
    {
        cookieCurFrame = RUN_FRAME_MIN;
    }

    backCurFrame += 10;
    if ((bitBack.bmWidth - backCurFrame) * 2 < 0)
    {
        backCurFrame = 0;
    }

    bridgeCurFrame += 20;
    if (bitBridge.bmWidth - bridgeCurFrame < 0)
    {
        bridgeCurFrame = 0;
    }

    InvalidateRect(hWnd, NULL, false);
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    { //>> : 배경
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

        TransparentBlt(hdc, 0, 0, bitBack.bmWidth * 2, bitBack.bmHeight * 2, hMemDC, 0, 0, bitBack.bmWidth, bitBack.bmHeight, NULL);
        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    { //>> : Ani
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        int xStart = (cookieCurFrame * SPRITE_SIZE_X) + 2; // +2는 빨간 선 문제
        int yStart = (by * SPRITE_SIZE_Y) + 2;

        TransparentBlt(hdc, 100, cookieHeight, SPRITE_SIZE_X, SPRITE_SIZE_Y, hMemDC, xStart, yStart, SPRITE_SIZE_X - 2, SPRITE_SIZE_Y - 2, NULL);

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    { // : 배경
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);

        TransparentBlt(hMemDC, 0, 0, (bitBack.bmWidth - backCurFrame) * 2, bitBack.bmHeight * 2,
            hMemDC2, backCurFrame, 0, bitBack.bmWidth - backCurFrame, bitBack.bmHeight, NULL);

        TransparentBlt(hMemDC, (bitBack.bmWidth - backCurFrame) * 2, 0, bitBack.bmWidth * 2, bitBack.bmHeight * 2,
            hMemDC2, 0, 0, bitBack.bmWidth, bitBack.bmHeight, NULL);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    { // : 다리
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBridgeImage);

        for (int i = 0; i < 15; i++)
        {
            TransparentBlt(hMemDC, bitBridge.bmWidth * i - bridgeCurFrame, bridgeHeight + SPRITE_SIZE_Y, bitBridge.bmWidth, bitBridge.bmHeight,
                hMemDC2, 0, 0, bitBridge.bmWidth, bitBridge.bmHeight, NULL);
        }

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    { //>> : Ani
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);

        int xStart = (cookieCurFrame * SPRITE_SIZE_X) + 2; // +2는 빨간 선 문제
        int yStart = (by * SPRITE_SIZE_Y) + 2;

        TransparentBlt(hMemDC, 100, cookieHeight, SPRITE_SIZE_X, SPRITE_SIZE_Y, hMemDC2, xStart, yStart, SPRITE_SIZE_X - 2, SPRITE_SIZE_Y - 2, NULL);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom,
        hMemDC, 0, 0, rectView.right, rectView.bottom,
        RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hLandImage);
    DeleteObject(hBackImage);
    DeleteObject(hBridgeImage);
}

void Update()
{
    if (cookieState == JUMP && cookieHeight != 250)
        return;

    if (GetKeyState('J') & 0x8000) // 점프
    {

        by = 0; // 첫 번째 줄
        RUN_FRAME_MIN = 7; // 몇 번째부터 할 지
        RUN_FRAME_MAX = 8; // 몇 번째까지 할 지

        if (cookieState != JUMP)
        {
            cookieCurFrame = RUN_FRAME_MIN;
            cntJump = 0;
            cookieHeight = 250;
        }
        cookieState = JUMP;
    }
    else if (GetKeyState('S') & 0x8000) // 슬라이드
    {

        by = 0; // 첫 번째 줄
        RUN_FRAME_MIN = 9; // 몇 번째부터 할 지
        RUN_FRAME_MAX = 10; // 몇 번째까지 할 지
        if (cookieState != SLIDE)
        {
            if (cookieCurFrame >= RUN_FRAME_MAX || cookieCurFrame < RUN_FRAME_MIN)
                cookieCurFrame = RUN_FRAME_MIN;
        }
        cookieState = SLIDE;
        cookieHeight = 250;
    }
    else
    {
        by = 1; // 두 번째 줄
        RUN_FRAME_MIN = 0; // 몇 번째부터 할 지
        RUN_FRAME_MAX = 3; // 몇 번째까지 할 지
        if (cookieState != RUN)
        {
            cookieCurFrame = RUN_FRAME_MIN;
        }
        cookieState = RUN;
        cookieHeight = 250;

    }

    if (GetKeyState('R') & 0x8000) // run_test용
    {
        by = 1; // 두 번째 줄
        RUN_FRAME_MIN = 0; // 몇 번째부터 할 지
        RUN_FRAME_MAX = 3; // 몇 번째까지 할 지
        //cookieCurFrame = RUN_FRAME_MIN;
        cookieHeight = 250;
    }
}