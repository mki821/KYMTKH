#pragma once

#include "Object.h"

class Lemniscate;

class LemniscateParent : public Object {
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
public:
	const bool GetScalceUp() const { return m_scaleUp; }
private:
	bool m_scaleUp;
private:
	vector<Lemniscate*> m_vecLemniscates;
};
