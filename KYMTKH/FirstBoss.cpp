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
#include "StopAndRandomMoveProj.h"
#include "RandomMoveProj.h"
#include "InputManager.h"
#include "RandomMoveProjManager.h"

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
	if (GET_KEY_DOWN(KEY_TYPE::Q)) {
		FiveShot();
	}
	/*if (GET_KEY_DOWN(KEY_TYPE::E)) {
		for (int i = 0; i < m_projVec.size(); i++) {
			m_projVec[i]->SetStop(true);
		}
	}
	if (GET_KEY_DOWN(KEY_TYPE::R)) {
		for (int i = 0; i < m_projVec.size(); i++) {
			m_projVec[i]->SetRemove(true);
		}
	}*/
}

void FirstBoss::Render(HDC hdc)
{
}

void FirstBoss::One()
{
	int bulletCount = 4;
	CircleShot(8, 300);
	CircleShot(10, 350);

	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	SpreadShot(bulletCount++, dir);
	Wait(0.15f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir));
	Wait(0.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir));
	Wait(0.45f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir));
	Wait(0.6f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir));
}

void FirstBoss::Two()
{
	CircleShot(8, 210);
	CircleShot(9, 190);
	StopAndChaseShot(9);
}

void FirstBoss::Three()
{
	StopAndRandomMoveShot(1.5, 280);
	Wait(0.3f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(0.6f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(0.9f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(1.2f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(1.5f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(1.8f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
	Wait(2.1f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 280));
}

void FirstBoss::Four()
{
	RandomMoveShot(200);
}

void FirstBoss::StopAndRandomMoveShot(float time, float speed)
{
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 360; i += 25) {
			float rad = i * Deg2Rad;
			StopAndRandomMoveProj* pProj = new StopAndRandomMoveProj;
			pProj->SetDirChangeTime(time);
			pProj->SetChangeSpeed(150);

			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(speed - j * 30);
			pProj->SetDir({ cos(rad), sin(rad) });
			pProj->SetLifeTime(15.0f);
			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
	
}

void FirstBoss::StopAndChaseShot(int shotDeg) // 9 
{
	for (int i = 0; i < 360; i += shotDeg) {
		float rad = i * Deg2Rad;
		StopAndChaseProj* pProj = new StopAndChaseProj;
		//StopAndChaseProj에만 있는 세팅
		pProj->SetOwner(this);
		pProj->SetDirChangeTime(0.8f);
		pProj->SetChangeSpeed(450);

		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(500);
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
		pProj->SetSize({ 25.0f, 25.0f });
		pProj->SetSpeed(speed);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void FirstBoss::SpreadShot(int count, Vector2 dir)
{
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
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(400);
		pProj->SetDir({ rotatedX, rotatedY });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void FirstBoss::RandomMoveShot(int count)
{
	RandomMoveProjManager* manager = new RandomMoveProjManager;
	manager->SetOwner(this);
	manager->Spawn(count);
	Wait(2.f, std::bind(&RandomMoveProjManager::Stop, manager));
	Wait(6.f, std::bind(&RandomMoveProjManager::Remove, manager));
	Wait(8.f, std::bind(&RandomMoveProjManager::Delete, manager));
}

void FirstBoss::FiveShot()
{
	float centerDeg = 270.0f; 
	int numShots = 5;        
	float angleSpread = 30.0f; 

	float startAngle = centerDeg - (angleSpread / 2.0f); 
	float step = angleSpread / (numShots - 1);          

	for (int i = 0; i < numShots; ++i) {
		for (int j = 0; j < 15; j++) {
			float angle = startAngle + (i * step);
			float rad = angle * Deg2Rad;

			Projectile* pProj = new Projectile;
			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 25.0f, 25.0f });
			pProj->SetSpeed(400- j* 15);
			pProj->SetDir({ cos(rad), -sin(rad)});
			pProj->SetLifeTime(5.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
}





