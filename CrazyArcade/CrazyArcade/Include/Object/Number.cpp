#include "Number.h"
#include "../Animation/Animation.h"


CNumber::CNumber()
{
}

CNumber::CNumber(const CNumber & obj) :
	CObj(obj)
{
}


CNumber::~CNumber()
{
}

bool CNumber::Init()
{
	SetTexture("Number", L"03.InGame/InGame_Image_Num.bmp", true, RGB(0, 0, 255));
	SetPivot(0.f, 0.f);
	SetAnimation("TimeUI.anm");
	m_pAnimation->SetAnimationStart(false);

	return true;
}

void CNumber::Input(float fTime)
{
}

void CNumber::Update(float fTime)
{
}

void CNumber::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CNumber * CNumber::Clone()
{
	return new CNumber(*this);
}
