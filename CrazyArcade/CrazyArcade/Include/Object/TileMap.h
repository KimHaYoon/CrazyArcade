#pragma once
#include "Obj.h"

class CTileMap :
	public CObj
{
protected:
	friend class CObjectManager;

protected:
	CTileMap();
	CTileMap(const CTileMap& tilemap);
	~CTileMap();

protected:
	vector<class CTile*>	m_vecTile;
	vector<class CTexture*>	m_vecTileTexture;
	vector<class CTexture*> m_vecFlagTexture;

protected:
	TILEMAPCOLLIDERINFO	m_tTileInfo;
	EDIT_MODE			m_eEdit;
	TILE_FLAG			m_eFlag;
	TILE_IMAGE			m_eTileImage;

public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CTileMap* Clone();

public:
	void AddTileTexture(const string& strKey, const wchar_t* pFileName, bool bColorKey = false,
		COLORREF dwColorKey = RGB(255, 0, 255));

public:
	void Load(char* pFileName, const string& strPathKey);

public:
	void CreateCollider();
	void CollisionEnter(class CCollider* pColl1, class CCollider* pColl2);
	void CollisionTrigger(class CCollider* pColl1, class CCollider* pColl2);

public:
	TILEMAPCOLLIDERINFO GetTileMapInfo()	const
	{
		return m_tTileInfo;
	}

	vector<class CTile*>& GetVectTile()
	{
		return m_vecTile;
	}
};


