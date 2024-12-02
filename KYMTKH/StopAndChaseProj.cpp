#include "pch.h"
#include "StopAndChaseProj.h"
#include "TimeManager.h"
#include"SceneManager.h"
#include"Y_TestScene.h"
#include "FirstBoss.h"
#include "EventManager.h"

StopAndChaseProj::StopAndChaseProj() : Projectile() {}

StopAndChaseProj::~StopAndChaseProj()
{
	/*auto curScene = GET_SINGLE(SceneManager)->GetCurScene();
	auto yTestScene = std::dynamic_pointer_cast<Y_TestScene>(curScene);
	m_player = yTestScene->GetPlayer();*/
}

void StopAndChaseProj::Init()
{
	m_player = m_owner->GetPlayer();
}

void StopAndChaseProj::Update()
{
	m_timer += fDT;

	if (!chasePlayer) {
		if (m_timer > m_dirChangeTime) {
			chasePlayer = true;
			Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
			dir.Normalize();
			this->SetDir({ dir.x,dir.y });
			this->SetSpeed(m_changeSpeed);
		}
		else if (m_dirChangeTime - m_timer < 0.4f && m_dirChangeTime - m_timer > 0.3f) {
			this->SetSpeed(this->m_speed / 2);
		}
		else if (m_dirChangeTime - m_timer < 0.2f && m_dirChangeTime - m_timer > 0.f) {
			this->SetSpeed(0);
		}
	}
	

	m_vPos += m_vDir * m_speed * fDT;
	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

