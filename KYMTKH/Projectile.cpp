#include "pch.h"
#include "TimeManager.h"
#include "CircleCollider.h"
#include "EventManager.h"
#include "Projectile.h"

Projectile::Projectile() : m_speed(500.0f) {
	m_vSize = { 50.0f, 50.0f };

	AddComponent<CircleCollider>();
}

Projectile::~Projectile() { }

void Projectile::Update() {
	m_vPos += m_vDir * m_speed * fDT;

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC hdc) {
	ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Projectile::EnterCollision(Collider* other) 
{
	GET_SINGLE(EventManager)->DeleteObject(this);
}
