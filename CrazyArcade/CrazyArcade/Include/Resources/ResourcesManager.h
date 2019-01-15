#pragma once

#include "../GameFramework.h"

class CResourcesManager
{
private:
	HINSTANCE	m_hInst;
	HDC			m_hDC;

private:
	unordered_map<string, class CTexture*>	m_mapTexture;

public:
	bool Init(HINSTANCE hInst, HDC hDC);
	class CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName,
		bool bColorKey = false, COLORREF dwColorKey = RGB(255, 0, 255),
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* LoadTextureFromFullPath(const string& strKey, const wchar_t* pFileName,
		bool bColorKey = false, COLORREF dwColorKey = RGB(255, 0, 255));
	class CTexture* FindTexture(const string& strKey);

	DECLARE_SINGLE(CResourcesManager)
};

