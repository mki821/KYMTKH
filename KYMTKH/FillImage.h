#pragma once

#include "Image.h"

class FillImage : public Image {
public:
	FillImage() {}
	~FillImage() {}
public:
	void Render(HDC hdc) override;
public:
	const float GetFillAmount() const { return m_fillAmount; }
	void SetFillAmount(float fillAmount) { m_fillAmount = std::clamp(fillAmount, 0.0f, 1.0f); }
	void SetIsHorizon(bool isHorizon) { m_isHorizon = isHorizon; }
private:
	float m_fillAmount = 1.0f;
	bool m_isHorizon = true;
};

