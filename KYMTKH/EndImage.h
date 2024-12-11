#pragma once

#include "UI.h"

class Texture;

class EndImage : public UI {

public:
	EndImage() {}
	~EndImage() {}
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
public:
	void SetTexture(Texture* texture) { m_pTex = texture; }
protected:
	Texture* m_pTex = nullptr;
};
