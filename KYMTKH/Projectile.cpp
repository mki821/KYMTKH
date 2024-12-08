#include "pch.h"
#include "TimeManager.h"
#include "CircleCollider.h"
#include "EventManager.h"
#include "Texture.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Projectile.h"

Projectile::Projectile() : m_speed(500.0f) {
	AddComponent<CircleCollider>();

    m_hBrush = CreateSolidBrush(RGB(255, 0, 255));
}

Projectile::~Projectile() {
    DeleteObject(m_hBrush);
    DeleteObject(m_rotateBitmap);
    DeleteDC(m_rotateDC);
}

void Projectile::Init() {
    GetComponent<CircleCollider>()->SetSize(m_vSize);
    GET_SINGLE(ResourceManager)->Play(L"Fire");
}

void Projectile::Update() {
	m_vPos += m_vDir * m_speed * fDT;

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC hdc) {
	if (m_pTex != nullptr) {
        float delta = atan2(m_vDir.y, m_vDir.x);
        delta -= PI / 2.0f;

        float cosA = cosf(delta);
        float sinA = sinf(delta);

        BITMAP bm = m_pTex->GetBitmap();

        int halfWidth = bm.bmWidth / 2;
        int halfHeight = bm.bmHeight / 2;

        POINT vertices[3];
        vertices[0].x = cosA * -halfWidth - sinA * halfHeight + halfWidth;
        vertices[0].y = sinA * -halfWidth + cosA * halfHeight + halfHeight;

        vertices[1].x = cosA * halfWidth - sinA * halfHeight + halfWidth;
        vertices[1].y = sinA * halfWidth + cosA * halfHeight + halfHeight;

        vertices[2].x = cosA * -halfWidth - sinA * -halfHeight + halfWidth;
        vertices[2].y = sinA * -halfWidth + cosA * -halfHeight + halfHeight;

        FillRect(m_rotateDC, &m_rt, m_hBrush);

		Vector2 renderPos = { m_vPos.x - GAME_LEFT - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2 };

        vertices[0].x += renderPos.x;
        vertices[0].y += renderPos.y;

        vertices[1].x += renderPos.x;
        vertices[1].y += renderPos.y;

        vertices[2].x += renderPos.x;
        vertices[2].y += renderPos.y;

        PlgBlt(GET_SINGLE(RenderManager)->GetDC(), vertices, m_pTex->GetDC(), 0, 0, bm.bmWidth, bm.bmHeight, NULL, 0, 0);
        //TransparentBlt(GET_SINGLE(RenderManager)->GetDC(), renderPos.x, renderPos.y, m_vSize.x, m_vSize.y, m_rotateDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));
	}
	else ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Projectile::EnterCollision(Collider* other) 
{
	GET_SINGLE(EventManager)->DeleteObject(this);
}
void Projectile::SetTexture(Texture* texture) {
    m_pTex = texture;

    m_rotateDC = CreateCompatibleDC(m_pTex->GetDC());
    m_rotateBitmap = CreateCompatibleBitmap(m_pTex->GetDC(), m_pTex->GetWidth(), m_pTex->GetHeight());
    SelectObject(m_rotateDC, m_rotateBitmap);

    BITMAP bm = m_pTex->GetBitmap();
    m_rt = { 0, 0, bm.bmWidth, bm.bmHeight };
}
