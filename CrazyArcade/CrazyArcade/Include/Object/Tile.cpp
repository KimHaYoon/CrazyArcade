#include "Tile.h"
#include "../Core.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourcesManager.h"

CTile::CTile()
{
}

CTile::CTile(const CTile & tile)	:
	CObj(tile)
{
	m_tTileInfo = tile.m_tTileInfo;
	m_eEdit = tile.m_eEdit;
	m_eFlag = tile.m_eFlag;
	m_eTileImage = tile.m_eTileImage;
	m_bAnimationEnable = tile.m_bAnimationEnable;
	m_bTileBreak = tile.m_bTileBreak;
}

CTile::~CTile()
{
}

bool CTile::Init()
{
	m_eEdit = EM_FLAG;
	m_eFlag = TF_NONE;
	m_eTileImage = TI_NONE;
	m_bAnimationEnable = false;
	m_bTileBreak = false;
	return true;
}

void CTile::Input(float fTime)
{
}

void CTile::Update(float fTime)
{
	CObj::Update(fTime);
}

void CTile::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CTile * CTile::Clone()
{
	return new CTile(*this);
}

void CTile::Load(FILE * pFile)
{
	// flag 받기
	fread(&m_eFlag, 4, 1, pFile);

	// 타일 이미지 번호 저장
	fread(&m_eTileImage, sizeof(m_eTileImage), 1, pFile);

	// 타일 애니메이션 유무 저장
	fread(&m_bAnimationEnable, sizeof(m_bAnimationEnable), 1, pFile);

	// 타일이 터질수 있는지 유무 저장
	fread(&m_bTileBreak, sizeof(m_bTileBreak), 1, pFile);

	// tag 받기
	int iLength;

	fread(&iLength, 4, 1, pFile);

	char* pTag = new char[iLength + 1];

	fread(pTag, iLength, 1, pFile);
	pTag[iLength] = 0;		// 끝에 NULL

	m_strTag = pTag;

	delete[] pTag;

	// 위치 받기
	fread(&m_tPos, sizeof(m_tPos), 1, pFile);

	// 크기 받기
	fread(&m_tSize, sizeof(m_tSize), 1, pFile);

	// 피봇 받기
	fread(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// 텍스처 정보받기
	// key 받기
	fread(&iLength, 4, 1, pFile);
	char* strKey = new char[iLength + 1];
	fread(strKey, iLength, 1, pFile);
	strKey[iLength] = 0;

	// 전체 경로 받기
	fread(&iLength, 4, 1, pFile);
	wchar_t* strFullPath = new wchar_t[iLength + 1];
	fread(strFullPath, iLength, 2, pFile);
	strFullPath[iLength] = 0;

	// colorkey 사용여부 받기
	bool bColorKey;
	fread(&bColorKey, 1, 1, pFile);

	// color 받기
	COLORREF dwColorKey;
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);

	SetTextureFromFullPath(strKey, strFullPath, bColorKey, dwColorKey);

	delete[]	strKey;
	delete[]	strFullPath;
}
