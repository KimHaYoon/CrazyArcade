#include "Obj.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourcesManager.h"
#include "../Animation/Animation.h"
#include "../Core/Camera.h"
#include "../Core.h"
#include "../Collider/Collider.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Layer.h"

CObj::CObj()	:
	m_pTexture(NULL),
	m_pAnimation(NULL),
	m_pLayer(NULL),
	m_pScene(NULL),
	m_bEnable(true),
	m_bAlive(true),
	m_bUseGravity(false),
	m_bCamera(true),
	m_fGravityTime(0.f),
	m_bCustomSize(false)
{
	m_tPivot = POSITION(0.5f, 0.5f);
}

CObj::CObj(const CObj & obj)
{
	// ��������
	*this = obj;
	m_iRefCount = 1;
	m_fGravityTime = 0.f;

	if (m_pTexture)
		m_pTexture->AddRef();

	if (m_pAnimation)
		m_pAnimation = m_pAnimation->Clone();

	m_ColliderList.clear();

	list<CCollider*>::const_iterator	iter;
	list<CCollider*>::const_iterator	iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		CCollider*	pCollider = (*iter)->Clone();
		pCollider->SetObj(this);
		m_ColliderList.push_back(pCollider);
	}
}

CObj::~CObj()
{
	Safe_Release_VecList(m_ColliderList);
	SAFE_DELETE(m_pAnimation);
	SAFE_RELEASE(m_pTexture);
}

CTexture * CObj::GetTexture() const
{
	if (m_pTexture)
		m_pTexture->AddRef();
	return m_pTexture;
}

CAnimation * CObj::GetAnimation() const
{
	return m_pAnimation;
}

void CObj::SetSizeFromImageSize()
{
	if (!m_pTexture)
		return;

	m_tSize.x = m_pTexture->GetWidth();
	m_tSize.y = m_pTexture->GetHeight();
}

void CObj::SetSizeFromAnimationFrameSize()
{
	if (!m_pAnimation)
		return;

	m_tSize.x = m_pAnimation->GetFrameWidth();
	m_tSize.y = m_pAnimation->GetFrameHeight();
}

void CObj::SetAnimationFrameSize()
{
	if (!m_pAnimation)
		return;

	m_tSize.x = m_pAnimation->GetFrameWidth();
	m_tSize.y = m_pAnimation->GetFrameHeight();
}

void CObj::SetScene(CScene * pScene)
{
	m_pScene = pScene;

	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->SetScene(m_pScene);
	}
}

void CObj::SetLayer(CLayer * pLayer)
{
	m_pLayer = pLayer;

	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->SetLayer(m_pLayer);
	}
}

void CObj::SetTexture(CTexture * pTexture)
{
	SAFE_RELEASE(m_pTexture);

	m_pTexture = pTexture;
	m_pTexture->AddRef();

	if (m_pAnimation)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		if (!m_bCustomSize)
			SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}
}

void CObj::SetTexture(const string & strKey, const wchar_t * pFileName, bool bColorKey,
	COLORREF dwColorKey, const string & strPathKey)
{
	SAFE_RELEASE(m_pTexture);

	if (pFileName)
		m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, bColorKey, dwColorKey, strPathKey);

	else
		m_pTexture = GET_SINGLE(CResourcesManager)->FindTexture(strKey);

	if (m_pAnimation)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}

	else
	{
		if(!m_bCustomSize)
			SetSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
	}
}

void CObj::SetTextureFromFullPath(const string & strKey, const wchar_t * pFullPath, bool bColorKey, COLORREF dwColorKey)
{
	SAFE_RELEASE(m_pTexture);

	if (pFullPath)
		m_pTexture = GET_SINGLE(CResourcesManager)->LoadTextureFromFullPath(strKey, pFullPath, bColorKey, dwColorKey);
	else
		m_pTexture = GET_SINGLE(CResourcesManager)->FindTexture(strKey);

	if (m_pAnimation)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		if (!m_bCustomSize)
			SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}

	else
	{
		if (!m_bCustomSize)
			SetSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
	}
}

void CObj::SetAnimation(CAnimation * pAnimation)
{
	SAFE_DELETE(m_pAnimation);
	m_pAnimation = pAnimation;

	if (m_pTexture)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		if (!m_bCustomSize)
			SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}
}

void CObj::SetAnimation(const char * pName, ANIMATION_TYPE eType, 
	ANIMATION_OPTION eOption, UINT iWidth, UINT iHeight, UINT iFrameMaxX,
	UINT iFrameMaxY, float fLimitTime)
{
	SAFE_DELETE(m_pAnimation);
	m_pAnimation = CAnimation::Create(pName, eType, eOption, iWidth, iHeight,
		iFrameMaxX, iFrameMaxY, fLimitTime);

	if (m_pTexture)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		if (!m_bCustomSize)
			SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}
}

void CObj::SetAnimation(const char * pFileName, const string & strPathKey)
{
	SAFE_DELETE(m_pAnimation);
	m_pAnimation = CAnimation::Create(pFileName, strPathKey);

	if (m_pTexture)
	{
		m_pAnimation->SetTextureSize(m_pTexture->GetWidth(), m_pTexture->GetHeight());
		if (!m_bCustomSize)
			SetSize(m_pAnimation->GetFrameWidth(), m_pAnimation->GetFrameHeight());
	}
}

