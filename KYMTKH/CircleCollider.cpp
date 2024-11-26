#include "pch.h"
#include "Object.h"
#include "GDISelector.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider() : Collider() { }
CircleCollider::~CircleCollider() { }

void CircleCollider::LateUpdate() {
	Collider::LateUpdate();
}

void CircleCollider::Render(HDC hdc) {
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_showDebug) ePen = PEN_TYPE::RED;
	GDISelector pen(hdc, ePen);
	GDISelector brush(hdc, BRUSH_TYPE::HOLLOW);
	ELLIPSE_RENDER(hdc, m_vLateUpdatedPos.x, m_vLateUpdatedPos.y, m_vSize.x, m_vSize.y);
}
