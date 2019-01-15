#pragma once

#include "../GameFramework.h"

typedef struct _tagAnimation
{
	string				strName;
	ANIMATION_TYPE		eType;
	ANIMATION_OPTION	eOption;
	UINT	iImageWidth;
	UINT	iImageHeight;
	UINT	iFrameMaxX;
	UINT	iFrameMaxY;
	UINT	iFrameX;
	UINT	iFrameY;
	float	fLimitTime;
	float	fTime;
}ANIMATION, *PANIMATION;

class CAnimation
{
private:
	friend class CObj;

private:
	CAnimation();
	~CAnimation();

private:
	ANIMATION	m_tInfo;
	vector<UINT>	m_vecLineFrameCount;
	UINT			m_iCurrentAnimation;
	bool			m_bFrameEnd;
	bool			m_bAnimationStart;

public:
	bool GetAnimationFrameEnd()	const
	{
		return m_bFrameEnd;
	}

	bool GetAnimationStart() const
	{
		return m_bAnimationStart;
	}

	ANIMATION GetAnimationInfo()	const
	{
		return m_tInfo;
	}

	UINT GetFrameWidth()	const
	{
		return m_tInfo.iImageWidth / m_tInfo.iFrameMaxX;
	}

	UINT GetFrameHeight()	const
	{
		return m_tInfo.iImageHeight / m_tInfo.iFrameMaxY;
	}

public:
	void SetAnimationStart(bool bAnimationStart)
	{
		m_bAnimationStart = bAnimationStart;
	}

	void SetLimitTime(float fTime)
	{
		m_tInfo.fLimitTime = fTime;
	}

	// �ʿ信 ���� Set�Լ��� ����� ����սô�.
	void AddLineFrameCount(UINT iFrameCount)
	{
		m_vecLineFrameCount.push_back(iFrameCount);
	}

	void SetTextureSize(UINT iWidth, UINT iHeight)
	{
		m_tInfo.iImageHeight = iHeight;
		m_tInfo.iImageWidth = iWidth;
	}

	void SetFrameX(UINT x)
	{
		m_tInfo.iFrameX = x;
	}

public:
	static CAnimation* Create(const char* pName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, UINT iWidth, UINT iHeight,
		UINT iFrameMaxX, UINT iFrameMaxY, float fLimitTime);
	static CAnimation* Create(const char* pFileName, 
		const string& strPathKey = ROOT_PATH);
	
public:
	bool Init(const char* pName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, UINT iWidth, UINT iHeight,
		UINT iFrameMaxX, UINT iFrameMaxY, float fLimitTime);
	bool Init(const char* pFileName,
		const string& strPathKey = ROOT_PATH);
	void Update(float fTime);
	CAnimation* Clone();

public:
	void ChangeAnimation(UINT iAnimation);
	bool Load(const char* pFileName, const string& strPathKey = ANIMATION_PATH);
};

