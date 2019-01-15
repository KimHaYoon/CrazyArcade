#include "ColliderTileMap.h"
#include "ColliderRect.h"
#include "ColliderSphere.h"
#include "ColliderPoint.h"
#include "../Object/Tile.h"

CColliderTileMap::CColliderTileMap()
{
	SetTag("ColliderTileMap");
	m_eType = CT_TILEMAP;
}

CColliderTileMap::CColliderTileMap(const CColliderTileMap & tilemap) :
	CCollider(tilemap)
{
	m_tInfo = tilemap.m_tInfo;
}


CColliderTileMap::~CColliderTileMap()
{
}

CColliderTileMap * CColliderTileMap::Create(const string & strTag, UINT iTileX, UINT iTileY, UINT iTileSizeX, UINT iTileSizeY, const vector<class CTile*>& vecTile)
{
	CColliderTileMap* pTileMap = new CColliderTileMap;

	if (!pTileMap->Init())
	{
		SAFE_DELETE(pTileMap);
		return  NULL;
	}

	pTileMap->SetTag(strTag);

	pTileMap->m_tInfo.iTileX = iTileX;
	pTileMap->m_tInfo.iTileY = iTileY;
	pTileMap->m_tInfo.iTileSizeX = iTileSizeX;
	pTileMap->m_tInfo.iTileSizeY = iTileSizeY;

	pTileMap->m_tInfo.vecTileFlag.reserve(vecTile.size());

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		pTileMap->m_tInfo.vecTileFlag.push_back(vecTile[i]->GetFlag());
	}

	return pTileMap;
}

void CColliderTileMap::Move(const POSITION & tMove)
{
}

void CColliderTileMap::Move(float x, float y)
{
}

void CColliderTileMap::Move(const POINT & ptMove)
{
}

bool CColliderTileMap::Init()
{
	return true;
}

void CColliderTileMap::Update(float fTime)
{
	CCollider::Update(fTime);
}

void CColliderTileMap::Render(HDC hDC, float fTime)
{
}

CColliderTileMap * CColliderTileMap::Clone()
{
	return new CColliderTileMap(*this);
}

bool CColliderTileMap::Collision(CCollider * pCollider)
{
	switch (pCollider->GetType())
	{
	case CT_RECT:
		return CollisionRectToTileMap(((CColliderRect*)pCollider)->GetRect(), m_tInfo);
	case CT_SPHERE:
		break;
	case CT_LINE:
		break;
	case CT_POINT:
		return CollisionPointToTileMap(((CColliderPoint*)pCollider)->GetPoint(), m_tInfo);
	case CT_PIXEL:
		break;
	case CT_TILEMAP:
		break;
	}
}
