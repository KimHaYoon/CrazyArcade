#pragma once

#include "../GameFramework.h"

class CSceneManager
{
private:
	class CScene*	m_pCurScene;
	class CScene*	m_pNextScene;

public:
	class CScene* GetNextScene()
	{
		return m_pNextScene;
	}

public:
	bool Init();
	int Input(float fTime);
	int Update(float fTime);
	void Render(HDC hDC, float fTime);
	int ChangeScene();
	void SetNextScene(class CScene* pScene);
	class CScene* CreateScene();
	class CScene* GetCurScene() { return m_pCurScene; }

	DECLARE_SINGLE(CSceneManager)
};

