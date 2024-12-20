#include "pch.h"
#include "SecondBossScene.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "UIManager.h"
#include "Image.h"
#include "FillImage.h"
#include "FirstBoss.h"
#include "SecondBoss.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Background.h"

void SecondBossScene::Init()
{
	LOAD_RES(L"BlueDiamond_10x18", L"Texture\\Projectile\\BlueDiamond_10x18.bmp");
	LOAD_RES(L"BluepleDia_10x18", L"Texture\\Projectile\\BluepleDia_10x18.bmp");
	LOAD_RES(L"BlueShuriken_10x18", L"Texture\\Projectile\\BlueShuriken_10x18.bmp");
	LOAD_RES(L"GreenDia_10x18", L"Texture\\Projectile\\GreenDia_10x18.bmp");
	LOAD_RES(L"OrrangeDia_10x18", L"Texture\\Projectile\\OrrangeDia_10x18.bmp");
	LOAD_RES(L"PurpleDia_10x18", L"Texture\\Projectile\\PurpleDia_10x18.bmp");
	LOAD_RES(L"RedDia_10x18", L"Texture\\Projectile\\RedDia_10x18.bmp");
	LOAD_RES(L"RedShuriken_10x18", L"Texture\\Projectile\\RedShuriken_10x18.bmp");
	LOAD_RES(L"WhiteDiamod_10x18", L"Texture\\Projectile\\WhiteDiamod_10x18.bmp");

	LOAD_RES(L"SecondBoss", L"Texture\\Boss\\SecondBoss.bmp");
	LOAD_RES(L"SecondBossBackGround", L"Texture\\Background\\SecondBossBackGround.bmp");

	GET_SINGLE(ResourceManager)->Play(L"ThirdBGM");

	Background* pBackground = new Background;
	pBackground->SetTexture(GET_RES(L"SecondBossBackGround"));
	AddObject(pBackground, LAYER::BACKGROUND);
	for (int i = 1; i <= 5; ++i) {
		Image* heart = new Image;
		heart->SetPos({ GAME_RIGHT + 70.0f, SCREEN_HEIGHT - 60.0f * i });
		heart->SetTexture(GET_RES(L"Heart"), RENDER_TYPE::TransparentBlt);

		wstring name = std::format(L"Heart_{0}", i);
		GET_SINGLE(UIManager)->AddUI(name, heart);
	}

	FillImage* bossHealth = new FillImage;
	bossHealth->SetPos({ 1050.0f, 100.0f });
	bossHealth->SetSize({ 500.0f, 30.0f });
	bossHealth->SetTexture(GET_RES(L"BossHealthBar"), RENDER_TYPE::TransparentBlt);

	GET_SINGLE(UIManager)->AddUI(L"BossHealth", bossHealth);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ GAME_CENTER, 650.0f });
	pPlayer->SetSize({ 8.0f, 8.0f });
	AddObject(pPlayer, LAYER::PLAYER);
	SetPlayer(pPlayer);

	Boss* pBoss = new SecondBoss;
	pBoss->SetPos({ GAME_CENTER, 200.0f });
	pBoss->SetSize({ 80.0f, 80.0f });
	pBoss->GetComponent<Collider>()->SetSize(pBoss->GetSize());
	pBoss->GetComponent<Collider>()->SetOffSetPos({ 0,-55 });
	pBoss->SetTexture(GET_RES(L"SecondBoss"));
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}

void SecondBossScene::Release()
{
	Scene::Release();
}
