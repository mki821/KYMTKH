#include "pch.h"
#include "InputManager.h"
#include "Texture.h"
#include "GDISelector.h"
#include "Button.h"

void Button::Init() {

}

void Button::Update() {
	if (GET_KEY_DOWN(KEY_TYPE::LBUTTON)) {
		Vector2 mousePos = GET_MOUSEPOS;
		RECT rt = { m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2, m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2 };
		
		if (PtInRect(&rt, POINT(mousePos.x, mousePos.y))) {
			event();
		}
	}
}

void Button::Render(HDC hdc) {
	if (m_pTex != nullptr) {
		Vector2 renderPos = { m_vPos.x - m_vSize.x / 2.0f , m_vPos.y - m_vSize.y / 2.0f };
		switch (m_eRenderType) {
		case RENDER_TYPE::BitBlt:
			BitBlt(hdc, renderPos.x, renderPos.y, m_vSize.x, m_vSize.y, m_pTex->GetDC(), 0, 0, SRCCOPY);
			break;
		case RENDER_TYPE::TransparentBlt:
			int width = m_pTex->GetWidth();
			int height = m_pTex->GetHeight();
			TransparentBlt(hdc, renderPos.x, renderPos.y, m_vSize.x, m_vSize.y, m_pTex->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
			break;
		}
	}
	else {
		GDISelector a(hdc, BRUSH_TYPE::BLUE);
		RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
	}
}
