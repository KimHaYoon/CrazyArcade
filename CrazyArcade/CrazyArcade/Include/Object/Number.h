#pragma once
#include "Obj.h"

class CNumber :
	public CObj
{
protected:
	friend class CObjectManager;

protected:
	CNumber();
	CNumber(const CNumber& obj);
	virtual ~CNumber();

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CNumber* Clone();
};

