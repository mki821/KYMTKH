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

void FirstBoss::Init()
{
	m_originPos = GetPos();
	m_curPattern = Pattern::First;
	//FirstPattern();
}



void FirstBoss::Update()
{
	Boss::Update();


	if (GET_KEY_DOWN(KEY_TYPE::Q)) {
		ChangePattern();
	}

	switch (m_curPattern) {
	case Pattern::First: FirstPatternUpdate(); break;
	case Pattern::Second: SecondPatternUpdate();
		break;
	case Pattern::Third: ThirdPatternUpdate();
		break;
	case Pattern::Fourth: FourthPatternUpdate();
	}
}

void FirstBoss::Render(HDC hdc)
{
}

void FirstBoss::ChangePattern()
{
	Move(m_originPos);
	m_changePatternCount = 0;
	m_firstPattern = true;
	m_curPattern = static_cast<Pattern>(static_cast<int>(m_curPattern) + 1);
	if (m_curPattern == Pattern::Dead) {
		//죽는거
	}
}

void FirstBoss::FirstPattern()
{
	One();
}
void FirstBoss::FirstPatternUpdate()
{
	if (!m_stop) {
		m_timer += fDT;
		if (m_changePatternCount < 3) {
			if (m_timer >= 1.6f) {
				m_timer = 0.0f;
				One();
				m_changePatternCount++;
			}
		}
		else {
			if (m_timer >= 1.6f) {
				m_timer = 0.0f;
				Two();
				m_changePatternCount++;
				if (m_changePatternCount >= 7) {
					m_timer = 0;
					m_changePatternCount = 0;
					m_stop = true;
				}
			}
		}
	}
	else {
		m_timer += fDT;
		if (m_timer >= 0.5f) {
			m_timer = 0;
			m_stop = false;
		}
	}
}
void FirstBoss::SecondPattern()
{
	Three();
}
void FirstBoss::SecondPatternUpdate()
{
	if (m_firstPattern) {
		m_firstPattern = false;
		SecondPattern();
	}
	m_timer += fDT;
	if (m_timer >= 6.f) {
		m_timer = 0;
		Three();
	}
}
void FirstBoss::ThirdPatternUpdate()
{
	m_timer += fDT;
	if (m_changePatternCount < 20) {
		if (m_timer >= 0.2f) {
			m_timer = 0;
			m_changePatternCount++;
			CircleShot(16, 400);
		}
	}
	else {
		if (m_timer >= 0.8f) {
			m_timer = 0.0f;
			Four();
			m_changePatternCount++;
			if (m_changePatternCount >= 24) {
				m_timer = 0;
				m_changePatternCount = 0;
			}
		}
	}
}
void FirstBoss::FourthPatternUpdate()
{
	if (m_firstPattern) {
		m_firstPattern = false;
		FourthPattern();
	}
	m_timer += fDT;
	if (m_timer >= 14.f) {
		m_timer = 0;
		Five();
	}
}
void FirstBoss::FourthPattern()
{
	Five();
}
void FirstBoss::One()
{
	CircleShot(9, 220);
	CircleShot(11, 250);
	int bulletCount = 4;
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	SpreadShot(bulletCount++, dir, 260);
	Wait(0.15f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 260));
	Wait(0.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 260));
	Wait(0.45f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 260));
	Wait(0.6f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 260));
}
void FirstBoss::Two()
{
	CircleShot(9, 200);
	CircleShot(11, 180);
	StopAndChaseShot(8);
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
	CircleShot(12, 250);
	CircleShot(8, 300);
}
void FirstBoss::Five()
{
	RandomMoveShot(350);
	Wait(4.f, std::bind(&FirstBoss::Six, this));
}
void FirstBoss::Six()
{
	int bulletCount = 8;
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	SpreadShot(bulletCount, dir, 300);
	Wait(0.1f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.2f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.4f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.5f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.6f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.7f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.8f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(0.9f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(1.f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(1.1f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));
	Wait(1.2f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 300));

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
			pProj->SetSize({ 10.0f, 18.0f });
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
		pProj->SetSize({ 10.0f, 18.0f });
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

void FirstBoss::SpreadShot(int count, Vector2 dir, float speed)
{
	float maxSpreadAngle = 40.0f;
	float angleStep = maxSpreadAngle / (count - 1);
	float startAngle = -maxSpreadAngle / 2.0f;

	for (int i = 0; i < count; i++) {
		float angle = startAngle + i * angleStep;
		float rad = angle * Deg2Rad;
		float rotatedX = dir.x * cos(rad) - dir.y * sin(rad);
		float rotatedY = dir.x * sin(rad) + dir.y * cos(rad);

		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.0f, 18.0f });
		pProj->SetSpeed(speed);
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
	Wait(3.f, std::bind(&RandomMoveProjManager::Stop, manager));
	Wait(7.5f, std::bind(&RandomMoveProjManager::Remove, manager));
	Wait(15.f, std::bind(&RandomMoveProjManager::Delete, manager));
}

void FirstBoss::FiveShot()
{
	float centerDeg = 270.0f;
	int numShots = 5;
	float angleSpread = 30.0f;

	float startAngle = centerDeg - (angleSpread / 2.0f);
	float step = angleSpread / (numShots - 1);

	for (int i = 0; i < numShots; ++i) {
		for (int j = 0; j < 10; j++) {
			float angle = startAngle + (i * step);
			float rad = angle * Deg2Rad;

			Projectile* pProj = new Projectile;
			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 25.0f, 25.0f });
			pProj->SetSpeed(400 - j * 15);
			pProj->SetDir({ cos(rad), -sin(rad) });
			pProj->SetLifeTime(5.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
}







