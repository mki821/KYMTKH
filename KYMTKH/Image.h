#pragma once
#include "UI.h"
class Image : public UI {
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
};
