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
#include "ResourceManager.h"
#include "EventManager.h"
#include "SecondBossScene.h"

SecondBoss::SecondBoss()
{
	auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
	auto secondBossScene = std::dynamic_pointer_cast<SecondBossScene>(curScene);
	m_player = secondBossScene->GetPlayer();

	m_RandomTex[0] = GET_RES(L"RedDia_10x18");
	m_RandomTex[1] = GET_RES(L"OrrangeDia_10x18");
	m_RandomTex[2] = GET_RES(L"GreenDia_10x18");
	m_RandomTex[3] = GET_RES(L"BluepleDia_10x18");
	m_RandomTex[4] = GET_RES(L"BlueDiamond_10x18");
	m_RandomTex[5] = GET_RES(L"PurpleDia_10x18");

	m_ShurikanTex[0] = GET_RES(L"BlueShuriken_10x18");
	m_ShurikanTex[1] = GET_RES(L"RedShuriken_10x18");
}

SecondBoss::~SecondBoss()
{
}
	
void SecondBoss::Init()
{
	m_originPos = GetPos();
	m_curPattern = Pattern::First;
	m_hp = 500;
}

void SecondBoss::Update()
{
	Boss::Update();
	if (m_curPattern == Pattern::First && m_hp <= 370) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Second && m_hp <= 250) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Third && m_hp <= 150) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Fourth && m_hp <= 0) {
		ChangePattern();
	}

	/*if (GET_KEY_DOWN(KEY_TYPE::Q)) {
		ChangePattern();
	}*/

	if (m_waitTime <= 0) {
		switch (m_curPattern) {
		case Pattern::First: FirstPatternUpdate(); break;
		case Pattern::Second: SecondPatternUpdate();
			break;
		case Pattern::Third: ThirdPatternUpdate();
			break;
		case Pattern::Fourth: FourthPatternUpdate();
			break;
		}
	}
	else {
		m_waitTime -= fDT;
	}
}

void SecondBoss::Render(HDC hdc)
{
	Boss::Render(hdc);
}

void SecondBoss::ChangePattern()
{
	Move(m_originPos, 1.f);
	m_changePatternCount = 0;
	m_firstPattern = true;
	m_startPattern = false;
	m_curPattern = static_cast<Pattern>(static_cast<int>(m_curPattern) + 1);
	m_waitTime = 3;
	if (m_curPattern == Pattern::Dead) {
		//Á×´Â°Å
	}
}

Vector2 SecondBoss::GetRandomPos()
{
	int y = rand() % 120 + 80;
	int min = GAME_RIGHT - GAME_LEFT + 35;
	int x = rand() % min + GAME_LEFT;
	return { x, y };
}

void SecondBoss::FirstPatternUpdate()
{
	m_timer += fDT;
	if (!m_stop) {
		if (m_firstPattenAngle <= 240) {
			if (m_timer >= 0.09f) {
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
	if (m_timer >= 0.16f) {
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
	if (!m_startPattern) {
		Two();
		m_startPattern = true;
	}
	if (m_timer >= 5.f) {
		m_timer = 0.0f;
		Two();
	}
}

void SecondBoss::FourthPatternUpdate()
{
	m_timer += fDT;
	if (!m_startPattern) {
		Three();
		m_startPattern = true;
	}
	if (m_timer >= 9.f) {
		m_timer = 0.0f;
		Three();
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
	DownShot(8);
	Wait(0.15f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(0.3f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(0.45f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(0.6f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(0.75f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(0.9f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.05f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.2f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.35f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.5f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.65f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.8f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(1.95f, std::bind(&SecondBoss::DownShot, this, 8));
	Wait(2.f, std::bind(&SecondBoss::Move, this, GetRandomPos(), 1.5f));
}

void SecondBoss::Three()
{
	CircleReturnShot(28, 1.4f, 0);
	Wait(1.f, std::bind(&SecondBoss::CircleReturnShot, this, 28, 1.f, 1));
	Wait(5.5f, std::bind(&SecondBoss::Move, this, GetRandomPos(), 1.f));
}

void SecondBoss::CircleRotateShot(int baseAngle)
{
	int numBullets = 5;
	float angleStep = 360.0f / numBullets;

	for (int i = 0; i < numBullets; ++i) {
		float angle = baseAngle + i * angleStep;
		float rad = angle * Deg2Rad;

		Projectile* pProj = new Projectile;
		pProj->SetTexture(m_RandomTex[0]);
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.f, 18.f });
		pProj->SetSpeed(350);
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
		for (int j = 0; j < 6; j++) {
			float angle = baseAngle + i * angleStep + j * 13;
			float rad = angle * Deg2Rad;

			Projectile* pProj = new Projectile;
			pProj->SetTexture(m_RandomTex[j]);
			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 10.f, 18.f });
			pProj->SetSpeed(280);
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
		pProj->SetTexture(m_RandomTex[0]);
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
		pProj->SetTexture(m_RandomTex[rand() % 6]);
		pProj->SetChangeTime(1.7f);

		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(100 + rand() % 100);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void SecondBoss::CircleReturnShot(int count, float exitTime, int k)
{
	int numBullets = count;
	float angleStep = 360.0f / numBullets;
	float speed = 370;
	float changeTime = 1.f;

	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 360; i += angleStep) {
			float rad = i * Deg2Rad;
			ReturnProj* pProj = new ReturnProj;
			pProj->SetTexture(m_ShurikanTex[k]);
			pProj->SetChangeTime(changeTime);
			pProj->SetTarget(m_vPos);
			pProj->SetChangeSpeed(300);
			pProj->SetExitTime(exitTime - j * 0.1f);

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

