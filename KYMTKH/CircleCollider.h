#pragma once

#include "Collider.h"

class CircleCollider : public Collider {
public:
	CircleCollider();
	~CircleCollider();
public:
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
};
