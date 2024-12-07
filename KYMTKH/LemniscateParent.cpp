#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Lemniscate.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "LemniscateParent.h"

void LemniscateParent::Init() {
	Texture* m_pProjectile20 = GET_RES(L"Projectile_20x35");

	m_createdPos = m_vPos;

	for (int i = 0; i < 1440; i += 12) {
		Lemniscate* pProj = new Lemniscate(i);
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 20.0f, 35.0f });
		pProj->SetSpeed(180.0f);
		pProj->SetRotationSpeed(2.0f);
		pProj->SetTurnSpeed(10.0f * m_turnDirection);
		pProj->SetOwner(this);
		pProj->SetTexture(m_pProjectile20);

		pProj->Init();

		m_vecLemniscates.push_back(pProj);
	}
}

void LemniscateParent::Update() {
	m_timer += fDT;

	float x = std::lerp(m_createdPos.x, m_targetPos.x, m_timer * 0.1f);
	float y = std::lerp(m_createdPos.y, m_targetPos.y, m_timer * 0.1f);

	m_vPos = { x, y };

	m_lifeTimer -= fDT;
	if (m_lifeTimer <= 0.0f) {
		for (Lemniscate* lemniscate : m_vecLemniscates) {
			GET_SINGLE(EventManager)->DeleteObject(lemniscate);
		}
		GET_SINGLE(EventManager)->DeleteObject(this);
	}

	for (Lemniscate* lemniscate : m_vecLemniscates) {
		lemniscate->Update();
	}
}

void LemniscateParent::LateUpdate() {
	Object::LateUpdate();

	for (Lemniscate* lemniscate : m_vecLemniscates) {
		lemniscate->LateUpdate();
	}
}

void LemniscateParent::Render(HDC hdc) {
	for (Lemniscate* lemniscate : m_vecLemniscates) {
		lemniscate->Render(hdc);
	}
}

void LemniscateParent::ComponentRender(HDC hdc) {
	Object::ComponentRender(hdc);

	for (Lemniscate* lemniscate : m_vecLemniscates) {
		lemniscate->ComponentRender(hdc);
	}
}
