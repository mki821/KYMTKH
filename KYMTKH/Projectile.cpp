#include "pch.h"
#include "TimeManager.h"
#include "CircleCollider.h"
#include "EventManager.h"
#include "Texture.h"
#include "Projectile.h"

Projectile::Projectile() : m_speed(500.0f) {
	AddComponent<CircleCollider>();
}

Projectile::~Projectile() {
    DeleteObject(m_rotateBitmap);
    DeleteDC(m_rotateDC);
}

void Projectile::Init() {
	GetComponent<CircleCollider>()->SetSize(m_vSize);
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
        POINT vertices[4];

        float delta = atan2(m_vDir.y, m_vDir.x);
        delta -= PI / 2.0f;

        float cosA = cosf(delta);
        float sinA = sinf(delta);

        BITMAP bm = m_pTex->GetBitmap();

        int halfWidth = bm.bmWidth / 2;
        int halfHeight = bm.bmHeight / 2;

        vertices[0].x = (LONG)((-halfWidth * cosA + (-halfHeight) * sinA));
        vertices[0].y = (LONG)((-halfWidth * sinA - (-halfHeight) * cosA));
        vertices[1].x = (LONG)((halfWidth * cosA + (-halfHeight) * sinA));
        vertices[1].y = (LONG)((halfWidth * sinA - (-halfHeight) * cosA));
        vertices[2].x = (LONG)((-halfWidth * cosA + (halfHeight)*sinA));
        vertices[2].y = (LONG)((-halfWidth * sinA - (halfHeight)*cosA));
        vertices[3].x = (LONG)((halfWidth * cosA + (halfHeight)*sinA));
        vertices[3].y = (LONG)((halfWidth * sinA - (halfHeight)*cosA));

        long maxX = vertices[0].x, minX = vertices[0].x;
        long maxY = vertices[0].y, minY = vertices[0].y;

        for (int i = 0; i < 4; i++) {
            if (vertices[i].x > maxX)
                maxX = vertices[i].x;
            if (vertices[i].y > maxY)
                maxY = vertices[i].y;
            if (vertices[i].x < minX)
                minX = vertices[i].x;
            if (vertices[i].y < minY)
                minY = vertices[i].y;
        }

        m_rotateDC = CreateCompatibleDC(m_pTex->GetDC());
        m_rotateBitmap = CreateCompatibleBitmap(m_pTex->GetDC(), maxX - minX, maxY - minY);
        SelectObject(m_rotateDC, m_rotateBitmap);

        RECT rect = { 0, 0, maxX - minX, maxY - minY };
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
        FillRect(m_rotateDC, &rect, hBrush);
        DeleteObject(hBrush);

        POINT verticesSubset[3] = { vertices[0], vertices[1], vertices[2] };

        for (int i = 0; i < 4; ++i) {
            if (minX < 0) {
                vertices[i].x -= minX;
                if (vertices[i].x > maxX)
                    maxX = vertices[i].x;
            }
            if (minY < 0) {
                vertices[i].y -= minY;
                if (vertices[i].y > maxY)
                    maxY = vertices[i].y;
            }

            if (i != 3) verticesSubset[i] = vertices[i];
        }

        if (minX < 0) minX = 0;
        if (minY < 0) minY = 0;

		Vector2 renderPos = { m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2 };
        PlgBlt( m_rotateDC, verticesSubset, m_pTex->GetDC(), 0, 0, bm.bmWidth, bm.bmHeight, NULL, 0, 0);
        TransparentBlt( hdc, (int)(renderPos.x), (int)(renderPos.y), (int)m_vSize.x, (int)m_vSize.y, 
            m_rotateDC, minX, minY,  maxX - minX, maxY - minY, RGB(255, 0, 255));
	}
	else ELLIPSE_RENDER(hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void Projectile::EnterCollision(Collider* other) 
{
	GET_SINGLE(EventManager)->DeleteObject(this);
} 
