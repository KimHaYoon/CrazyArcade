#include "VillageMap.h"
#include "Layer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "../Object/Obj.h"
#include "../Object/ObjectManager.h"
#include "../Object/Background.h"

CVillageMap::CVillageMap()
{
}

CVillageMap::~CVillageMap()
{
}

bool CVillageMap::Init()
{
	CLayer* pBackLayer = m_pScene->FindLayer("BackgroundLayer");

	// Stage Default Background 
	CObj* pBackground = GET_SINGLE(CObjectManager)->CreateObject<CBackground>("InGameBG");
	pBackground->SetTexture("InGameBG", L"03.InGame/InGame_Bg.bmp");
	pBackLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	return true;
}

void CVillageMap::Input(float fTime)
{
}

void CVillageMap::Update(float fTime)
{
}

void CVillageMap::Render(HDC hDC, float fTime)
{
}

void CVillageMap::ExitButtonCallback(CUIButton * pButton)
{
}
