#include "UITimer.h"
#include "../Animation/Animation.h"

CUITimer::CUITimer()
{
}

CUITimer::CUITimer(const CUITimer & obj)
{
}


CUITimer::~CUITimer()
{
}

bool CUITimer::Init()
{
	SetTexture("Number", L"03.InGame/InGame_Image_Num.bmp", true, RGB(0, 0, 255));
	SetPivot(0.f, 0.f);
	SetAnimation("TimeUI.anm");
	m_pAnimation->SetAnimationStart(false);
	return true;
}

void CUITimer::Input(float fTime)
{
}

void CUITimer::Update(float fTime)
{
}

void CUITimer::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CUITimer * CUITimer::Clone()
{
	return new CUITimer(*this);
}

void CUITimer::SetNumber(int num)
{
	m_pAnimation->SetFrameX(num);
}
