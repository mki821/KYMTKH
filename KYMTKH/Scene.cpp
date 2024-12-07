#include "pch.h"
#include "Object.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Scene.h"

Scene::~Scene() {
	Release();
}

void Scene::Update() {
	for (int i = 0; i < (UINT)LAYER::END; ++i) {
		for (int j = 0; j < m_vecObj[i].size(); ++j) {
			if(!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Update();
		}
	}
}

void Scene::LateUpdate() {
	for (int i = 0; i < (UINT)LAYER::END; ++i) {
		for (int j = 0; j < m_vecObj[i].size(); ++j) {
			m_vecObj[i][j]->LateUpdate();
		}
	}
}

void Scene::Render(HDC hdc) {
	for (int i = 0; i < (UINT)LAYER::END; ++i) {
		for (int j = 0; j < m_vecObj[i].size(); ) {
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j++]->Render(hdc);
			else m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}

	for (int i = 0; i < (UINT)LAYER::END; ++i) {
		for (int j = 0; j < m_vecObj[i].size(); ++j) {
			m_vecObj[i][j]->ComponentRender(hdc);
		}
	}
}

void Scene::Release() {
	for (int i = 0; i < (UINT)LAYER::END; ++i) {
		for (int j = 0; j < m_vecObj[i].size(); ++j) {
			delete m_vecObj[i][j];
		}
		m_vecObj[i].clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}

void Scene::DeleteEnemyProjectiles() {
	for (int j = 0; j < m_vecObj[(UINT)LAYER::ENEMY_PROJECTILE].size(); ++j) {
		if (!m_vecObj[(UINT)LAYER::ENEMY_PROJECTILE][j]->GetIsDead())
			GET_SINGLE(EventManager)->DeleteObject(m_vecObj[(UINT)LAYER::ENEMY_PROJECTILE][j]);
	}
}
