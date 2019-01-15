#pragma once
#include "Collider.h"

class CColliderTileMap : 
	public CCollider
{
private:
	CColliderTileMap();
	CColliderTileMap(const CColliderTileMap& tilemap);
	~CColliderTileMap();

public:
	static CColliderTileMap* Create(const string& strTag, UINT iTileX, UINT iTileY,
		UINT iTileSizeX, UINT iTileSizeY, const vector<class CTile*>& vecTile);

private:
	TILEMAPCOLLIDERINFO m_tInfo;

public:
	TILEMAPCOLLIDERINFO& GetInfo()
	{
		return m_tInfo;
	}

public:
	virtual void Move(const POSITION& tMove);
	virtual void Move(float x, float y);
	virtual void Move(const POINT& ptMove);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CColliderTileMap* Clone();

public:
	virtual bool Collision(CCollider* pCollider);
};

