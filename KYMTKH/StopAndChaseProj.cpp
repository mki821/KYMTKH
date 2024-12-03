#include "pch.h"
#include "StopAndChaseProj.h"
#include "TimeManager.h"
#include "FirstBoss.h"
#include "EventManager.h"
#include "CircleCollider.h"

StopAndChaseProj::StopAndChaseProj() : Projectile() {}

StopAndChaseProj::~StopAndChaseProj()
{
}

void StopAndChaseProj::Init()
{
	m_player = m_owner->GetPlayer();
	GetComponent<CircleCollider>()->SetSize(GetSize());
}

void StopAndChaseProj::Update()
{
	if (!m_chasePlayer) {
		m_timer += fDT;
		float gap = m_dirChangeTime - m_timer;
		if (m_timer > m_dirChangeTime) {
			m_chasePlayer = true;
			Vector2 dir = { m_player->GetPos().x - this->GetPos().x, m_player->GetPos().x - this->GetPos().y };
			dir.Normalize();
			this->SetDir({ dir.x,dir.y });
			this->SetSpeed(m_changeSpeed);
		}
		else if (gap < 0.5f && gap > 0.3f) {
			this->SetSpeed(this->m_speed / 2);
		}
		else if (gap < 0.2f && gap > 0.f) {
			this->SetSpeed(0);
		}
	}

	m_vPos += m_vDir * m_speed * fDT;
	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

