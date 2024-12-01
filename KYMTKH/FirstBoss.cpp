#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "Projectile.h"
#include "InputManager.h"
#include "FirstBoss.h"
#include "Player.h"
#include "Y_TestScene.h"
#include "StopAndChaseProj.h"

FirstBoss::FirstBoss()
{
	auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
	auto yTestScene = std::dynamic_pointer_cast<Y_TestScene>(curScene);
	m_player = yTestScene->GetPlayer();
}

FirstBoss::~FirstBoss()
{
}

void FirstBoss::Update()
{
	Boss::Update();

	m_timer += fDT;
	if (m_timer > 3) {
		m_timer = 0;
	}
}

void FirstBoss::Render(HDC hdc)
{
}

void FirstBoss::One()
{
	int bulletCount = 4;
	CircleShot(9, 200);
	CircleShot(10, 250);
	SpreadShot(bulletCount++);
}

void FirstBoss::StopAndChaseShot(int shotDeg, float speed) // 12 500
{
	for (int i = 0; i < 360; i += shotDeg) {
		float rad = i * Deg2Rad;
		StopAndChaseProj* pProj = new StopAndChaseProj;
		//StopAndChaseProj에만 있는 세팅
		pProj->SetOwner(this);
		pProj->SetDirChangeTime(1.f);
		pProj->SetChangeSpeed(speed);

		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 25.0f, 25.0f });
		pProj->SetSpeed(600);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(8.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void FirstBoss::CircleShot(int shotDeg, float speed)
{
	for (int i = 0; i < 360; i += shotDeg) {
		float rad = i * Deg2Rad;
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 35.0f, 35.0f });
		pProj->SetSpeed(speed);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void FirstBoss::SpreadShot(int count)
{
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();

	float maxSpreadAngle = 30.0f;
	float angleStep = maxSpreadAngle / (count - 1);
	float startAngle = -maxSpreadAngle / 2.0f;

	for (int i = 0; i < count;i++) {
		float angle = startAngle + i * angleStep;
		float rad = angle * Deg2Rad;
		float rotatedX = dir.x * cos(rad) - dir.y * sin(rad);
		float rotatedY = dir.x * sin(rad) + dir.y * cos(rad);

		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 20.0f, 20.0f });
		pProj->SetSpeed(350);
		pProj->SetDir({ rotatedX, rotatedY });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}


