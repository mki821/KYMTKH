#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "Projectile.h"
#include "Lemniscate.h"
#include "InputManager.h"
#include "JHBoss.h"

JHBoss::JHBoss() { }
JHBoss::~JHBoss() { }

void JHBoss::Update() {
	m_timer += fDT;

	if (m_timer >= 0.01f) {
		m_timer = 0.0f;

		Two();
	}

	if (GET_KEY_DOWN(KEY_TYPE::P)) m_scaleUp = true;
}

void JHBoss::One() {
	m_angleModifier += 7;
	int tempModifier = m_angleModifier;

	for (int i = 0; i < 360; i += 60) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 30.0f, 30.0f });
		pProj->SetSpeed(200.0f);
		pProj->SetDir(i + tempModifier);
		pProj->SetLifeTime(5.0f);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void JHBoss::Two() {
	Lemniscate* pProj = new Lemniscate;
	pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
	pProj->SetSize({ 30.0f, 30.0f });
	pProj->SetSpeed(200.0f);
	pProj->SetLifeTime(15.0f);
	pProj->SetOwner(this);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
}

void JHBoss::Render(HDC hdc) {

}
