#include "Background.h"



CBackground::CBackground()
{
}

CBackground::CBackground(const CBackground & back) :
	CObj(back)
{
}


CBackground::~CBackground()
{
}

bool CBackground::Init()
{
	SetPos(0.f, 0.f);
	SetPivot(0.f, 0.f);

	return true;
}

void CBackground::Input(float fTime)
{
}

void CBackground::Update(float fTime)
{
}

void CBackground::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CBackground * CBackground::Clone()
{
	return new CBackground(*this);
}
