#include "pch.h"
#include "RandomMoveProjManager.h"
#include "SceneManager.h"
#include "RandomMoveProj.h"
#include "Object.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Boss.h"

void RandomMoveProjManager::Spawn(int count)
{
	for (int i = 0; i < count; i++) {
		RandomMoveProj* pProj = new RandomMoveProj;
		pProj->SetTexture(m_RandomProjTexture[rand() % 3]);
		pProj->SetChangeSpeed(120);
		pProj->SetPos({  m_owner->GetPos().x, m_owner->GetPos().y - m_owner->GetSize().y / 2.0f});
		pProj->SetSize({ 20.0f, 20.0f });
		pProj->SetSpeed(rand() % 200 + 100);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
		m_projVec.push_back(pProj);
	}
}

void RandomMoveProjManager::Delete()
{
	for (auto it = m_projVec.begin(); it != m_projVec.end(); ++it) {
		if (*it != nullptr) {
			(*it)->Delete();
			it = m_projVec.erase(it);
		}
		else {
			++it;
		}
	}
	m_projVec.clear();
	delete this;
} 

void RandomMoveProjManager::Stop()
{
	for (auto it = m_projVec.begin(); it != m_projVec.end(); ++it) {
		if (*it != nullptr) {
			(*it)->Stop();
			(*it)->SetTexture(m_whiteTex);
		}
	}
}

void RandomMoveProjManager::Remove()
{
	for (auto it = m_projVec.begin(); it != m_projVec.end(); ++it) {
		if (*it != nullptr) {
			(*it)->Remove();
		}
	}
}
