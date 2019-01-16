#include "Character.h"
#include "../Core/Input.h"
#include "../Animation/Animation.h"

CCharacter::CCharacter()
{
}

CCharacter::CCharacter(const CCharacter & character)	:
	CDynamic(character)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	if (!CDynamic::Init())
		return false;

	m_fSpeed = 100.f;

	return true;
}

void CCharacter::Input(float fTime)
{
	CDynamic::Input(fTime);

	if (GET_SINGLE(CInput)->KeyPush("MoveLeft"))
	{
		MoveLeft(fTime);
		m_pAnimation->ChangeAnimation(3);
	}

	if (GET_SINGLE(CInput)->KeyPush("MoveRight"))
	{
		MoveRight(fTime);
		m_pAnimation->ChangeAnimation(2);
	}

	if (GET_SINGLE(CInput)->KeyPush("MoveUp"))
	{
		MoveUp(fTime);
		m_pAnimation->ChangeAnimation(0);
	}

	if (GET_SINGLE(CInput)->KeyPush("MoveDown"))
	{
		MoveDown(fTime);
		m_pAnimation->ChangeAnimation(1);
	}

}

void CCharacter::Update(float fTime)
{
	CDynamic::Update(fTime);

	if (!m_pAnimation && m_pTexture)
		SetAnimation("Dao.anm");
}

void CCharacter::Render(HDC hDC, float fTime)
{
	CDynamic::Render(hDC, fTime);
}

CCharacter * CCharacter::Clone()
{
	return new CCharacter(*this);
}

void CCharacter::SetCharacter(UINT iNum)
{
	m_iCharacter = iNum;

	if(m_iCharacter == 1)
		SetTexture("Dao", L"03.InGame/Character/Dao.bmp", true, RGB(0, 255, 0));
}

void CCharacter::SetItemNum(UINT iItem[4])
{
	for (int i = 0; i < 4; ++i)
	{
		m_iItem[i] = iItem[i];
	}
}
