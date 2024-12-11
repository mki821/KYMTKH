#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "Projectile.h"
#include "LemniscateParent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "JHBossH.h"

JHBossH::JHBossH() {
	m_hp = 600;

	m_pProjectile15 = GET_RES(L"Projectile_15x15");
	m_pProjectile10 = GET_RES(L"Projectile_10x10");
}
JHBossH::~JHBossH() {}

void JHBossH::Init() {
	m_timer2 = 6.5f;
	m_eCurPattern = Pattern::First;
}

void JHBossH::Update() {
	Boss::Update();

	if (m_eCurPattern == Pattern::First && m_hp <= 500) {
		GET_SINGLE(SceneManager)->GetCurScene()->DeleteEnemyProjectiles();

		m_eCurPattern = Pattern::Second;

		Wait(1.0f, [this]() {
			float delay = 5.0f;
			for (int i = 0; i < 3; ++i) {
				Wait(delay * i, [this]() {
					SecondPattern();
					});
			}
		});
	}
	else if (m_eCurPattern == Pattern::Second && m_hp <= 150) {
		GET_SINGLE(SceneManager)->GetCurScene()->DeleteEnemyProjectiles();

		m_eCurPattern = Pattern::Third;
		ThirdPattern();

		Wait(20.0f, [this]() {
			m_eCurPattern = Pattern::Second;
		});
	}

	switch (m_eCurPattern) {
	case Pattern::First: FirstPatternUpdate(); break;
	case Pattern::Third: ThirdPatternUpdate(); break;
	}
}

void JHBossH::Render(HDC hdc) {
	Boss::Render(hdc);
}

#pragma region FirstPattern

void JHBossH::FirstPatternUpdate() {
	m_timer += fDT;
	if (m_timer >= 0.03f) {
		m_timer = 0.0f;
		One();
	}

	m_timer2 += fDT;
	if (m_timer2 >= 7.5) {
		m_timer2 = 0.0f;

		Two();
	}

	m_timer3 += fDT;
	if (m_timer3 >= 0.48f) {
		m_timer3 = 0.0f;

		Three();
	}
}

void JHBossH::One() {
	m_angleModifier += 77;
	int tempModifier = m_angleModifier;

	for (int i = 0; i < 360; i += 60) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.0f, 10.0f });
		pProj->SetSpeed(200.0f);
		pProj->SetDir(i + tempModifier);
		pProj->SetLifeTime(5.0f);
		pProj->SetTexture(m_pProjectile10);

		pProj->GetComponent<CircleCollider>()->SetSize({ 8.0f, 8.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void JHBossH::Two() {
	m_turnDirection *= -1;
	float targetPosX = m_turnDirection == 1 ? SCREEN_WIDTH - SCREEN_WIDTH / 10.0f : SCREEN_WIDTH / 10.0f;

	LemniscateParent* pLemniscate = new LemniscateParent;
	pLemniscate->SetPos(m_vPos);
	pLemniscate->SetTurnDirection(m_turnDirection);
	pLemniscate->SetTargetPos({ targetPosX, SCREEN_HEIGHT * 1.3f });
	pLemniscate->SetLifeTime(15.0f);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
}

void JHBossH::Three() {
	for (int i = 0; i < 360; i += 20) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(100.0f);
		pProj->SetDir(i);
		pProj->SetLifeTime(15.0f);
		pProj->SetTexture(m_pProjectile15);

		pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

#pragma endregion
#pragma region SecondPattern

void JHBossH::SecondPattern() {
	Vector2 firstPos = { m_vPos.x, m_vPos.y - m_vSize.y / 2.0f };
	Wait(0.4f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(firstPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(250.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(0.6f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(firstPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});

	Vector2 secondPos = { SCREEN_WIDTH / 2.0f, 0.0f };
	Wait(0.7f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(secondPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(0.9f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(secondPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(150.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});

	Vector2 thirdPos = { SCREEN_WIDTH / 3.0f, 150.0f };
	Vector2 fourthPos = { SCREEN_WIDTH - SCREEN_WIDTH / 3.0f, 150.0f };
	Wait(1.0f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(thirdPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(1.0f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(fourthPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(1.2f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(thirdPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(150.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(1.2f, [=]() {
		for (int i = 0; i < 360; i += 6) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(fourthPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(150.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});

	Wait(1.3f, [=]() {
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> x(SCREEN_WIDTH / 3.0f, SCREEN_WIDTH - SCREEN_WIDTH / 3.0f);
		std::uniform_int_distribution<int> y(0, SCREEN_HEIGHT / 3.5f);
		Vector2 spawnPos = { x(mt), y(mt) };

		for (int i = 0; i < 360; i += 12) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(spawnPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
	Wait(1.5f, [=]() {
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> x(SCREEN_WIDTH / 3.0f, SCREEN_WIDTH - SCREEN_WIDTH / 3.0f);
		std::uniform_int_distribution<int> y(0, SCREEN_HEIGHT / 3.5f);

		Vector2 spawnPos = { x(mt), y(mt) };

		for (int i = 0; i < 360; i += 12) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(spawnPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(200.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);
			pProj->SetTexture(m_pProjectile15);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});
}

#pragma endregion
#pragma region ThirdPattern

void JHBossH::ThirdPattern() {
	Move({ GAME_LEFT + 80.0f, 250.0f }, 5.0f);
	Wait(6.0f, [this]() {
		Move({ GAME_RIGHT - 80.0f, 280.0f }, 8.0f);
		Wait(9.0f, [this]() {
			Move({ GAME_CENTER, 100.0f }, 3.5f);
			});
		});
}

void JHBossH::ThirdPatternUpdate() {
	m_timer += fDT;
	if (m_timer >= 0.08f) {
		m_timer = 0.0f;

		Four();
	}
}

void JHBossH::Four() {
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randomize(-44.0f, 44.0f);
	for (int i = 45; i < 360; i += 20) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y });
		pProj->SetSize({ 10.0f, 10.0f });
		pProj->SetSpeed(150.0f);
		pProj->SetDir(i + randomize(mt));
		pProj->SetLifeTime(8.0f);
		pProj->SetTexture(m_pProjectile10);

		pProj->GetComponent<CircleCollider>()->SetSize({ 8.0f, 8.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

#pragma endregion