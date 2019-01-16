#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Input.h"
#include "../Animation/Animation.h"

//#define MAPTOOL

CUIButton::CUIButton()
{
	SetTag("Button");
	m_tCallback.bEnable = false;
}

CUIButton::CUIButton(const CUIButton & button)	:
	CObj(button)
{
	m_eState = BS_NONE;
	m_tCallback.bEnable = false;
}

CUIButton::~CUIButton()
{
}

void CUIButton::AddCallback(void(*pFunc)(CUIButton *))
{
	m_tCallback.bEnable = true;
	m_tCallback.func = bind(pFunc, placeholders::_1);
}

bool CUIButton::Init()
{
	m_eState = BS_NONE;
	DisableCamera();
	
	return true;
}

void CUIButton::Input(float fTime)
{
}

void CUIButton::Update(float fTime)
{
	CObj::Update(fTime);
}

void CUIButton::Render(HDC hDC, float fTime)
{
	if (m_pAnimation)
	{
		m_pAnimation->SetFrameX((UINT)m_eState);
	}

	CObj::Render(hDC, fTime);
}

CUIButton * CUIButton::Clone()
{
	return new CUIButton(*this);
}

void CUIButton::CollisionEnter(CCollider * p1, CCollider * p2)
{
	if (p2->GetTag() == "Mouse")
		m_eState = BS_MOUSEON;
}

void CUIButton::CollisionTrigger(CCollider * p1, CCollider * p2)
{
	if (p2->GetTag() == "Mouse")
	{
		m_eState = BS_MOUSEON;

#ifdef MAPTOOL
		if (KEYDOWN("MouseLButton") || KEYPUSH("MouseLButton"))
		{
			m_eState = BS_CLICK;
			if (m_tCallback.bEnable)
				m_tCallback.func(this);
		}

#else
		if (KEYDOWN("MouseLButton"))
		{
			m_eState = BS_CLICK;
			if (m_tCallback.bEnable)
				m_tCallback.func(this);
		}
#endif // MAPTOOL
	}
}

void CUIButton::CollisionLeave(CCollider * p1, CCollider * p2)
{
	m_eState = BS_NONE;
}
