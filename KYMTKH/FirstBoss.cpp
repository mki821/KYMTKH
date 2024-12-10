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
#include "ResourceManager.h"
#include "EventManager.h"

FirstBoss::FirstBoss()
{
	BlueDiamond_10x18 = GET_RES(L"BlueDiamond_10x18");
	BlueProjectile1_25x25 = GET_RES(L"BlueProjectile1_25x25");
	BlueProjectile2_25x25 = GET_RES(L"BlueProjectile2_25x25");
	WhiteDiamod_10x18 = GET_RES(L"WhiteDiamod_10x18");
	WhiteProjectile_20x20 = GET_RES(L"WhiteProjectile_20x20");

	RandomProjTexture_20x20[0] = GET_RES(L"BlueProjectile_20x20");
	RandomProjTexture_20x20[1] = GET_RES(L"GreenProjectile_20x20");
	RandomProjTexture_20x20[2] = GET_RES(L"RedProjectile_20x20");

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
	m_hp = 500;
	m_curPattern = Pattern::First;
	//FirstPattern();
}



void FirstBoss::Update()
{
	Boss::Update();

	if (m_curPattern == Pattern::First && m_hp <= 400) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Second && m_hp <= 300) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Third && m_hp <= 200) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Fourth && m_hp <= 100) {
		ChangePattern();
	}
	else if (m_curPattern == Pattern::Fifth && m_hp <= 0) {
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
		case Pattern::Fifth: FifthPatternUpdate();
			break;
		}
	}
	else {
		m_waitTime -= fDT;
	}
}

void FirstBoss::Render(HDC hdc)
{
	Boss::Render(hdc);
}

void FirstBoss::ChangePattern()
{
	m_waitTime = 3;
	Move(m_originPos, 1.f);
	m_changePatternCount = 0;
	m_firstPattern = true;
	m_curPattern = static_cast<Pattern>(static_cast<int>(m_curPattern) + 1);
	if (m_curPattern == Pattern::Dead) {
		//죽는거
	}
}

Vector2 FirstBoss::GetRandomPos()
{
	int y = rand() % 120 + 80;
	int min = GAME_RIGHT - GAME_LEFT + 35;
	int x = rand() % min + GAME_LEFT;
	return {x, y};
}