void CObj::AddCollider(CCollider * pCollider)
{
	pCollider->SetScene(m_pScene);
	pCollider->SetLayer(m_pLayer);
	pCollider->SetObj(this);
	m_ColliderList.push_back(pCollider);
}

bool CObj::CheckCollider()
{
	return !m_ColliderList.empty();
}

CCollider * CObj::FindCollider(const string & strTag)
{
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
			return *iter;
	}

	return NULL;
}

void CObj::DontDestroyOnLoad()
{
	CScene*	pNextScene = GET_SINGLE(CSceneManager)->GetNextScene();

	CLayer*	pLayer = pNextScene->FindLayer("DefaultLayer");

	pLayer->AddObject(this);
}

void CObj::Update(float fTime)
{
	if (m_pAnimation)
		m_pAnimation->Update(fTime);

	// �߷� ������Ʈ
	if (m_bUseGravity)
	{
		m_fGravityTime += fTime;
		float	fMoveY = GRAVITY * (m_fGravityTime * m_fGravityTime);

		//if (fMoveY >= 1.f)
			//fMoveY = 1.f;

		m_tPos.y += fMoveY;
	}

	// �浹ü ������Ʈ
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(fTime);
	}

}

void CObj::Render(HDC hDC, float fTime)
{
	POSITION	tPos = m_tPos;
	
	if (m_bCamera)
		tPos -= GET_SINGLE(CCamera)->GetPos();

	else
		int a = 10;

	if (tPos.x + (1.f - m_tPivot.x) * m_tSize.x < 0 ||
		tPos.x - m_tPivot.x * m_tSize.x > RESOLUTION_W ||
		tPos.y + (1.f - m_tPivot.y) * m_tSize.y < 0 ||
		tPos.y - m_tPivot.y * m_tSize.y > RESOLUTION_H)
		return;

	if (m_pTexture)
	{
		if (!m_pTexture->GetColorKeyEnable())
		{
			// BitBlt �Լ��� Ư�� DC�� ����� �Ǵ� DC�� ������ִ� �Լ��̴�.
			// 1�� ���ڴ� ����� �Ǵ� DC�� ���� DC���ٰ� ����ϰ� �ȴ�.
			// 2��, 3�� ���ڴ� x, y�ε� �� ���� ��� ����� DC���� ��ǥ�� �������ش�.
			// ��ǥ�� �� ��� ���� �ȴ�.
			// 4��, 5�� ���ڴ� ����, ������ ��� ũ���̴�.
			// 2, 3�� ������ ��ǥ�κ��� 4��, 5�� ������ ����, ���� ũ�⸸ŭ
			// 6�����ڿ� ������ DC�� �׷�����.
			// 7, 8�� ���ڴ� �̹����� ��� �������� �����Ѵ�.
			int	x, y;
			x = tPos.x - m_tPivot.x * m_tSize.x;
			y = tPos.y - m_tPivot.y * m_tSize.y;

			UINT	iWidth, iHeight;
			iWidth = m_pTexture->GetWidth();
			iHeight = m_pTexture->GetHeight();

			UINT	iImageX = 0, iImageY = 0;

			if (m_pAnimation)
			{
				iWidth = m_pAnimation->GetFrameWidth();
				iHeight = m_pAnimation->GetFrameHeight();

				iImageX = m_pAnimation->GetAnimationInfo().iFrameX * iWidth;
				iImageY = m_pAnimation->GetAnimationInfo().iFrameY * iHeight;
			}

			if (m_bCustomSize)
			{
				StretchBlt(hDC, x, y, m_tCustomSize.x, m_tCustomSize.y, m_pTexture->GetMemDC(), iImageX, iImageY, iWidth, iHeight, SRCCOPY);
			}

			else
			{
				BitBlt(hDC, x, y, iWidth, iHeight, m_pTexture->GetMemDC(), iImageX, iImageY, SRCCOPY);
			}
		}

		else
		{
			// ColorKey�� �����ϰ� ����Ѵ�.
			int	x, y;
			x = tPos.x - m_tPivot.x * m_tSize.x;
			y = tPos.y - m_tPivot.y * m_tSize.y;

			UINT	iWidth, iHeight;
			iWidth = m_pTexture->GetWidth();
			iHeight = m_pTexture->GetHeight();

			UINT	iImageX = 0, iImageY = 0;

			if (m_pAnimation)
			{
				iWidth = m_pAnimation->GetFrameWidth();
				iHeight = m_pAnimation->GetFrameHeight();

				iImageX = m_pAnimation->GetAnimationInfo().iFrameX * iWidth;
				iImageY = m_pAnimation->GetAnimationInfo().iFrameY * iHeight;
			}

			if (m_bCustomSize)
			{
				TransparentBlt(hDC, x, y, m_tCustomSize.x, m_tCustomSize.y,
					m_pTexture->GetMemDC(), iImageX, iImageY, iWidth, iHeight,
					m_pTexture->GetColorKey());
			}

			else
			{
				TransparentBlt(hDC, x, y, iWidth, iHeight,
					m_pTexture->GetMemDC(), iImageX, iImageY, iWidth, iHeight,
					m_pTexture->GetColorKey());
			}
		}
	}

	// �浹ü ������Ʈ
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, fTime);
	}
}
