#include "pch.h"
#include "Object.h"
#include "GDISelector.h"
#include "Collider.h"

Collider::Collider() : m_vSize(30.0f, 30.0f), m_vOffset(0.0f, 0.0f), m_vLateUpdatedPos(0.0f, 0.0f) { }

Collider::~Collider() { }

void Collider::LateUpdate() {
	const Object* pOwner = GetOwner();
	Vector2 vPos = pOwner->GetPos();
	m_vLateUpdatedPos = vPos + m_vOffset;
}

void Collider::Render(HDC hdc) {
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_showDebug) ePen = PEN_TYPE::RED;
	GDISelector pen(hdc, ePen);
	GDISelector brush(hdc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(hdc, m_vLateUpdatedPos.x, m_vLateUpdatedPos.y, m_vSize.x, m_vSize.y);
}

void Collider::EnterCollision(Collider* other) {
	m_showDebug = true;

	m_pOwner->EnterCollision(other);
}

void Collider::StayCollision(Collider* other) {
	m_pOwner->StayCollision(other);
}

void Collider::ExitCollision(Collider* other) {
	m_showDebug = false;

	m_pOwner->ExitCollision(other);
}
