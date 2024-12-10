#include "pch.h"
#include "UIManager.h"
#include "Image.h"
#include "FillImage.h"
#include "Background.h"
#include "Player.h"
#include "JHBoss.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "TestScene.h"

void TestScene::Init() {
	LOAD_RES(L"Projectile_20x35", L"Texture\\Projectile\\Projectile_20x35.bmp");
	LOAD_RES(L"Projectile_10x10", L"Texture\\Projectile\\Projectile_10x10.bmp");
	LOAD_RES(L"JHBoss", L"Texture\\Boss\\JHBoss.bmp");
	LOAD_RES(L"JHBackground", L"Texture\\Background\\JHBackground.bmp");

	GET_SINGLE(ResourceManager)->Play(L"SecondBGM");

	for (int i = 1; i <= 5; ++i) {
		Image* heart = new Image;
		heart->SetPos({ GAME_RIGHT + 70.0f, SCREEN_HEIGHT - 60.0f * i });
		heart->SetTexture(GET_RES(L"Heart"), RENDER_TYPE::TransparentBlt);

		wstring name = std::format(L"Heart_{0}", i);
		GET_SINGLE(UIManager)->AddUI(name, heart);
	}

	FillImage* bossHealth = new FillImage;
	bossHealth->SetPos({ 1082.0f, 100.0f });
	bossHealth->SetSize({ 500.0f, 30.0f });
	bossHealth->SetTexture(GET_RES(L"BossHealthBar"), RENDER_TYPE::TransparentBlt);

	GET_SINGLE(UIManager)->AddUI(L"BossHealth", bossHealth);

	Background* pBackground = new Background;
	pBackground->SetTexture(GET_RES(L"JHBackground"));
	AddObject(pBackground, LAYER::BACKGROUND);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ GAME_CENTER, 650.0f });
	pPlayer->SetSize({ 8.0f, 8.0f });
	AddObject(pPlayer, LAYER::PLAYER);

	Boss* pBoss = new JHBoss;
	pBoss->SetPos({ GAME_CENTER, 200.0f });
	pBoss->SetSize({ 80.0f, 80.0f });
	pBoss->GetComponent<Collider>()->SetSize(pBoss->GetSize());
	pBoss->SetTexture(GET_RES(L"JHBoss"));
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}

void TestScene::Release() {
	GET_SINGLE(UIManager)->Clear();
	Scene::Release();
}
