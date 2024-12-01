#include "pch.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Lemniscate.h"
#include "LemniscateParent.h"

void LemniscateParent::Init() {
	for (int i = 0; i < 1440; i += 5) {
		Lemniscate* pProj = new Lemniscate(i);
		pProj->SetPos({ m_vPos.x, m_vPos.y - m_vSize.y / 2.0f });
		pProj->SetSize({ 30.0f, 30.0f });
		pProj->SetSpeed(200.0f);
		pProj->SetLifeTime(15.0f);
		pProj->SetRotationSpeed(2.0f);
		pProj->SetTurnSpeed(10.0f);
		pProj->SetOwner(this);

		m_vecLemniscates.push_back(pProj);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(pProj, LAYER::ENEMY_PROJECTILE);
	}
}

void LemniscateParent::Update() {
	if (GET_KEY_DOWN(KEY_TYPE::P)) m_scaleUp = true;
}

void LemniscateParent::Render(HDC hdc) {

}
