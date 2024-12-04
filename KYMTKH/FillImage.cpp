#include "pch.h"
#include "GDISelector.h"
#include "FillImage.h"

void FillImage::Render(HDC hdc) {
	GDISelector a(hdc, BRUSH_TYPE::GREEN);
	if (m_isHorizon) {
		float sizeX = std::lerp(0, m_vSize.x, m_fillAmount);
		float posX = m_vPos.x + sizeX / 2.0f;
		RECT_RENDER(hdc, posX, m_vPos.y, sizeX, m_vSize.y);
	}
	else {
		float sizeY = std::lerp(0, m_vSize.y, m_fillAmount);
		float posY = m_vPos.y - sizeY / 2.0f;
		RECT_RENDER(hdc, m_vPos.x, posY, m_vSize.x, sizeY);
	}
}
