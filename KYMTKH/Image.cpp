#include "pch.h"
#include "GDISelector.h"
#include "Image.h"

void Image::Init() { }
void Image::Update() { }

void Image::Render(HDC hdc) {
	GDISelector a(hdc, BRUSH_TYPE::RED);
	ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}
