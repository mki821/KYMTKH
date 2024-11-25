#include "pch.h"
#include "Core.h"
#include "InputManager.h"

void InputManager::Init() {
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void InputManager::Update() {
    if (GetFocus() == nullptr) {
        for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
            m_vecKey[i].IsPrevCheck = false;
            m_vecKey[i].eState = KEY_STATE::NONE;
        }
        return;
    }

	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i) {
        if (GetAsyncKeyState(m_arrVKKey[i])) {
            if (m_vecKey[i].IsPrevCheck)
                m_vecKey[i].eState = KEY_STATE::PRESS;
            else m_vecKey[i].eState = KEY_STATE::DOWN;

            m_vecKey[i].IsPrevCheck = true;
        }
        else {
            if (m_vecKey[i].IsPrevCheck)
                m_vecKey[i].eState = KEY_STATE::UP;
            else m_vecKey[i].eState = KEY_STATE::NONE;

            m_vecKey[i].IsPrevCheck = false;
        }
	}

    GetCursorPos(&m_ptMouse);
    ScreenToClient(GET_SINGLE(Core)->GetHWnd(), &m_ptMouse);
}
