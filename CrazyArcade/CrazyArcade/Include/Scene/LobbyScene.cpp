#include "LobbyScene.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "VillageMap.h"
#include "../Animation/Animation.h"
#include "../Object/Obj.h"
#include "../Object/ObjectManager.h"
#include "../Object/Background.h"
#include "../Object/UIButton.h"
#include "../Collider/ColliderRect.h"

CLobbyScene::CLobbyScene() : 
	m_iSellectMap(0)
{
}


CLobbyScene::~CLobbyScene()
{
}

bool CLobbyScene::Init()
{
	CLayer* pBackLayer = m_pScene->FindLayer("BackgroundLayer");
	CLayer* pUILayer = m_pScene->FindLayer("UILayer");

	// Lobby Background 
	CObj* pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Background");
	pBackground->SetTexture("Lobby", L"02.Lobby/Lobby_Bg.bmp", true);
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	// Map1
	// Button
	CObj* pMap1Button = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Map1Button");

	pMap1Button->SetPos(698.f, 348.f);
	pMap1Button->SetTexture("Map1Button", L"02.Lobby/Loddy_Image_SelectMap_0.bmp", true);
	pMap1Button->SetAnimation("LogoButton.anm");
	POSITION tPos = pMap1Button->GetPos() - pMap1Button->GetPivot() * pMap1Button->GetSize();

	CColliderRect* pRC = CColliderRect::Create("Map1Button", tPos.x, tPos.y, tPos.x + pMap1Button->GetSize().x, tPos.y + pMap1Button->GetSize().y);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pMap1Button);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pMap1Button);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pMap1Button);

	((CUIButton*)pMap1Button)->SetTag("Map1Button");
	((CUIButton*)pMap1Button)->AddCallback<CLobbyScene>(&CLobbyScene::MapSellectCallback, this);

	pMap1Button->AddCollider(pRC);

	pUILayer->AddObject(pMap1Button);
	SAFE_RELEASE(pMap1Button);

	// mini image
	CObj* pMap1 = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Map1Image");

	pMap1->SetPos(477.f, 342.f);
	pMap1->SetTexture("Map1Image", L"02.Lobby/Lobby_Image_Map_0.bmp", true);
	pMap1->SetEnable(false);

	pUILayer->AddObject(pMap1);
	SAFE_RELEASE(pMap1);

	// Map2 
	// button
	CObj* pMap2Button = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Map2Button");

	pMap2Button->SetPos(698.f, 366.f);
	pMap2Button->SetTexture("Map2Button", L"02.Lobby/Loddy_Image_SelectMap_1.bmp", true);
	pMap2Button->SetAnimation("LogoButton.anm");
	tPos = pMap2Button->GetPos() - pMap2Button->GetPivot() * pMap2Button->GetSize();
	pRC = CColliderRect::Create("Map2Button", tPos.x, tPos.y, tPos.x + pMap2Button->GetSize().x, tPos.y + pMap2Button->GetSize().y);

	((CUIButton*)pMap2Button)->SetTag("Map2Button");
	((CUIButton*)pMap2Button)->AddCallback<CLobbyScene>(&CLobbyScene::MapSellectCallback, this);

	pMap2Button->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pMap2Button);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pMap2Button);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pMap2Button);

	pUILayer->AddObject(pMap2Button);
	SAFE_RELEASE(pMap2Button);

	// mini image
	CObj* pMap2 = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Map2Image");

	pMap2->SetPos(477.f, 342.f);
	pMap2->SetTexture("Map2Image", L"02.Lobby/Lobby_Image_Map_1.bmp");
	pMap2->SetEnable(false);

	pUILayer->AddObject(pMap2);
	SAFE_RELEASE(pMap2);
	
	// StartButton
	CObj* pStartButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("StartButton");

	pStartButton->SetPos(620.f, 513.f);
	pStartButton->SetTexture("StartButton", L"02.Lobby/Lobby_Button_Start.bmp", true, RGB(0, 255, 0));
	pStartButton->SetAnimation("LogoButton.anm");

	tPos = pStartButton->GetPos() - pStartButton->GetPivot() * pStartButton->GetSize();
	pRC = CColliderRect::Create("StartButton", tPos.x, tPos.y, tPos.x + pStartButton->GetSize().x, tPos.y + pStartButton->GetSize().y);

	pStartButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pStartButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pStartButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pStartButton);

	((CUIButton*)pStartButton)->AddCallback<CLobbyScene>(&CLobbyScene::StartButtonCallback, this);

	pUILayer->AddObject(pStartButton);
	SAFE_RELEASE(pStartButton);

	return true;
}

void CLobbyScene::Input(float fTime)
{
}

void CLobbyScene::Update(float fTime)
{
}

void CLobbyScene::Render(HDC hDC, float fTime)
{
}

void CLobbyScene::MapSellectCallback(CUIButton * pButton)
{
	CLayer* pUILayer = m_pScene->FindLayer("UILayer");

	if (!pUILayer)
		return;

	string ImageTag1, ImageTag2;

	if (pButton->GetTag() == "Map1Button")
	{
		ImageTag1 = "Map1Image";
		ImageTag2 = "Map2Image";
		m_iSellectMap = 1;
	}

	else
	{
		ImageTag1 = "Map2Image";
		ImageTag2 = "Map1Image";
		m_iSellectMap = 2;
	}

	CObj* pImage1 = pUILayer->FindObjectFromTag(ImageTag1);

	pImage1->SetEnable(true);

	SAFE_RELEASE(pImage1);

	CObj* pImage2 = pUILayer->FindObjectFromTag(ImageTag2);

	pImage2->SetEnable(false);

	SAFE_RELEASE(pImage2);
}

void CLobbyScene::StartButtonCallback(CUIButton * pButton)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->CreateScene();

	if (m_iSellectMap == 1)
	{
		pScene->CreateSceneScript<CVillageMap>();
	}

	else if (m_iSellectMap == 2)
	{
		//pScene->CreateSceneScript<CLobbyScene>();
	}

	// 선택된 캐릭터 파일 입출력 or 전역변수 생성

	GET_SINGLE(CSceneManager)->SetNextScene(pScene);
}