Vector2 FirstBoss::GetBossRoundPos(int range)
{
	float x = GetPos().x + ((std::rand() % (range * 200 + 1)) / 100.0f - range);
	float y = GetPos().y + ((std::rand() % (range * 200 + 1)) / 100.0f - range);
	return {x, y};
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
			if (m_timer >= 1.7f) {
				m_timer = 0.0f;
				One();
				m_changePatternCount++;
			}
		}
		else {
			if (m_timer >= 2.5f) {
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
		if (m_timer >= 0.8f) {
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
	if (m_timer >= 9.f) {
		m_timer = 0;
		Three();
	}
}
void FirstBoss::ThirdPatternUpdate()
{
	m_timer += fDT;
	if (m_changePatternCount < 20) {
		if (m_timer >= 0.25f) {
			m_timer = 0;
			Move(GetRandomPos(), 2.f);
			m_changePatternCount++;
			CircleShot(12, 360);
		}
	}
	else {
		if (m_timer >= 1.2f) {
			m_timer = 0.0f;
			Four();
			Move(GetRandomPos(), 1.8f);
			m_changePatternCount++;
			if (m_changePatternCount >= 23) {
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
	if (m_timer >= 15.f) {
		m_timer = 0;
		Five();
	}
}
void FirstBoss::FourthPattern()
{
	Five();
}
void FirstBoss::FifthPatternUpdate()
{
	m_timer += fDT;
	if (m_timer >= 0.25f) {
		m_timer = 0;
		CircleRandomShot(30, GetBossRoundPos(30));
		Move(GetRandomPos(), 2.5f);
	}
}
void FirstBoss::One()
{
	CircleShot(9, 220);
	CircleShot(11, 250);
	int bulletCount = 4;
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	SpreadShot(bulletCount++, dir, 230);
	Wait(0.15f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 230));
	Wait(0.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 230));
	Wait(0.45f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 230));
	Wait(0.6f, std::bind(&FirstBoss::SpreadShot, this, bulletCount++, dir, 230));
}
void FirstBoss::Two()
{
	CircleShot(11, 200);
	CircleShot(12, 180);
	Move(GetRandomPos(), 1.f);
	Wait(0.2f, std::bind(&FirstBoss::StopAndChaseShot, this, 4));
	Wait(1.f, std::bind(&FirstBoss::CircleShot, this, 11, 200)); 
	Wait(1.1f, std::bind(&FirstBoss::CircleShot, this, 12, 180));
}
void FirstBoss::Three()
{
	StopAndRandomMoveShot(1.5, 280);
	Wait(0.4f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(0.8f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(1.2f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(1.6f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(2.f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(2.4f, std::bind(&FirstBoss::StopAndRandomMoveShot, this, 1.5, 240));
	Wait(2.5f, std::bind(&FirstBoss::Move, this, GetRandomPos(), 5.f));
}
void FirstBoss::Four()
{
	CircleShot(12, 300);
	CircleShot(8, 320);
}
void FirstBoss::Five()
{
	RandomMoveShot(370);
	Wait(3.5f, std::bind(&FirstBoss::Move, this, GetRandomPos(), 1.f));
	Wait(3.75f, std::bind(&FirstBoss::FiveShot, this));
}
void FirstBoss::Six()
{
	int bulletCount = 6;
	Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
	dir.Normalize();
	SpreadShot(bulletCount, dir, 280);
	Wait(0.1f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.2f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.4f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.5f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.6f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.7f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.8f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(0.9f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(1.f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(1.1f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(1.2f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
	Wait(1.3f, std::bind(&FirstBoss::SpreadShot, this, bulletCount, dir, 280));
}

void FirstBoss::StopAndRandomMoveShot(float time, float speed)
{
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 360; i += 25) {
			float rad = i * Deg2Rad;
			StopAndRandomMoveProj* pProj = new StopAndRandomMoveProj;
			pProj->SetTexture(BlueDiamond_10x18);
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
		pProj->SetTexture(WhiteDiamod_10x18);
		//StopAndChaseProj에만 있는 세팅
		pProj->SetOwner(this);
		pProj->SetDirChangeTime(0.8f);
		pProj->SetChangeSpeed(470);

		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.0f, 18.0f });
		pProj->SetSpeed(700);
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
		pProj->SetTexture(BlueProjectile1_25x25);

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
		pProj->SetTexture(BlueDiamond_10x18);
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
	manager->SetTexture(RandomProjTexture_20x20[0], 0);
	manager->SetTexture(RandomProjTexture_20x20[1], 1);
	manager->SetTexture(RandomProjTexture_20x20[2], 2);
	manager->SetWhiteTexture(WhiteProjectile_20x20);
	manager->SetOwner(this);
	manager->Spawn(count);
	Wait(3.f, std::bind(&RandomMoveProjManager::Stop, manager));
	Wait(7.5f, std::bind(&RandomMoveProjManager::Remove, manager));
	Wait(16.f, std::bind(&RandomMoveProjManager::Delete, manager));
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
			pProj->SetTexture(BlueProjectile1_25x25);
			pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
			pProj->SetSize({ 25.0f, 25.0f });
			pProj->SetSpeed(400 - j * 15);
			pProj->SetDir({ cos(rad), -sin(rad) });
			pProj->SetLifeTime(5.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	}
}

void FirstBoss::CircleRandomShot(int count, Vector2 pos)
{
	std::random_device rd; 
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> dist(0.0f, 360.0f); 

	for (int i = 0; i < count; ++i) {
		
		float randomAngle = dist(eng);
		float rad = randomAngle * Deg2Rad;

		Projectile* pProj = new Projectile;
		pProj->SetTexture(BlueDiamond_10x18);
		pProj->SetPos({ pos.x, pos.y });
		pProj->SetSize({ 10.0f, 18.0f });
		pProj->SetSpeed(200);
		pProj->SetDir({ cos(rad), sin(rad) });
		pProj->SetLifeTime(5.0f);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}







