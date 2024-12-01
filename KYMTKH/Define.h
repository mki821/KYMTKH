#pragma once

#define DECLARE_SINGLE(type)      \
private:					      \
	type() {}					  \
public:						      \
	static type* GetInst() {      \
		static type m_pInst;	  \
		return &m_pInst;		  \
	}						      \

#define GET_SINGLE(type) type::GetInst()
#define fDT GET_SINGLE(TimeManager)->GetDT()

#define GET_RESPATH GET_SINGLE(ResourceManager)->GetResPath()
#define GET_RES(name, path) GET_SINGLE(ResourceManager)->TextureLoad(name, path);

#define KEY_CHECK(key, state) InputManager::GetInst()->GetKey(key) == state
#define GET_KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define GET_KEY_UP(key) KEY_CHECK(key, KEY_STATE::UP)
#define GET_KEY_DOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define GET_KEY(key) KEY_CHECK(key, KEY_STATE::PRESS)

#define GET_MOUSEPOS GET_SINGLE(InputManager)->GetMousePos()

#define Vector2ToAngle(dir) throw

#define RECT_RENDER(hdc, posx, posy, sizex, sizey) Rectangle(hdc, (int)(posx - sizex / 2), (int)(posy - sizey / 2), (int)(posx + sizex / 2), (int)(posy + sizey / 2))
#define ELLIPSE_RENDER(hdc, posx, posy, sizex, sizey) Ellipse(hdc, (int)(posx - sizex / 2), (int)(posy - sizey / 2), (int)(posx + sizex / 2), (int)(posy + sizey / 2))
#define RECT_MAKE(posx, posy, sizex, sizey) { posx - sizex / 2, posy - sizey / 2, posx + sizex / 2, posy + sizey / 2}
