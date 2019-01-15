#pragma once
#include "SceneScript.h"

class CTestScene :
	public CSceneScript
{
private:
	friend class CScene;

private:
	CTestScene();
	virtual ~CTestScene();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);

private:
	void StartButtonCallback(class CUIButton* pButton);
};

