#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "Projectile.h"
#include "LemniscateParent.h"
#include "InputManager.h"
#include "Player.h"
#include "JHBoss.h"

JHBoss::JHBoss() { }
JHBoss::~JHBoss() { }

void JHBoss::Init() {
	Two();
}

void JHBoss::Update() {
	Boss::Update();

	m_timer += fDT;

	if (m_timer >= 0.05f) {
		m_timer = 0.0f;

		One();
	}
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
	LemniscateParent* pLemniscate = new LemniscateParent;
	pLemniscate->SetPos(m_vPos);
	pLemniscate->SetTurnDirection(-1);
	pLemniscate->SetTargetPos({ SCREEN_WIDTH / 4.0f, 1300.0f });
	pLemniscate->SetLifeTime(15.0f);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);

	Wait(5.5f, [=]() {
		LemniscateParent* pLemniscate = new LemniscateParent;
		pLemniscate->SetPos(m_vPos);
		pLemniscate->SetTargetPos({ SCREEN_WIDTH - SCREEN_WIDTH / 4.0f, 1300.0f });
		pLemniscate->SetLifeTime(15.0f);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
	});
	Wait(11.0f, [=]() {
		LemniscateParent* pLemniscate = new LemniscateParent;
		pLemniscate->SetPos(m_vPos);
		pLemniscate->SetTurnDirection(-1);
		pLemniscate->SetTargetPos({ SCREEN_WIDTH / 4.0f, 1300.0f });
		pLemniscate->SetLifeTime(15.0f);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
	});
	Wait(16.5f, [=]() {
		LemniscateParent* pLemniscate = new LemniscateParent;
		pLemniscate->SetPos(m_vPos);
		pLemniscate->SetTargetPos({ SCREEN_WIDTH - SCREEN_WIDTH / 4.0f, 1300.0f });
		pLemniscate->SetLifeTime(15.0f);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
	});
}

void JHBoss::Three() {
	Vector2 playerPos = m_player->GetPos();
	Vector2 direction = playerPos - m_vPos;
}

void JHBoss::Render(HDC hdc) {

}
