#include "pch.h"
#include "GDISelector.h"
#include "Texture.h"
#include "FillImage.h"

void FillImage::Render(HDC hdc) {
	GDISelector a(hdc, BRUSH_TYPE::GREEN);
	float posX = m_vPos.x, posY = m_vPos.y;
	float sizeX = m_vSize.x, sizeY = m_vSize.y;

	if (m_isHorizon) {
		sizeX = std::lerp(0, m_vSize.x, m_fillAmount);
		posX = m_vPos.x + sizeX / 2.0f;
	}
	else {
		sizeY = std::lerp(0, m_vSize.y, m_fillAmount);
		posY = m_vPos.y - sizeY / 2.0f;
	}

	if (m_pTex != nullptr) {
		Vector2 renderPos = { posX - sizeX / 2.0f , posY - sizeY / 2.0f };
		switch (m_eRenderType) {
		case RENDER_TYPE::BitBlt:
			BitBlt(hdc, renderPos.x, renderPos.y, sizeX, sizeY, m_pTex->GetDC(), 0, 0, SRCCOPY);
			break;
		case RENDER_TYPE::TransparentBlt:
			int width = m_pTex->GetWidth();
			int height = m_pTex->GetHeight();
			if (m_isHorizon) width = std::lerp(0, width, m_fillAmount);
			else height = std::lerp(0, height, m_fillAmount);
			TransparentBlt(hdc, renderPos.x, renderPos.y, sizeX, sizeY, m_pTex->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
			break;
		}
	}
	else {
		GDISelector a(hdc, BRUSH_TYPE::RED);
		RECT_RENDER(hdc, posX, posY, sizeX, sizeY);
	}
}
