#pragma once
#include "Obj.h"

class CUITimer :
	public CObj
{
private:
	friend class CObjectManager;

private:
	CUITimer();
	CUITimer(const CUITimer& obj);
	virtual ~CUITimer();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CUITimer* Clone();

public:
	void SetNumber(int num);
};

