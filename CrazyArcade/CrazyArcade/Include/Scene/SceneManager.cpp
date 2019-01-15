#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "LogoScene.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()	:
	m_pCurScene(NULL),
	m_pNextScene(NULL)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pCurScene);
}

bool CSceneManager::Init()
{
	m_pCurScene = CreateScene();

	m_pCurScene->CreateSceneScript<CLogoScene>();

	return true;
}

int CSceneManager::Input(float fTime)
{
	m_pCurScene->Input(fTime);

	return 0;
}

int CSceneManager::Update(float fTime)
{
	m_pCurScene->Update(fTime);

	return ChangeScene();
}

void CSceneManager::Render(HDC hDC, float fTime)
{
	m_pCurScene->Render(hDC, fTime);
}

int CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pCurScene);

		m_pCurScene = m_pNextScene;
		m_pNextScene = NULL;

		return SC_CHANGE;
	}

	return SC_NONE;
}

void CSceneManager::SetNextScene(CScene * pScene)
{
	m_pNextScene = pScene;
}

CScene * CSceneManager::CreateScene()
{
	CScene* pScene = new CScene;

	if (!pScene->Init())
	{
		SAFE_DELETE(pScene);
		return NULL;
	}

	return pScene;
}
