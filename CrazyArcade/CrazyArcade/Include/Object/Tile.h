#pragma once
#include "Obj.h"

class CTile :
	public CObj
{
protected:
	friend class CObjectManager;
	friend class CTileMap;

protected:
	CTile();
	CTile(const CTile& tile);
	~CTile();

protected:
	TILEMAPCOLLIDERINFO	m_tTileInfo;
	EDIT_MODE			m_eEdit;
	TILE_FLAG			m_eFlag;
	TILE_IMAGE			m_eTileImage;
	bool				m_bAnimationEnable;
	bool				m_bTileBreak;

public:
	TILEMAPCOLLIDERINFO	GetTileInfo() const
	{
		return m_tTileInfo;
	}

	EDIT_MODE GetEdit()	const
	{
		return m_eEdit;
	}

	TILE_FLAG GetFlag() const
	{
		return m_eFlag;
	}

	TILE_IMAGE GetTileImage()	const
	{
		return m_eTileImage;
	}

	bool GetAnimationEnable()	const
	{
		return m_bAnimationEnable;
	}

	bool GetTileBreak()	const
	{
		return m_bTileBreak;
	}

public:
	void SetEdit(EDIT_MODE eEdit)
	{
		m_eEdit = eEdit;
	}

	void SetFlag(TILE_FLAG eFlag)
	{
		m_eFlag = eFlag;
	}

	void SetTileImage(TILE_IMAGE eTileImage)
	{
		m_eTileImage = eTileImage;
	}

	void SetAnimationEnable(bool bAnimationEnable)
	{
		m_bAnimationEnable = bAnimationEnable;
	}

	void SetTileBreak(bool bTileBreak)
	{
		m_bTileBreak = bTileBreak;
	}
public:
	virtual bool Init();
	virtual void Input(float fTime);
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CTile* Clone();

public:
	void Load(FILE* pFile);
};
