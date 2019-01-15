#pragma once
#include "Obj.h"

class CBackground :
	public CObj
{
protected:
	friend class CObjectManager;

protected:
	CBackground();
	CBackground(const CBackground& back);
	virtual ~CBackground();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CBackground* Clone();
};

