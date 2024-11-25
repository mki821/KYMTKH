#include "pch.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "Projectile.h"
#include "Player.h"

Player::Player() : m_pTex(nullptr), m_speed(100.0f) {
	AddComponent<Collider>();
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

	movement.Normalize();

	m_vPos += movement * m_speed * fDT;

	if (GET_KEY(KEY_TYPE::SPACE))
		CreateProjectile();
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
