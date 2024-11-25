#include "pch.h"
#include "CircleCollider.h"
#include "Boss.h"

Boss::Boss() {
	m_hp = 10;

	AddComponent<CircleCollider>();
}

Boss::~Boss() { }
void Boss::Update() { }

void Boss::Render(HDC hdc) {
	if(!m_isDie) RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Boss::EnterCollision(Collider* other) {
	--m_hp;

	if (m_hp <= 0)
		SetDead();
}
