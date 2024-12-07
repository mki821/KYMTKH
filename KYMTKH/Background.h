#pragma once

#include "Object.h"

class Texture;

class Background : public Object {
public:
	void Init() override { };
	void Render(HDC hdc) override;
public:
	void SetTexture(Texture* texture) { m_pTex = texture; }
protected:
	Texture* m_pTex = nullptr;
};

