#include "pch.h"
#include "Texture.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "EndImage.h"

void EndImage::Init() { }

void EndImage::Update() {
	if (GET_KEY_DOWN(KEY_TYPE::ESC))
		GET_SINGLE(SceneManager)->LoadScene(L"SelectScene");
}

void EndImage::Render(HDC hdc) {
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	Vector2 renderPos = { m_vPos.x - width / 2.0f , m_vPos.y - height / 2.0f };
	TransparentBlt(hdc, renderPos.x, renderPos.y, width, height, m_pTex->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
}
