#include "pch.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Component.h"
#include "Object.h"

Object::Object() : m_vPos{}, m_vSize{} { }

Object::~Object() {
	for (Component* component : m_vecComponents) {
		if (component != nullptr)
			delete component;
	}
	m_vecComponents.clear();
}

void Object::Update() {
	if (m_wait) {
		m_waitTimer -= fDT;

		if (m_waitTimer <= 0.0f) {
			m_wait = false;
			m_waitTimer = 0.0f;
			m_waitFunc();
		}
	}
}

void Object::LateUpdate() {
	for (Component* component : m_vecComponents) {
		if (component != nullptr)
			component->LateUpdate();
	}
}

void Object::ComponentRender(HDC hdc) {
	for (Component* component : m_vecComponents) {
		if (component != nullptr)
			component->Render(hdc);
	}
}

void Object::Wait(float second, std::function<void()> func) {
	m_wait = true;
	m_waitTimer = second;
	m_waitFunc = func;
}

void Object::EnterCollision(Collider* other) { }
void Object::StayCollision(Collider* other) { }
void Object::ExitCollision(Collider* other) { }
