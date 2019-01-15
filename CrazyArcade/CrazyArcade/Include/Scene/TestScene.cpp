#include "TestScene.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "LobbyScene.h"
#include "../Object/Obj.h"
#include "../Object/ObjectManager.h"
#include "../Object/Background.h"

CTestScene::CTestScene()
{
}

CTestScene::~CTestScene()
{
}

bool CTestScene::Init()
{
	CLayer* pBackLayer = m_pScene->FindLayer("BackgroundLayer");

	// Logo Background 
	CObj* pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("Background");
	pBackground->SetTexture("Logo", L"Logo_Bg.bmp");
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	return true;
}

void CTestScene::Input(float fTime)
{
}

void CTestScene::Update(float fTime)
{
}

void CTestScene::Render(HDC hDC, float fTime)
{
}

void CTestScene::StartButtonCallback(CUIButton * pButton)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->CreateScene();

	pScene->CreateSceneScript<CLobbyScene>();

	GET_SINGLE(CSceneManager)->SetNextScene(pScene);
}
