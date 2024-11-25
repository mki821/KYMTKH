#include "pch.h"
#include <assert.h>
#include "Core.h"
#include "Texture.h"

Texture::Texture() :m_hDC(nullptr), m_hBit(nullptr), m_bitInfo{ } { }

Texture::~Texture() {
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void Texture::Load(const wstring& path) {
	// Instnace Handle (nullptr: µ¶¸³Çü)
	// path
	// BITMAP / ICON / CURSOR / ...
	// Image(Resource) Size
	// Modify Flag
	m_hBit = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	m_hDC = CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
	SelectObject(m_hDC, m_hBit);
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
