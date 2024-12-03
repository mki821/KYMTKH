#pragma once

#include "Object.h"

class Lemniscate;

class LemniscateParent : public Object {
public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
	void ComponentRender(HDC hdc) override;
public:
	void SetTargetPos(Vector2 targetPos) { m_targetPos = targetPos; }
	void SetTurnDirection(int direction) { m_turnDirection = direction; }
	void SetLifeTime(float lifeTime) { m_lifeTimer = lifeTime; }
private:
	int m_turnDirection = 1;
	float m_timer = 0.0f;
	float m_lifeTimer = 0.0f;
	Vector2 m_createdPos;
	Vector2 m_targetPos;
private:
	vector<Lemniscate*> m_vecLemniscates;
};
