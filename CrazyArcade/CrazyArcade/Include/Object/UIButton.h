#pragma once
#include "Obj.h"

typedef struct _tagButtonFunction
{
	function<void(class CUIButton*)> func;
	bool	bEnable;
}BUTTONFUNCTION, *PBUTTONFUNCTION;

class CUIButton :
	public CObj
{
protected:
	friend class CObjectManager;

protected:
	CUIButton();
	CUIButton(const CUIButton& button);
	virtual ~CUIButton();

protected:
	BUTTON_STATE	m_eState;
	BUTTONFUNCTION	m_tCallback;

public:
	void AddCallback(void(*pFunc)(CUIButton*));
	template <typename T>
	void AddCallback(void (T::*pFunc)(CUIButton*), T* pObj)
	{
		m_tCallback.bEnable = true;
		// bind �Լ��� �̿��ؼ� function ��ü�� ������� �� �ִ�. �Ϲ� �����Լ��� �Լ� �ּҸ� �־��ְ�
		// ������� �� ������ ����Լ��� �Լ��ּҿ� ȣ�� ��ü�� ��� �־��־�� �Ѵ�.
		m_tCallback.func = bind(pFunc, pObj, placeholders::_1);
	}

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CUIButton* Clone();

public:
	void CollisionEnter(class CCollider* p1, class CCollider* p2);
	void CollisionTrigger(class CCollider* p1, class CCollider* p2);
	void CollisionLeave(class CCollider* p1, class CCollider* p2);
};

