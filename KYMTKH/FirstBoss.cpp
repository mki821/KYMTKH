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


	/*if (m_timer > 0.3f && !isStop) {
		//m_timer = 0;
		if (bulletCount > 8) {
			isStop = true;
			bulletCount = 4;
		}
		else if (bulletCount <= 5) {
			CircleShot(bulletCount + 4);
			SpreadShot(bulletCount++);
		}
		else {
			SpreadShot(bulletCount++);
		}
	}*/

	if (GET_KEY_DOWN(KEY_TYPE::P)) isStop = false;

}

void FirstBoss::Render(HDC hdc)
{
}

void FirstBoss::One()
{
	CircleShot(9);
	CircleShot(9);
}

void FirstBoss::CircleShot(int shotDeg)
{
	for (int i = 0; i < 360; i += shotDeg) {
		float rad = i * Deg2Rad;
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 35.0f, 35.0f });
		pProj->SetSpeed(200);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void FirstBoss::SpreadShot(int count)
{
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	
	float maxSpreadAngle =30.0f; 
	float angleStep = maxSpreadAngle / (count - 1); 
	float startAngle = -maxSpreadAngle / 2.0f;   

	for (int i = 0; i < count; i++) {
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


