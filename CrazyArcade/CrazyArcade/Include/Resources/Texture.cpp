#include "Texture.h"
#include "../Core/PathManager.h"

CTexture::CTexture()
{
	m_dwColorKey = RGB(255, 0, 255);
}

CTexture::~CTexture()
{
	// �׸��� ������ ������ ������ �ִ� ������ �������ش�.
	SelectObject(m_hMemDC, m_hOldBmp);

	// �ε��� ��Ʈ�� �ڵ��� �����ش�.
	DeleteObject(m_hBmp);

	// �޸� DC�� �����ش�.
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(const string& strKey, HINSTANCE hInst, HDC hDC, const wchar_t * pFileName, bool bColorKey,
	COLORREF dwColorKey, const string & strPathKey)
{
	m_strPath = GET_SINGLE(CPathManager)->FindPathFromWString(strPathKey);
	m_strFileName = pFileName;
	m_strFullPath = m_strPath + m_strFileName;

	return LoadTextureFromFullPath(strKey, hInst, hDC, m_strFullPath.c_str(), bColorKey, dwColorKey);
}

bool CTexture::LoadTextureFromFullPath(const string & strKey, HINSTANCE hInst, HDC hDC, const wchar_t* pFullPath, bool bColorKey, COLORREF dwColorKey)
{
	m_strKey = strKey;
	m_dwColorKey = dwColorKey;
	m_bColorKey = bColorKey;

	m_hBmp = (HBITMAP)LoadImageW(hInst, pFullPath, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);

	m_hMemDC = CreateCompatibleDC(hDC);

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);

	GetObject(m_hBmp, sizeof(m_tInfo), &m_tInfo);

	return true;
}
