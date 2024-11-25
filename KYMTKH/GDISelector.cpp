#include "pch.h"
#include "Core.h"
#include "GDISelector.h"

GDISelector::GDISelector(HDC _hdc, PEN_TYPE _ePen) : m_hDC(_hdc), m_hDefaultBrush(nullptr), m_hDefaultPen(nullptr), m_hDefaultFont(nullptr), m_hFont(nullptr) {
    HPEN hColorPen = GET_SINGLE(Core)->GetPen(_ePen);
    m_hDefaultPen = (HPEN)SelectObject(_hdc, hColorPen);
}

GDISelector::GDISelector(HDC _hdc, BRUSH_TYPE _eBrush) : m_hDC(_hdc), m_hDefaultBrush(nullptr), m_hDefaultPen(nullptr), m_hDefaultFont(nullptr), m_hFont(nullptr) {
    HBRUSH hColorBrush = GET_SINGLE(Core)->GetBrush(_eBrush);
    m_hDefaultBrush = (HBRUSH)SelectObject(_hdc, hColorBrush);
}

GDISelector::GDISelector(HDC _hdc, HFONT _font) : m_hDC(_hdc), m_hDefaultBrush(nullptr), m_hDefaultPen(nullptr), m_hDefaultFont(nullptr), m_hFont(nullptr) {
    m_hFont = _font;
    m_hDefaultFont = (HFONT)SelectObject(_hdc, m_hFont);
    SetBkMode(_hdc, TRANSPARENT);
}

GDISelector::~GDISelector() {
    SelectObject(m_hDC, m_hDefaultPen);
    SelectObject(m_hDC, m_hDefaultBrush);
    SelectObject(m_hDC, m_hDefaultFont);
}