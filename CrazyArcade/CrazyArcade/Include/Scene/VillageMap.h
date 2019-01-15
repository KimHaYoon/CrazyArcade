#pragma once
#include "SceneScript.h"

class CVillageMap :
	public CSceneScript
{
private:
	friend class CScene;

private:
	CVillageMap();
	virtual ~CVillageMap();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);

private:
	void ExitButtonCallback(class CUIButton* pButton);

private:
	float	m_fGameLimitTime;
	int		m_iMinute;
	int		m_iTenSec;
	int		m_iOneSec;
};

