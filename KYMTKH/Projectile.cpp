#include "pch.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Projectile.h"

Projectile::Projectile() : m_speed(500.0f) {
	m_vSize = { 50.0f, 50.0f };

	AddComponent<Collider>();
}

Projectile::~Projectile() { }

void Projectile::Update() {
	m_vPos += m_vDir * m_speed * fDT;
}

void Projectile::Render(HDC hdc) {
	ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}
