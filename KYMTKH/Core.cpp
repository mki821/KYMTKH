#include "pch.h"
#include "Core.h"
#include "GDISelector.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "EventManager.h"

bool Core::Init(HWND _hWnd) {
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	m_hBackDC = 0;
	m_hBackBit = 0;

	m_hBackBit = CreateCompatibleBitmap(m_hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_hBackDC = CreateCompatibleDC(m_hDC);

	SelectObject(m_hBackDC, m_hBackBit);

	srand((unsigned int)time(NULL));

	CreateGDI();

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init();
	GET_SINGLE(ResourceManager)->Init();
	GET_SINGLE(RenderManager)->Init();
	GET_SINGLE(SceneManager)->Init();

	return true;
}

void Core::GameLoop() {
	MainUpdate();
	MainRender();
	GET_SINGLE(EventManager)->Update();
}

void Core::CleanUp() {
	DeleteDC(m_hBackDC);
	DeleteObject(m_hBackBit);
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
		DeleteObject(m_colorPens[i]);

	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
		DeleteObject(m_colorBrushs[i]);

	GET_SINGLE(ResourceManager)->Release();
}

void Core::MainUpdate() {
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(UIManager)->Update();
}

void Core::MainRender() {

	PatBlt(m_hBackDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);

	GET_SINGLE(RenderManager)->BeforeRender();
	GET_SINGLE(SceneManager)->Render(m_hBackDC);
	GET_SINGLE(RenderManager)->Render(m_hBackDC);
	GET_SINGLE(UIManager)->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hBackDC, 0, 0, SRCCOPY);
}

void Core::CreateGDI() {
	// HOLLOW
	m_colorBrushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_colorBrushs[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_colorBrushs[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_colorBrushs[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_colorBrushs[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	m_colorBrushs[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)CreateSolidBrush(BLACK_BRUSH);

	//RED GREEN BLUE PEN
	m_colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	m_colorPens[(UINT)PEN_TYPE::BLACK_THICK] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
}
