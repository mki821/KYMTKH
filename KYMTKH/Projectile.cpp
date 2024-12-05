#include "pch.h"
#include "TimeManager.h"
#include "CircleCollider.h"
#include "EventManager.h"
#include "Texture.h"
#include "Projectile.h"

Projectile::Projectile() : m_speed(500.0f) {
	AddComponent<CircleCollider>();
}

Projectile::~Projectile() { }

void Projectile::Init() {
	GetComponent<CircleCollider>()->SetSize(m_vSize);
}

void Projectile::Update() {
	m_vPos += m_vDir * m_speed * fDT;

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC hdc) {
	if (m_pTex != nullptr) {
		Vector2 renderPos = { m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2 };
		TransparentBlt(hdc, renderPos.x, renderPos.y, m_vSize.x, m_vSize.y, m_pTex->GetDC(), 0, 0, m_vSize.x, m_vSize.y, RGB(255, 0, 255));
	}
	else ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Projectile::EnterCollision(Collider* other) 
{
	GET_SINGLE(EventManager)->DeleteObject(this);
}
