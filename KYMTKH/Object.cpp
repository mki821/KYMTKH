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
	m_vecWaitFuncs.clear();
	m_vecAdditionalWaitFuncs.clear();
}

void Object::Update() {
	if (m_vecWaitFuncs.size() > 0) {
		vector<std::pair<float, std::function<void()>>>::iterator iter;

		for (iter = m_vecWaitFuncs.begin(); iter != m_vecWaitFuncs.end(); ++iter) {
			(*iter).first -= fDT;

			if ((*iter).first <= 0.0f) {
				(*iter).second();
				iter = m_vecWaitFuncs.erase(iter);

				if (iter == m_vecWaitFuncs.end())
					break;
			}
		}
	}

	if (m_vecAdditionalWaitFuncs.size() > 0) {
		for (int i = 0; i < m_vecAdditionalWaitFuncs.size(); ++i) {
			m_vecWaitFuncs.push_back(m_vecAdditionalWaitFuncs[i]);
		}
		m_vecAdditionalWaitFuncs.clear();
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
	std::pair<float, std::function<void()>> temp = { second, func };
	m_vecAdditionalWaitFuncs.push_back(temp);
}

void Object::EnterCollision(Collider* other) { }
void Object::StayCollision(Collider* other) { }
void Object::ExitCollision(Collider* other) { }
