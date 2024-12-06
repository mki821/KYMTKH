#include "pch.h"
#include "GDISelector.h"
#include "Texture.h"
#include "Image.h"

void Image::Init() { }
void Image::Update() { }

void Image::Render(HDC hdc) {
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
		GDISelector a(hdc, BRUSH_TYPE::RED);
		RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
	}
}
