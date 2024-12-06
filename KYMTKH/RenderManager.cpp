#include "pch.h"
#include "Core.h"
#include "RenderManager.h"

RenderManager::~RenderManager() {
	DeleteObject(m_hBrush);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hDC);
}

void RenderManager::Init() {
	width = GAME_RIGHT - GAME_LEFT;

	m_hDC = CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
	m_hBitmap = CreateCompatibleBitmap(GET_SINGLE(Core)->GetMainDC(), width, SCREEN_HEIGHT);
	SelectObject(m_hDC, m_hBitmap);

	m_hBrush = CreateSolidBrush(RGB(255, 0, 255));
}

void RenderManager::BeforeRender() {
	RECT rt = { 0, 0, width, SCREEN_HEIGHT };
	FillRect(m_hDC, &rt, m_hBrush);
}

void RenderManager::Render(HDC hdc) {
	TransparentBlt(hdc, GAME_LEFT, 0, width, SCREEN_HEIGHT,
		m_hDC, 0, 0, width, SCREEN_HEIGHT, RGB(255, 0, 255));
}
