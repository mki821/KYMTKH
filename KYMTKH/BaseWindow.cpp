#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"

BaseWindow::BaseWindow() : m_hWnd(nullptr), m_hInst(nullptr) { }
BaseWindow::~BaseWindow() { }

int BaseWindow::Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _CmdShow) {
    this->m_hInst = _hInst;
    this->MyRegisterClass();
    this->createWindow();
    this->showWindow(_CmdShow);
    this->updateWindow();
    if (!GET_SINGLE(Core)->Init(m_hWnd))
        MessageBox(m_hWnd, L"Core Init Error!", L"Error", MB_OK);
    return this->MessageLoop();
}

LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM BaseWindow::MyRegisterClass() {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BaseWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_KYMTKH));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"KYMTKH";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::createWindow() {
    int ResolutionX = GetSystemMetrics(SM_CXSCREEN);
    int ResolutionY = GetSystemMetrics(SM_CYSCREEN);

    int Winposx = ResolutionX / 2 - SCREEN_WIDTH / 2;
    int Winposy = ResolutionY / 2 - SCREEN_HEIGHT / 2;

    m_hWnd = CreateWindowW(
        L"KYMTKH",          // 윈도우 클래스 식별자
        L"KYMTKH",       // 제목
        WS_SYSMENU,            // 윈도우 어떤 스타일로 만들것인가
        Winposx,               // ★ 띄울 위치의 LEFT
        Winposy,               // ★ 띄울 위치의 TOP
        SCREEN_WIDTH,          // ★ 해상도X
        SCREEN_HEIGHT,         // ★ 해상도Y
        nullptr,               // 부모 윈도우 어쩌구라서 무시
        nullptr,               // 메뉴쓸꺼냐
        m_hInst,               // 내 프로그램 인스턴스 값
        nullptr);              // 자식 윈도우 관련된것 무시


    // 윈도우 사이즈 조정(타이틀, 메뉴 계산하지 않도록)
    RECT rt = { Winposx , Winposy,
                 Winposx + SCREEN_WIDTH,
                 Winposy + SCREEN_HEIGHT };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(m_hWnd, Winposx, Winposy,
        rt.right - rt.left, rt.bottom - rt.top, false);
}

void BaseWindow::showWindow(int _CmdShow) {
    ::ShowWindow(m_hWnd, _CmdShow);
}

void BaseWindow::updateWindow() {
    UpdateWindow(m_hWnd); // WM_PAINT
}

int BaseWindow::MessageLoop() {
    MSG msg;
    memset(&msg, 0, sizeof(msg));

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            GET_SINGLE(Core)->GameLoop();
        }
    }

    GET_SINGLE(Core)->CleanUp();
    return (int)msg.wParam;
}
