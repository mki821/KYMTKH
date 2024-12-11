#include "pch.h"
#include "CircleCollider.h"
#include "TImeManager.h"
#include "UIManager.h"
#include "FillImage.h"
#include "Texture.h"
#include "EndImage.h"
#include "ResourceManager.h"
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
		if (m_pTex != nullptr) {
			int width = m_pTex->GetWidth();
			int height = m_pTex->GetHeight();
			TransparentBlt(hdc, m_vPos.x - width / 2, m_vPos.y - height, width, height, m_pTex->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
		}
		else {
			RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
		}
		ELLIPSE_RENDER(hdc, m_vPos.x, SCREEN_HEIGHT, 7.0f, 7.0f);
	}
}

void Boss::SetDead() {
	Object::SetDead();

	EndImage* btn = new EndImage;
	btn->SetPos({ SCREEN_WIDTH / 2.0f - 100.0f, SCREEN_HEIGHT / 2.0f });
	btn->SetTexture(GET_RES(L"GameClear"));
	GET_SINGLE(UIManager)->AddUI(L"Button", btn);
}

void Boss::EnterCollision(Collider* other) {
	--m_hp;

	FillImage* healthbar = dynamic_cast<FillImage*>(GET_SINGLE(UIManager)->GetUI(L"BossHealth"));
	if(healthbar != nullptr)
		healthbar->SetFillAmount(m_hp / 600.0f);

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
