#include "pch.h"
#include "Texture.h"
#include "Background.h"

void Background::Render(HDC hdc) {
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	StretchBlt(hdc, GAME_LEFT, 0, GAME_RIGHT - GAME_LEFT, SCREEN_HEIGHT, m_pTex->GetDC(), 0, 0, width, height, SRCCOPY);
}
