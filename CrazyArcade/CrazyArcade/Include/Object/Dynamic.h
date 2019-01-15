#pragma once
#include "Obj.h"
class CDynamic :
	public CObj
{
protected:
	CDynamic();
	CDynamic(const CDynamic& dynamic);
	virtual ~CDynamic() = 0;

protected:
	float		m_fSpeed;
	float		m_fAngle;

public:
	void SetSpeed(float fSpeed);
	void SetAngle(float fAngle);
	void Move(float fTime);
	void MoveDown(float fTime);
	void MoveUp(float fTime);
	void MoveLeft(float fTime);
	void MoveRight(float fTime);

public:
	float GetSpeed() const
	{
		return m_fSpeed;
	}

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CDynamic* Clone() = 0;
};

