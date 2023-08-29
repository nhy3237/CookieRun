// CookieRun.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "CookieRun.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// >> : Ani
#pragma comment(lib, "msimg32.lib")

// >> : ��� �� �ٸ�
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

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COOKIERUN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COOKIERUN));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ��Ű
#define timer_ID_1 111
//���
#define timer_ID_2 222
//�ٸ�
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
        // �޴� ������ ���� �м��մϴ�:
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
        by = 1; // �� ��° ��
        RUN_FRAME_MAX = 3; // �� ��°���� �� ��
        RUN_FRAME_MIN = 0; // �� ��°���� �� ��
        cookieCurFrame = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X; // �� x �� ��
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y; // �� y �� ��
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

    { //>> : ���
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

        TransparentBlt(hdc, 0, 0, bitBack.bmWidth * 2, bitBack.bmHeight * 2, hMemDC, 0, 0, bitBack.bmWidth, bitBack.bmHeight, NULL);
        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    { //>> : Ani
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        int xStart = (cookieCurFrame * SPRITE_SIZE_X) + 2; // +2�� ���� �� ����
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

    { // : ���
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);

        TransparentBlt(hMemDC, 0, 0, (bitBack.bmWidth - backCurFrame) * 2, bitBack.bmHeight * 2,
            hMemDC2, backCurFrame, 0, bitBack.bmWidth - backCurFrame, bitBack.bmHeight, NULL);

        TransparentBlt(hMemDC, (bitBack.bmWidth - backCurFrame) * 2, 0, bitBack.bmWidth * 2, bitBack.bmHeight * 2,
            hMemDC2, 0, 0, bitBack.bmWidth, bitBack.bmHeight, NULL);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    { // : �ٸ�
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

        int xStart = (cookieCurFrame * SPRITE_SIZE_X) + 2; // +2�� ���� �� ����
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

    if (GetKeyState('J') & 0x8000) // ����
    {

        by = 0; // ù ��° ��
        RUN_FRAME_MIN = 7; // �� ��°���� �� ��
        RUN_FRAME_MAX = 8; // �� ��°���� �� ��

        if (cookieState != JUMP)
        {
            cookieCurFrame = RUN_FRAME_MIN;
            cntJump = 0;
            cookieHeight = 250;
        }
        cookieState = JUMP;
    }
    else if (GetKeyState('S') & 0x8000) // �����̵�
    {

        by = 0; // ù ��° ��
        RUN_FRAME_MIN = 9; // �� ��°���� �� ��
        RUN_FRAME_MAX = 10; // �� ��°���� �� ��
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
        by = 1; // �� ��° ��
        RUN_FRAME_MIN = 0; // �� ��°���� �� ��
        RUN_FRAME_MAX = 3; // �� ��°���� �� ��
        if (cookieState != RUN)
        {
            cookieCurFrame = RUN_FRAME_MIN;
        }
        cookieState = RUN;
        cookieHeight = 250;

    }

    if (GetKeyState('R') & 0x8000) // run_test��
    {
        by = 1; // �� ��° ��
        RUN_FRAME_MIN = 0; // �� ��°���� �� ��
        RUN_FRAME_MAX = 3; // �� ��°���� �� ��
        //cookieCurFrame = RUN_FRAME_MIN;
        cookieHeight = 250;
    }
}