#pragma once
#include "SceneScript.h"

class CLobbyScene :
	public CSceneScript
{
private:
	friend class CScene;

private:
	CLobbyScene();
	virtual ~CLobbyScene();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);

private:
	UINT	m_iSellectMap;

private:
	void MapSellectCallback(class CUIButton* pButton);
	void StartButtonCallback(class CUIButton* pButton);
};

