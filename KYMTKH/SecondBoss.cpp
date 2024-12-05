#include "pch.h"
#include "SecondBoss.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Player.h"
#include "Y_TestScene.h"
#include "StopAndChaseProj.h"
#include "StopAndRandomMoveProj.h"
#include "RandomMoveProj.h"
#include "InputManager.h"
#include "RandomMoveProjManager.h"
#include "DownProj.h"
#include "ReturnProj.h"

SecondBoss::SecondBoss()
{
	auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
	auto yTestScene = std::dynamic_pointer_cast<Y_TestScene>(curScene);
	m_player = yTestScene->GetPlayer();
}

SecondBoss::~SecondBoss()
{
}

void SecondBoss::Init()
{
	m_originPos = GetPos();
	m_curPattern = Pattern::Fourth;
}

void SecondBoss::Update()
{
	Boss::Update();


	if (GET_KEY_DOWN(KEY_TYPE::Q)) {
		//ChangePattern();
	}

	switch (m_curPattern) {
	case Pattern::First: FirstPatternUpdate(); break;
	case Pattern::Second: SecondPatternUpdate();
		break;
	case Pattern::Third: ThirdPatternUpdate();
		break;
		case Pattern::Fourth: FourthPatternUpdate();
		/*case Pattern::Fifth: FifthPatternUpdate();
			break;*/
	}
}

void SecondBoss::Render(HDC hdc)
{
}

void SecondBoss::ChangePattern()
{
	Move(m_originPos, 1.f);
	m_changePatternCount = 0;
	m_firstPattern = true;
	m_curPattern = static_cast<Pattern>(static_cast<int>(m_curPattern) + 1);
	if (m_curPattern == Pattern::Dead) {
		//�״°�
	}
}

Vector2 SecondBoss::GetRandomPos()
{
	int y = rand() % 190 + 15;
	int min = GAME_RIGHT - GAME_LEFT - 10;
	int x = rand() % min + GAME_LEFT + 10;
	return { x, y };
}

void SecondBoss::FirstPatternUpdate()
{
	m_timer += fDT;
	if (!m_stop) {
		if (m_firstPattenAngle <= 240) {
			if (m_timer >= 0.075f) {
				m_timer = 0.0f;
				CircleRotateShot(m_firstPattenAngle += 3);
			}
		}
		else {
			if (m_timer >= 0.1f) {
				One();
				m_firstPattenAngle = 0;
				m_timer = 0;
				m_stop = true;
				m_turn = !m_turn;
			}
		}
	}
	else {
		if (m_timer >= 2.f) {
			m_stop = false;
		}
	}

}

void SecondBoss::SecondPatternUpdate()
{
	m_timer += fDT;
	if (m_timer >= 0.09f) {
		m_timer = 0.0f;
		FiveCircleRotateShot((m_firstPattenAngle += 3) % 360);
		if (m_firstPattenAngle >= 360) {
			m_turn = !m_turn;
			m_firstPattenAngle = 0;
		}
	}
}

void SecondBoss::ThirdPatternUpdate()
{
	m_timer += fDT;
	if (m_timer >= 4.1f) {
		m_timer = 0.0f;
		Two();
	}
}

void SecondBoss::FourthPatternUpdate()
{
	m_timer += fDT;
	if (m_timer >= 5.f) {
		m_timer = 0.0f;
		CircleReturnShot(50);
	}
}

void SecondBoss::One()
{
	Move(GetRandomPos(), 1.f);
	CircleRandomShot(30);
	Wait(0.15f, std::bind(&SecondBoss::CircleRandomShot, this, 30));
	Wait(0.3f, std::bind(&SecondBoss::CircleRandomShot, this, 30));
	Wait(0.45f, std::bind(&SecondBoss::CircleRandomShot, this, 30));
	Wait(0.6f, std::bind(&SecondBoss::CircleRandomShot, this, 30));
}

void SecondBoss::Two()
{
	DownShot(10);
	Wait(0.15f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(0.3f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(0.45f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(0.6f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(0.75f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(0.9f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.05f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.2f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.35f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.5f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.65f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.8f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(1.95f, std::bind(&SecondBoss::DownShot, this, 12));
	Wait(2.f, std::bind(&SecondBoss::Move, this,GetRandomPos(), 2.f));
}

void SecondBoss::CircleRotateShot(int baseAngle)
{
	int numBullets = 5;
	float angleStep = 360.0f / numBullets;

	for (int i = 0; i < numBullets; ++i) {
		float angle = baseAngle + i * angleStep;
		float rad = angle * Deg2Rad;

		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.f, 10.f });
		pProj->SetSpeed(330);
		pProj->SetDir({ cos(rad) * (m_turn ? 1 : -1), sin(rad) });
		pProj->SetLifeTime(5.0f);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void SecondBoss::FiveCircleRotateShot(int baseAngle)
{
	int numBullets = 3;
	float angleStep = 360.0f / numBullets;

	for (int i = 0; i < numBullets; ++i) {
		for (int j = 0; j < 7; j++) {
			float angle = baseAngle + i * angleStep + j * 13;
			float rad = angle * Deg2Rad;

			Projectile* pProj = new Projectile;
			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 8.f, 16.f });
			pProj->SetSpeed(300);
			pProj->SetDir({ cos(rad) * (m_turn ? 1 : -1), sin(rad) });
			pProj->SetLifeTime(5.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
}

void SecondBoss::CircleRandomShot(int count)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> dist(0.0f, 360.0f);

	for (int i = 0; i < count; ++i) {

		float randomAngle = dist(eng);
		float rad = randomAngle * Deg2Rad;

		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(400);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void SecondBoss::DownShot(int count)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> dist(0.0f, 360.0f);

	for (int i = 0; i < count; ++i) {

		float randomAngle = dist(eng);
		float rad = randomAngle * Deg2Rad;

		DownProj* pProj = new DownProj;
		pProj->SetChangeTime(1.f);

		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(100 + rand() % 100);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void SecondBoss::CircleReturnShot(int count)
{
	int numBullets = count;
	float angleStep = 360.0f / numBullets;
	float speed = 300;
	float changeTime = 1.f;

	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 360; i += angleStep) {
			float rad = i * Deg2Rad;
			ReturnProj* pProj = new ReturnProj;
			pProj->SetChangeTime(changeTime + j* 0.2f);
			pProj->SetTarget(m_vPos);
			pProj->SetChangeSpeed(400);
			pProj->SetExitTime(0.6f);

			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 20.0f, 20.0f });
			pProj->SetSpeed(speed - j * 20);
			pProj->SetDir({ cos(rad), sin(rad) });
			pProj->SetLifeTime(15.0f);
			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
}

void SecondBoss::RandomMoveShot(int count)
{
	RandomMoveProjManager* manager = new RandomMoveProjManager;
	manager->SetOwner(this);
	manager->Spawn(count);
	Wait(3.f, std::bind(&RandomMoveProjManager::Stop, manager));
	Wait(6.f, std::bind(&RandomMoveProjManager::Remove, manager));
	Wait(14.f, std::bind(&RandomMoveProjManager::Delete, manager));
}

