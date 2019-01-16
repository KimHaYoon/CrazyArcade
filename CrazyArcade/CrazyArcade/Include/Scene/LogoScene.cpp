#include "LogoScene.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "LobbyScene.h"
#include "../Core.h"
#include "../Collider/ColliderRect.h"
#include "../Object/Obj.h"
#include "../Object/ObjectManager.h"
#include "../Object/Background.h"
#include "../Object/UIButton.h"


CLogoScene::CLogoScene()
{
}


CLogoScene::~CLogoScene()
{
}

bool CLogoScene::Init()
{
	CLayer* pBackLayer = m_pScene->FindLayer("BackgroundLayer");
	CLayer*	pUILayer = m_pScene->FindLayer("UILayer");

	// Logo Background 
	CObj* pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Background");
	pBackground->SetTexture("Logo", L"01.Logo/Logo_Bg.bmp");
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	// 게임시작 버튼
	CObj*	pButton = GET_SINGLE(CObjectManager)->CreateObject<CUIButton>("StartButton");

	pButton->SetPos(RESOLUTION_W / 2.f, RESOLUTION_H / 2.f + 155);
	pButton->SetTexture("LogoButton", L"01.Logo/Logo_Button_Start.bmp", true, RGB(0, 255, 0));
	pButton->SetAnimation("LogoButton.anm");

	POSITION tPos = pButton->GetPos() - pButton->GetPivot() * pButton->GetSize();

	CColliderRect* pRC = CColliderRect::Create("StartButton", tPos.x, tPos.y + 10, tPos.x + pButton->GetSize().x, tPos.y + pButton->GetSize().y - 10);

	pButton->AddCollider(pRC);

	pRC->AddCollisionFunction<CUIButton>(CFT_ENTER, &CUIButton::CollisionEnter, (CUIButton*)pButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_TRIGGER, &CUIButton::CollisionTrigger, (CUIButton*)pButton);
	pRC->AddCollisionFunction<CUIButton>(CFT_LEAVE, &CUIButton::CollisionLeave, (CUIButton*)pButton);

	((CUIButton*)pButton)->AddCallback<CLogoScene>(&CLogoScene::StartButtonCallback, this);

	pUILayer->AddObject(pButton);

	SAFE_RELEASE(pButton);

	return true;
}

void CLogoScene::Input(float fTime)
{
}

void CLogoScene::Update(float fTime)
{
}

void CLogoScene::Render(HDC hDC, float fTime)
{
}

void CLogoScene::StartButtonCallback(CUIButton * pButton)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->CreateScene();

	pScene->CreateSceneScript<CLobbyScene>();

	GET_SINGLE(CSceneManager)->SetNextScene(pScene);
}
