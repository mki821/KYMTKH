#include "pch.h"
#include "CircleCollider.h"
#include "TImeManager.h"
#include "UIManager.h"
#include "FillImage.h"
#include "Boss.h"

Boss::Boss() {
	m_hp = 10;

	AddComponent<CircleCollider>();
}

Boss::~Boss() { }

void Boss::Update() {
	Object::Update();

	if (m_isMove) {
		m_moveTimer += fDT;

		float x = std::lerp(m_moveStartPos.x, m_targetPos.x, m_moveTimer / m_moveTime);
		float y = std::lerp(m_moveStartPos.y, m_targetPos.y, m_moveTimer / m_moveTime);

		m_vPos = { x, y };

		if (m_moveTimer >= m_moveTime) {
			m_isMove = false;
			m_vPos = m_targetPos;
		}
	}
}

void Boss::Render(HDC hdc) {
	if (!m_isDie) {
		RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
		ELLIPSE_RENDER(hdc, m_vPos.x, SCREEN_HEIGHT, 7.0f, 7.0f);
	}
}

void Boss::EnterCollision(Collider* other) {
	--m_hp;

	FillImage* healthbar = dynamic_cast<FillImage*>(GET_SINGLE(UIManager)->GetUI(L"BossHealth"));
	if(healthbar != nullptr)
		healthbar->SetFillAmount(m_hp / 800.0f);

	if (m_hp <= 0)
		SetDead();
}

void Boss::Move(Vector2 targetPos, float time) {
	if (m_isMove) return;

	m_moveStartPos = m_vPos;
	m_targetPos = targetPos;
	m_moveTime = time;
	m_moveTimer = 0.0f;

	m_isMove = true;
}
