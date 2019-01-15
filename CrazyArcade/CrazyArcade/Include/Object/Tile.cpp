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
	// flag �ޱ�
	fread(&m_eFlag, 4, 1, pFile);

	// Ÿ�� �̹��� ��ȣ ����
	fread(&m_eTileImage, sizeof(m_eTileImage), 1, pFile);

	// Ÿ�� �ִϸ��̼� ���� ����
	fread(&m_bAnimationEnable, sizeof(m_bAnimationEnable), 1, pFile);

	// Ÿ���� ������ �ִ��� ���� ����
	fread(&m_bTileBreak, sizeof(m_bTileBreak), 1, pFile);

	// tag �ޱ�
	int iLength;

	fread(&iLength, 4, 1, pFile);

	char* pTag = new char[iLength + 1];

	fread(pTag, iLength, 1, pFile);
	pTag[iLength] = 0;		// ���� NULL

	m_strTag = pTag;

	delete[] pTag;

	// ��ġ �ޱ�
	fread(&m_tPos, sizeof(m_tPos), 1, pFile);

	// ũ�� �ޱ�
	fread(&m_tSize, sizeof(m_tSize), 1, pFile);

	// �Ǻ� �ޱ�
	fread(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// �ؽ�ó �����ޱ�
	// key �ޱ�
	fread(&iLength, 4, 1, pFile);
	char* strKey = new char[iLength + 1];
	fread(strKey, iLength, 1, pFile);
	strKey[iLength] = 0;

	// ��ü ��� �ޱ�
	fread(&iLength, 4, 1, pFile);
	wchar_t* strFullPath = new wchar_t[iLength + 1];
	fread(strFullPath, iLength, 2, pFile);
	strFullPath[iLength] = 0;

	// colorkey ��뿩�� �ޱ�
	bool bColorKey;
	fread(&bColorKey, 1, 1, pFile);

	// color �ޱ�
	COLORREF dwColorKey;
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);

	SetTextureFromFullPath(strKey, strFullPath, bColorKey, dwColorKey);

	delete[]	strKey;
	delete[]	strFullPath;
}
