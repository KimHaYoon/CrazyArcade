#include "VillageMap.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "LobbyScene.h"
#include "../Object/Obj.h"
#include "../Object/ObjectManager.h"
#include "../Object/Background.h"
#include "../Object/UITimer.h"
#include "../Object/UIButton.h"
#include "../Object/Character.h"
#include "../Collider/ColliderRect.h"

CVillageMap::CVillageMap() : 
	m_fGameLimitTime(90.f),
	m_iMinute(0),
	m_iTenSec(0),
	m_iOneSec(0),
	m_iCharacter(0)
{
}

CVillageMap::~CVillageMap()
{
}

bool CVillageMap::Init()
{
	CLayer* pBackLayer = m_pScene->FindLayer("BackgroundLayer");
	CLayer* pUILayer = m_pScene->FindLayer("UILayer");
	CLayer* pLayer = m_pScene->FindLayer("DefaultLayer");

	// Stage Default Background 
	CObj* pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("InGameBG");
	pBackground->SetTexture("InGameBG", L"03.InGame/InGame_Bg.bmp");
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	// Map Image
	pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Map1_Back");
	pBackground->SetTexture("Map1_Back", L"03.InGame/Map_1/Map1_Back.bmp");
	pBackground->SetPos(20.f, 40.f);
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	// Timer 
	CObj* pTimer = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("Min");
	pTimer->SetPos(720.f, 76.f);
	pUILayer->AddObject(pTimer);
	SAFE_RELEASE(pTimer);

	pTimer = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("TenSec");
	pTimer->SetPos(740.f, 76.f);
	pUILayer->AddObject(pTimer);
	SAFE_RELEASE(pTimer);

	pTimer = GET_SINGLE(CObjectManager)->CreateObject<CUITimer>("OneSec");
	pTimer->SetPos(750.f, 76.f);
	pUILayer->AddObject(pTimer);
	SAFE_RELEASE(pTimer);

	// Exit Button
	CObj* pExitButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("ExitButton");

	pExitButton->SetPos(717.f, 577.f);
	pExitButton->SetTexture("ExitButton", L"03.InGame/InGame_Button_Out.bmp", true, RGB(0, 255, 0));
	pExitButton->SetAnimation("LogoButton.anm");
	POSITION tPos = pExitButton->GetPos() - pExitButton->GetPivot() * pExitButton->GetSize();

	CColliderRect* pRC = CColliderRect::Create("ExitButton", tPos.x, tPos.y, tPos.x + pExitButton->GetSize().x, tPos.y + pExitButton->GetSize().y);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pExitButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pExitButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pExitButton);

	((CUIButton*)pExitButton)->SetTag("ExitButton");
	((CUIButton*)pExitButton)->AddCallback<CVillageMap>(&CVillageMap::ExitButtonCallback, this);

	pExitButton->AddCollider(pRC);

	pUILayer->AddObject(pExitButton);
	SAFE_RELEASE(pExitButton);

	// Dao
	CObj* pCharacter = GET_SINGLE(CObjectManager)->CreateObject<CCharacter>("Character");
	pCharacter->SetPos(100.f, 100.f);
	pCharacter->SetTexture("Dao", L"03.InGame/Character/Dao.bmp", true, RGB(0, 255, 0));

	pLayer->AddObject(pCharacter);
	SAFE_RELEASE(pCharacter);

	return true;
}

void CVillageMap::Input(float fTime)
{
}

void CVillageMap::Update(float fTime)
{
	m_iMinute = m_fGameLimitTime / 60;
	int iSec = m_fGameLimitTime - (m_iMinute * 60);
	m_iTenSec = iSec / 10;
	m_iOneSec = iSec % 10;

	CLayer* pUILayer = m_pScene->FindLayer("UILayer");
	CObj* pTimer = pUILayer->FindObjectFromTag("Min");
	((CUITimer*)pTimer)->SetNumber(m_iMinute);
	SAFE_RELEASE(pTimer);

	pTimer = pUILayer->FindObjectFromTag("TenSec");
	((CUITimer*)pTimer)->SetNumber(m_iTenSec);
	SAFE_RELEASE(pTimer);

	pTimer = pUILayer->FindObjectFromTag("OneSec");
	((CUITimer*)pTimer)->SetNumber(m_iOneSec);
	SAFE_RELEASE(pTimer);

	m_fGameLimitTime -= fTime;
}

void CVillageMap::Render(HDC hDC, float fTime)
{
}

void CVillageMap::ExitButtonCallback(CUIButton * pButton)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->CreateScene();

	pScene->CreateSceneScript<CLobbyScene>();

	GET_SINGLE(CSceneManager)->SetNextScene(pScene);
}

void CVillageMap::SetCharacter(UINT iNum)
{
	m_iCharacter = iNum;
}
