#include "pch.h"
#include "UIManager.h"
#include "Image.h"
#include "FillImage.h"
#include "Player.h"
#include "JHBoss.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "TestScene.h"

void TestScene::Init() {
	LOAD_RES(L"Projectile_20x20", L"Texture\\Projectile\\Projectile_20x20.bmp");
	LOAD_RES(L"Projectile_15x15", L"Texture\\Projectile\\Projectile_15x15.bmp");
	LOAD_RES(L"Projectile_10x10", L"Texture\\Projectile\\Projectile_10x10.bmp");

	for (int i = 1; i <= 5; ++i) {
		Image* heart = new Image;
		heart->SetPos({ GAME_RIGHT + 70.0f, SCREEN_HEIGHT - 60.0f * i });

		wstring name = std::format(L"Heart_{0}", i);
		GET_SINGLE(UIManager)->AddUI(name, heart);
	}

	FillImage* bossHealth = new FillImage;
	bossHealth->SetPos({ 1082.0f, 100.0f });
	bossHealth->SetSize({ 500.0f, 30.0f });

	GET_SINGLE(UIManager)->AddUI(L"BossHealth", bossHealth);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ GAME_CENTER, 850.0f });
	pPlayer->SetSize({ 8.0f, 8.0f });
	AddObject(pPlayer, LAYER::PLAYER);

	Boss* pBoss = new JHBoss;
	pBoss->SetPos({ GAME_CENTER, 200.0f });
	pBoss->SetSize({ 45.0f, 45.0f });
	pBoss->GetComponent<Collider>()->SetSize(pBoss->GetSize());
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}

void TestScene::Release() {
	Scene::Release();

	GET_SINGLE(UIManager)->Clear();
}
