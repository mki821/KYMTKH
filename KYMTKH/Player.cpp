#include "pch.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CircleCollider.h"
#include "Projectile.h"
#include "Player.h"

Player::Player() : m_pTex(nullptr), m_hp(10), m_speed(200.0f) {
	AddComponent<CircleCollider>();
}

Player::~Player() { }

void Player::Update() {
	Vector2 movement;

	if (GET_KEY(KEY_TYPE::W))
		--movement.y;
	if (GET_KEY(KEY_TYPE::A))
		--movement.x;
	if (GET_KEY(KEY_TYPE::S))
		++movement.y;
	if (GET_KEY(KEY_TYPE::D))
		++movement.x;

	bool isShift = GET_KEY(KEY_TYPE::LSHIFT);

	movement.Normalize();

	m_vPos += movement * (isShift ? m_speed / 2.0f : m_speed) * fDT;

	m_timer += fDT;
	if (m_timer >= 0.5f && GET_KEY(KEY_TYPE::SPACE)) {
		m_timer = 0.0f;
		CreateProjectile();
	}
}

void Player::Render(HDC hdc) {
	RECT_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Player::CreateProjectile() {
	Projectile* pProj = new Projectile;
	pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
	pProj->SetSize({ 30.0f, 30.0f });
	pProj->SetDir({ 0.0f, -1.0f });

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::PLAYER_PROJECTILE);
}

void Player::EnterCollision(Collider* other) {
	--m_hp;

	cout << m_hp;

	if (m_hp <= 0)
		SetDead();
}
