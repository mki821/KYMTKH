#include "pch.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CircleCollider.h"
#include "Projectile.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GDISelector.h"
#include "Player.h"

Player::Player() : m_hp(5), m_speed(300.0f) {
	AddComponent<CircleCollider>();
}

Player::~Player() { }

void Player::Init() {
	GetComponent<CircleCollider>()->SetSize(m_vSize);

	m_pTex = GET_RES(L"Player");
	m_pProjectile = GET_RES(L"Projectile_15x15");
}

void Player::Update() {
	Object::Update();

	Move();

	m_timer += fDT;
	if (m_timer >= 0.08f && GET_KEY(KEY_TYPE::X)) {
		m_timer = 0.0f;
		CreateProjectile();
	}

	if (m_invincibilityTimer > 0.0f) {
		m_invincibilityTimer -= fDT;

		if (m_invincibilityTimer <= 0.0f) {
			GetComponent<CircleCollider>()->SetEnable(true);
		}
	}

	if(GET_KEY_DOWN(KEY_TYPE::ESC))
		GET_SINGLE(SceneManager)->LoadScene(L"SelectScene");
}

void Player::Render(HDC hdc) {
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	Vector2 renderPos = { m_vPos.x - width, m_vPos.y - height };
	TransparentBlt(hdc, renderPos.x, renderPos.y, width * 2.0f, height * 2.0f, m_pTex->GetDC(), 0, 0, width, height, RGB(255, 0, 255));

	GDISelector a(hdc, PEN_TYPE::BLACK_THICK);
	ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x * 1.3f, m_vSize.y * 1.3f);
}

void Player::SetDead() {
	Object::SetDead();

	GET_SINGLE(ResourceManager)->Play(L"GameOver");
}

void Player::Move() {
	Vector2 movement;

	if (GET_KEY(KEY_TYPE::UP))
		--movement.y;
	if (GET_KEY(KEY_TYPE::LEFT))
		--movement.x;
	if (GET_KEY(KEY_TYPE::DOWN))
		++movement.y;
	if (GET_KEY(KEY_TYPE::RIGHT))
		++movement.x;

	bool isShift = GET_KEY(KEY_TYPE::LSHIFT);

	movement.Normalize();

	m_vPos += movement * (isShift ? m_speed / 3.0f : m_speed) * fDT;
	ClampPos();
}

void Player::ClampPos() {
	float halfSizeX = m_vSize.x / 2;
	float minX = SCREEN_WIDTH / 4.0f + halfSizeX;
	float maxX = SCREEN_WIDTH - SCREEN_WIDTH / 3.0f - halfSizeX;

	float halfSizeY = m_vSize.y / 2;
	float minY = halfSizeY;
	float maxY = SCREEN_HEIGHT - halfSizeY;

	m_vPos.x = std::clamp(m_vPos.x, minX, maxX);
	m_vPos.y = std::clamp(m_vPos.y, minY, maxY);
}

void Player::CreateProjectile() {
	{
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x - m_vSize.x - 1.5f, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetDir({ 0.0f, -1.0f });
		pProj->SetSpeed(1300.0f);
		pProj->SetTexture(m_pProjectile);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::PLAYER_PROJECTILE);
	}
	{
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x + m_vSize.x + 1.5f, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetDir({ 0.0f, -1.0f });
		pProj->SetSpeed(1300.0f);
		pProj->SetTexture(m_pProjectile);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::PLAYER_PROJECTILE);
	}
	{
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x + m_vSize.x + 3.5f, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetDir({ 1.0f, -5.0f });
		pProj->SetSpeed(1300.0f);
		pProj->SetTexture(m_pProjectile);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::PLAYER_PROJECTILE);
	}
	{
		Projectile* pProj = new Projectile;
		pProj->SetPos({ m_vPos.x - m_vSize.x - 3.5f, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 15.0f, 15.0f });
		pProj->SetDir({ -1.0f, -5.0f });
		pProj->SetSpeed(1300.0f);
		pProj->SetTexture(m_pProjectile);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::PLAYER_PROJECTILE);
	}
	GET_SINGLE(ResourceManager)->Play(L"Fire");
}

void Player::EnterCollision(Collider* other) {
	if (m_invincibilityTimer > 0.0f) return;

	wstring heartName = std::format(L"Heart_{0}", m_hp--);
	GET_SINGLE(UIManager)->RemoveUI(heartName);

	m_invincibilityTimer = 1.5f;
	GetComponent<CircleCollider>()->SetEnable(false);

	if (m_hp <= 0)
		SetDead();
}
