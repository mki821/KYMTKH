#pragma once

#include "UI.h"

class Texture;

class Button : public UI {
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
public:
	std::function<void()> event;
public:
	void SetTexture(Texture* texture, RENDER_TYPE renderType) {
		m_pTex = texture;
		m_eRenderType = renderType;
	}
protected:
	Texture* m_pTex = nullptr;
	RENDER_TYPE m_eRenderType;
};

