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
#include "../Object/UITimer.h"
#include "../Collider/ColliderRect.h"
#include "../Core/PathManager.h"

CLobbyScene::CLobbyScene() : 
	m_iSellectMap(0),
	m_iCharacter(0)
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
	
	// item 
	// Bazzi
	// 바늘
	CObj* pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Needle");

	pItemButton->SetPos(60.f, 255.f);
	pItemButton->SetTexture("Needle", L"02.Lobby/Lobby_QButton.bmp");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Needle", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 다트
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Dart");

	pItemButton->SetPos(97.f, 255.f);
	pItemButton->SetTexture("Dart", L"02.Lobby/Lobby_WButton.bmp");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Dart", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 압정 tack
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Tack");

	pItemButton->SetPos(134.f, 255.f);
	pItemButton->SetTexture("Tack", L"02.Lobby/Lobby_EButton.bmp");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Tack", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 바나나
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Banana");

	pItemButton->SetPos(171.f, 255.f);
	pItemButton->SetTexture("Banana", L"02.Lobby/Lobby_RButton.bmp");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Banana", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// Dao=======================================================================================================================================================
	// 바늘
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Needle1");

	pItemButton->SetPos(250.f, 255.f);
	pItemButton->SetTexture("Needle");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Needle", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 다트
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Dart1");

	pItemButton->SetPos(287.f, 255.f);
	pItemButton->SetTexture("Dart");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Dart", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 압정 tack
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Tack1");

	pItemButton->SetPos(323.f, 255.f);
	pItemButton->SetTexture("Tack");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Tack", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 바나나
	pItemButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Banana1");

	pItemButton->SetPos(360.f, 255.f);
	pItemButton->SetTexture("Banana");
	tPos = pItemButton->GetPos() - pItemButton->GetPivot() * pItemButton->GetSize();
	pRC = CColliderRect::Create("Banana", tPos.x, tPos.y, tPos.x + pItemButton->GetSize().x, tPos.y + pItemButton->GetSize().y);

	((CUIButton*)pItemButton)->AddCallback<CLobbyScene>(&CLobbyScene::ItemButtonCallback, this);

	pItemButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pItemButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pItemButton);

	pUILayer->AddObject(pItemButton);
	SAFE_RELEASE(pItemButton);

	// 아이템 개수 
	CObj* Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("NeedleNum");
	Number->SetPos(65.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("DartNum");
	Number->SetPos(102.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("TackNum");
	Number->SetPos(139.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("BananaNum");
	Number->SetPos(176.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	// Dao=======================================================================================================================================================
	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("NeedleNum1");
	Number->SetPos(255.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("DartNum1");
	Number->SetPos(292.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("TackNum1");
	Number->SetPos(328.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	Number = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("BananaNum1");
	Number->SetPos(365.f, 255.f);
	pUILayer->AddObject(Number);
	SAFE_RELEASE(Number);

	// 캐릭터 선택창
	CObj* pCharacter = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Bazzi");
	pCharacter->SetPos(115.f, 185.f);
	pCharacter->SetSize(150.f, 100.f);
	tPos = pCharacter->GetPos() - pCharacter->GetPivot() * pCharacter->GetSize();
	pRC = CColliderRect::Create("Bazzi", tPos.x, tPos.y, tPos.x + pCharacter->GetSize().x, tPos.y + pCharacter->GetSize().y);

	((CUIButton*)pCharacter)->AddCallback<CLobbyScene>(&CLobbyScene::SelectCharacterCallback, this);

	pCharacter->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pCharacter);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pCharacter);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pCharacter);

	pUILayer->AddObject(pCharacter);
	SAFE_RELEASE(pCharacter);

	pCharacter = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("Dao");
	pCharacter->SetPos(305.f, 185.f);
	pCharacter->SetSize(150.f, 100.f);
	tPos = pCharacter->GetPos() - pCharacter->GetPivot() * pCharacter->GetSize();
	pRC = CColliderRect::Create("Dao", tPos.x, tPos.y, tPos.x + pCharacter->GetSize().x, tPos.y + pCharacter->GetSize().y);

	((CUIButton*)pCharacter)->AddCallback<CLobbyScene>(&CLobbyScene::SelectCharacterCallback, this);

	pCharacter->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pCharacter);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pCharacter);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pCharacter);

	pUILayer->AddObject(pCharacter);
	SAFE_RELEASE(pCharacter);

	// selectUI
	pCharacter = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Select");
	pCharacter->SetTexture("SelectCharacter", L"02.Lobby/Select.bmp", true);
	pCharacter->SetEnable(false);
	pUILayer->AddObject(pCharacter);
	SAFE_RELEASE(pCharacter);

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
		Save();
		pScene->CreateSceneScript<CVillageMap>();
	}

	else if (m_iSellectMap == 2)
	{
		//pScene->CreateSceneScript<CLobbyScene>();
	}

	// 선택된 캐릭터 파일 입출력 or 전역변수 생성

	GET_SINGLE(CSceneManager)->SetNextScene(pScene);
}

