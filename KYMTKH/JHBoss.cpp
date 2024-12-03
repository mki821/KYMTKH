#include "pch.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "Projectile.h"
#include "LemniscateParent.h"
#include "InputManager.h"
#include "Player.h"
#include "JHBoss.h"

JHBoss::JHBoss() { }
JHBoss::~JHBoss() { }

void JHBoss::Init() {
	m_eCurPattern = Pattern::Third; 
	ThirdPattern();
	//FirstPattern();
	//Wait(55.0f, [this]() {
	//	m_eCurPattern = Pattern::Second; 

	//	Wait(5.0f, [this]() {
	//		float delay = 5.0f;
	//		for (int i = 1; i <= 3; ++i) {
	//			Wait(delay * i, [this]() {
	//				SecondPattern();
	//			});
	//		}
	//	});
	//});
}

void JHBoss::Update() {
	Boss::Update();

	switch (m_eCurPattern) {
		case Pattern::First: FirstPatternUpdate(); break;
		case Pattern::Third: ThirdPatternUpdate(); break;
	}
}

void JHBoss::Render(HDC hdc) {

}

#pragma region FirstPattern

void JHBoss::FirstPattern() {
	Two();
}

void JHBoss::FirstPatternUpdate() {
	m_timer += fDT;
	if (m_timer >= 0.05f) {
		m_timer = 0.0f;

		One();
	}

	m_timer3 += fDT;
	if (m_timer3 >= 0.35f) {
		m_timer3 = 0.0f;

		Three();
	}
}

void JHBoss::One() {
	m_angleModifier += 7;
	int tempModifier = m_angleModifier;

	for (int i = 0; i < 360; i += 60) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 10.0f, 10.0f });
		pProj->SetSpeed(200.0f);
		pProj->SetDir(i + tempModifier);
		pProj->SetLifeTime(5.0f);

		pProj->GetComponent<CircleCollider>()->SetSize({ 8.0f, 8.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void JHBoss::Two() {
	float delay = 7.5f;
	for (int i = 0; i < 6; i += 2) {
		Wait(delay * i, [=]() {
			LemniscateParent* pLemniscate = new LemniscateParent;
			pLemniscate->SetPos(m_vPos);
			pLemniscate->SetTurnDirection(-1);
			pLemniscate->SetTargetPos({ SCREEN_WIDTH / 4.0f, 1300.0f });
			pLemniscate->SetLifeTime(15.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
		});

		Wait(delay * (i + 1), [=]() {
			LemniscateParent* pLemniscate = new LemniscateParent;
			pLemniscate->SetPos(m_vPos);
			pLemniscate->SetTargetPos({ SCREEN_WIDTH - SCREEN_WIDTH / 4.0f, 1300.0f });
			pLemniscate->SetLifeTime(15.0f);

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pLemniscate, LAYER::ENEMY_PROJECTILE);
		});
	}
}

void JHBoss::Three() {
	for (int i = 0; i < 360; i += 20) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetSpeed(100.0f);
		pProj->SetDir(i);
		pProj->SetLifeTime(15.0f);

		pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

#pragma endregion
#pragma region SecondPattern

void JHBoss::SecondPattern() {
	Vector2 firstPos = { m_vPos.x, m_vPos.y - m_vSize.y / 2.0f };
	Wait(0.4f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(firstPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(0.6f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(firstPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(250.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
		});

	Vector2 secondPos = { SCREEN_WIDTH / 2.0f, 0.0f };
	Wait(0.7f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(secondPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(0.9f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(secondPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(250.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});

	Vector2 thirdPos = { SCREEN_WIDTH / 3.0f, 150.0f };
	Vector2 fourthPos = { SCREEN_WIDTH - SCREEN_WIDTH / 3.0f, 150.0f };
	Wait(1.0f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(thirdPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(1.0f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(fourthPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(1.2f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(thirdPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(250.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(1.2f, [=]() {
		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(fourthPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(250.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});

	Wait(1.1f, [=]() {
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> x(SCREEN_WIDTH / 3.0f, SCREEN_WIDTH - SCREEN_WIDTH / 3.0f);
		std::uniform_int_distribution<int> y(0, SCREEN_HEIGHT / 3.5f);
		Vector2 spawnPos = { x(mt), y(mt)};

		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(spawnPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
	Wait(1.3f, [=]() {
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> x(SCREEN_WIDTH / 3.0f, SCREEN_WIDTH - SCREEN_WIDTH / 3.0f);
		std::uniform_int_distribution<int> y(0, SCREEN_HEIGHT / 3.5f);

		Vector2 spawnPos = { x(mt), y(mt) };

		for (int i = 0; i < 360; i += 5) {
			Projectile* pProj = new Projectile;
			pProj->SetPos(spawnPos);
			pProj->SetSize({ 15.0f, 15.0f });
			pProj->SetSpeed(300.0f);
			pProj->SetDir(i);
			pProj->SetLifeTime(15.0f);

			pProj->GetComponent<CircleCollider>()->SetSize({ 13.0f, 13.0f });

			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		}
	});
}

#pragma endregion
#pragma region ThirdPattern

void JHBoss::ThirdPattern() {
	Move({ 750.0f, 250.0f }, 3.5f);
	Wait(4.5f, [this]() {
		Move({ 1170.0f, 280.0f }, 3.5f);
		Wait(4.5f, [this]() {
			Move({ 960.0f, 100.0f }, 3.5f);
		});
	});
}

void JHBoss::ThirdPatternUpdate() {
	m_timer += fDT;
	if (m_timer >= 0.08f) {
		m_timer = 0.0f;

		Four();
	}
}

void JHBoss::Four() {
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randomize(-40.0f, 40.0f);
	for (int i = 45; i < 360; i += 36) {
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x, m_vPos.y });
		pProj->SetSize({ 10.0f, 10.0f });
		pProj->SetSpeed(150.0f);
		pProj->SetDir(i + randomize(mt));
		pProj->SetLifeTime(8.0f);

		pProj->GetComponent<CircleCollider>()->SetSize({ 8.0f, 8.0f });

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

#pragma endregion
