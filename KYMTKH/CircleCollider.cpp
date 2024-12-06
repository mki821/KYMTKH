#include "pch.h"
#include "Object.h"
#include "GDISelector.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider() : Collider() { }
CircleCollider::~CircleCollider() { }

void CircleCollider::LateUpdate() {
	Collider::LateUpdate();
}

void CircleCollider::Render(HDC hdc) { }