void CLobbyScene::ItemButtonCallback(CUIButton * pButton)
{
	CLayer* pUILayer = m_pScene->FindLayer("UILayer");
	CObj* pNumber = NULL;
	int iCnt = 0;
	int iCharacter = 0;

	if (pButton->GetTag() == "Needle")
	{
		pNumber = pUILayer->FindObjectFromTag("NeedleNum");
		iCnt = 0;
		iCharacter = 0;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Dart")
	{
		pNumber = pUILayer->FindObjectFromTag("DartNum");
		iCnt = 1;
		iCharacter = 0;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Tack")
	{
		pNumber = pUILayer->FindObjectFromTag("TackNum");
		iCnt = 2;
		iCharacter = 0;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Banana")
	{
		pNumber = pUILayer->FindObjectFromTag("BananaNum");
		iCnt = 3;
		iCharacter = 0;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Needle1")
	{
		pNumber = pUILayer->FindObjectFromTag("NeedleNum1");
		iCnt = 0;
		iCharacter = 1;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Dart1")
	{
		pNumber = pUILayer->FindObjectFromTag("DartNum1");
		iCnt = 1;
		iCharacter = 1;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Tack1")
	{
		pNumber = pUILayer->FindObjectFromTag("TackNum1");
		iCnt = 2;
		iCharacter = 1;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	else if (pButton->GetTag() == "Banana1")
	{
		pNumber = pUILayer->FindObjectFromTag("BananaNum1");
		iCnt = 3;
		iCharacter = 1;
		m_iItemCnt[iCharacter][iCnt]++;
	}

	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_iItemCnt[j][i] %= 10;
		}
	}

	((CUITimer*)pNumber)->SetNumber(m_iItemCnt[iCharacter][iCnt]);

	SAFE_RELEASE(pNumber);
}

void CLobbyScene::SelectCharacterCallback(CUIButton * pButton)
{
	if (pButton->GetTag() == "Bazzi")
		m_iCharacter = 0;

	else if (pButton->GetTag() == "Dao")
		m_iCharacter = 1;

	CLayer* pUILayer = m_pScene->FindLayer("UILayer");
	CObj* pObj = pUILayer->FindObjectFromTag("Select");
	pObj->SetPos(pButton->GetPos());
	pObj->SetPivot(0.5f, 0.5f);
	pObj->SetEnable(true);
	SAFE_RELEASE(pObj);
}

void CLobbyScene::Save()
{
	// 선택한 캐릭터
	// 아이템들 개수
	// 선택한 맵

	FILE* pFile = NULL;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(DATA_PATH);

	string strPath;

	if (pPath)
		strPath = pPath;

	strPath += "Player.data";

	fopen_s(&pFile, strPath.c_str(), "wb");

	fwrite(&m_iCharacter, sizeof(m_iCharacter), 1, pFile);
	
	for(int  i = 0; i < 4; ++i)
		fwrite(&m_iItemCnt[m_iCharacter][i], sizeof(m_iItemCnt[m_iCharacter][i]), 1, pFile);

	fwrite(&m_iSellectMap, sizeof(m_iSellectMap), 1, pFile);

	fclose(pFile);
}
