#pragma once

class UI {
public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
public:
	void SetPos(Vector2 pos) { m_vPos = pos; }
	const Vector2 GetPos() const { return m_vPos; }
	void SetSize(Vector2 size) { m_vSize = size; }
	const Vector2 GetSize() const { return m_vSize; }
protected:
	Vector2 m_vPos = { 0.0f, 0.0f };
	Vector2 m_vSize = { 50.0f, 50.0f };
};

