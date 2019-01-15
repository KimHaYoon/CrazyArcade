#include "TileMap.h"
#include "Tile.h"
#include "../Core.h"
#include "../Core/Input.h"
#include "../Core/PathManager.h"
#include "../Core/Camera.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Collider/ColliderTileMap.h"
#include "../Animation/Animation.h"

CTileMap::CTileMap()
{
	ZeroMemory(&m_tTileInfo, sizeof(m_tTileInfo));
}

CTileMap::CTileMap(const CTileMap & tilemap) :
	CObj(tilemap)
{
	m_tTileInfo = tilemap.m_tTileInfo;
	m_eEdit = tilemap.m_eEdit;
	m_eFlag = tilemap.m_eFlag;
	m_eTileImage = tilemap.m_eTileImage;

	m_vecTile.clear();

	for (size_t i = 0; i < tilemap.m_vecTile.size(); ++i)
	{
		m_vecTile.push_back(tilemap.m_vecTile[i]->Clone());
	}

	m_vecTileTexture = tilemap.m_vecTileTexture;

	for (size_t i = 0; i < m_vecTileTexture.size(); ++i)
	{
		m_vecTileTexture[i]->AddRef();
	}

	m_vecFlagTexture = tilemap.m_vecFlagTexture;

	for (size_t i = 0; i < m_vecFlagTexture.size(); ++i)
	{
		m_vecFlagTexture[i]->AddRef();
	}
}

CTileMap::~CTileMap()
{
	Safe_Release_VecList(m_vecTile);
	Safe_Release_VecList(m_vecTileTexture);
	Safe_Release_VecList(m_vecFlagTexture);
}

bool CTileMap::Init()
{
	m_eEdit = EM_FLAG;
	m_eFlag = TF_NONE;
	m_eTileImage = TI_NONE;

	CTexture* pTexture = GET_SINGLE(CResourcesManager)->LoadTexture("OptionNone",
		L"03.InGame/Tile/Tile_1.bmp", true);

	if (!pTexture)
		return false;

	m_vecFlagTexture.push_back(pTexture);

	pTexture = GET_SINGLE(CResourcesManager)->LoadTexture("OptionNoMove",
		L"03.InGame/Tile/Tile_2.bmp", true);

	if (!pTexture)
		return false;

	m_vecFlagTexture.push_back(pTexture);
	return true;
}

void CTileMap::Input(float fTime)
{
}

void CTileMap::Update(float fTime)
{
	for (int i = 0; i < m_tTileInfo.iTileY; ++i)
	{
		for (int j = 0; j < m_tTileInfo.iTileX; ++j)
		{
			int idx = i * m_tTileInfo.iTileX + j;

			m_vecTile[idx]->Update(fTime);
		}
	}
}

void CTileMap::Render(HDC hDC, float fTime)
{
	for (int i = 0; i < m_tTileInfo.iTileY; ++i)
	{
		for (int j = 0; j < m_tTileInfo.iTileX; ++j)
		{
			int idx = i * m_tTileInfo.iTileX + j;

			m_vecTile[idx]->Render(hDC, fTime);
		}
	}

#ifdef _DEBUG
	switch (m_eEdit)
	{
	case EM_FLAG:
		for (int i = 0; i < m_tTileInfo.iTileY; ++i)
		{
			for (int j = 0; j < m_tTileInfo.iTileX; ++j)
			{
				int idx = i * m_tTileInfo.iTileX + j;

				//ColorKey를 제외하고 출력한다.

				UINT	iWidth, iHeight;
				iWidth = m_vecFlagTexture[TF_NONE]->GetWidth();
				iHeight = m_vecFlagTexture[TF_NONE]->GetHeight();

				int	x, y;
				x = j * iWidth + 20;
				y = i * iHeight + 40;

				switch (m_vecTile[idx]->GetFlag())
				{
				case TF_NONE:
				{
					TransparentBlt(hDC, x, y, 40, 40,
						m_vecFlagTexture[TF_NONE]->GetMemDC(), 0, 0, 40, 40,
						m_vecFlagTexture[TF_NONE]->GetColorKey());
					break;
				}
				case TF_NOMOVE:
				{
					TransparentBlt(hDC, x, y, 40, 40,
						m_vecFlagTexture[TF_NOMOVE]->GetMemDC(), 0, 0, 40, 40,
						m_vecFlagTexture[TF_NOMOVE]->GetColorKey());
					break;
				}
				}
			}
		}
		break;
	case EM_TILE:
		break;
	default:
		break;
	}
#endif
}

CTileMap * CTileMap::Clone()
{
	return new CTileMap(*this);
}

void CTileMap::AddTileTexture(const string & strKey, const wchar_t * pFileName, bool bColorKey, COLORREF dwColorKey)
{
	CTexture* pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, bColorKey, dwColorKey);

	if (!pTexture)
		return;

	m_vecTileTexture.push_back(pTexture);
}

void CTileMap::Load(char * pFileName, const string & strPathKey)
{
	FILE*	pFile = NULL;

	string	strPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(strPathKey);
	strPath += pFileName;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (pFile)
	{
		Safe_Release_VecList(m_vecTile);

		// 타일의 가로, 세로 저장
		fread(&m_tTileInfo.iTileX, sizeof(m_tTileInfo.iTileX), 1, pFile);
		fread(&m_tTileInfo.iTileY, sizeof(m_tTileInfo.iTileY), 1, pFile);

		// 타일의 가로, 세로 크기 저장
		fread(&m_tTileInfo.iTileSizeX, sizeof(m_tTileInfo.iTileSizeX), 1, pFile);
		fread(&m_tTileInfo.iTileSizeY, sizeof(m_tTileInfo.iTileSizeY), 1, pFile);

		for (int i = 0; i < m_tTileInfo.iTileY; ++i)
		{
			for (int j = 0; j < m_tTileInfo.iTileX; ++j)
			{
				int	idx = i * m_tTileInfo.iTileX + j;

				CTile*	pTile = new CTile;

				pTile->Load(pFile);
				
				m_vecTile.push_back(pTile);

				if (m_vecTile[idx]->GetTileImage() == TI_BOX0 ||
					m_vecTile[idx]->GetTileImage() == TI_BOX1 ||
					m_vecTile[idx]->GetTileImage() == TI_BOX2)
				{
					m_vecTile[idx]->SetAnimation("Box.anm");
					m_vecTile[idx]->m_pAnimation->SetAnimationStart(false);
				}
				else if (m_vecTile[idx]->GetTileImage() == TI_MOVETREE)
				{
					//m_vecTile[idx]->SetAnimation("MoveTree.anm");
					//m_vecTile[idx]->m_pAnimation->SetAnimationStart(false);
				}
			}
		}

		fclose(pFile);
	}
	CreateCollider();
}

void CTileMap::CreateCollider()
{
	CColliderTileMap* pCollider = CColliderTileMap::Create("ColliderTileMap",
		m_tTileInfo.iTileX, m_tTileInfo.iTileY, m_tTileInfo.iTileSizeX,
		m_tTileInfo.iTileSizeY, m_vecTile);

	pCollider->AddCollisionFunction(CFT_ENTER, &CTileMap::CollisionEnter, this);

	AddCollider(pCollider);
}

void CTileMap::CollisionEnter(CCollider * pColl1, CCollider * pColl2)
{
}

void CTileMap::CollisionTrigger(CCollider * pColl1, CCollider * pColl2)
{
}
