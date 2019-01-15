#pragma once

#include "../GameFramework.h"
#include "../Base.h"

enum COLLISION_FUNCTION_TYPE
{
	CFT_ENTER,
	CFT_TRIGGER,
	CFT_LEAVE,
	CFT_END
};

typedef struct _tagCollisionFunction
{
	function<void(class CCollider*, class CCollider*)> func;
	bool	bEnable;
}COLLISIONFUNCTION, *PCOLLISIONFUNCTION;

class CCollider : 
	public CBase
{
private:
	friend class CObj;

protected:
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider() = 0;

protected:
	COLLIDER_TYPE		m_eType;
	string				m_strTag;
	class CScene*		m_pScene;
	class CLayer*		m_pLayer;
	class CObj*			m_pObj;
	POSITION			m_tPrevPos;
	POSITION			m_tMove;

protected:
	COLLISIONFUNCTION	m_tFunction[CFT_END];
	list<CCollider*>	m_CollisionList;

public:
	COLLIDER_TYPE GetType()	const
	{
		return m_eType;
	}

	string GetTag()	const
	{
		return m_strTag;
	}

	class CScene* GetScene()	const
	{
		return m_pScene;
	}

	class CLayer* GetLayer()	const
	{
		return m_pLayer;
	}

	class CObj* GetObj();

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}

	void SetObj(class CObj* pObj);

public:
	virtual void Move(const POSITION& tMove) = 0;
	virtual void Move(float x, float y) = 0;
	virtual void Move(const POINT& ptMove) = 0;

public:
	virtual bool Init() = 0;
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime) = 0;
	virtual CCollider* Clone() = 0;

public:
	virtual bool Collision(CCollider* pCollider) = 0;
	virtual void Move();

public:
	void AddCollisionFunction(COLLISION_FUNCTION_TYPE eType, void(*pFunc)(CCollider*, CCollider*));
	void CollisionEnter(CCollider* pColl);
	void CollisionTrigger(CCollider* pColl);
	void CollisionLeave(CCollider* pColl);
	void AddCollisionCollider(CCollider* pColl);
	bool CheckCollisionList(CCollider* pColl);
	void DeleteCollisionList(CCollider* pColl);

	template <typename T>
	void AddCollisionFunction(COLLISION_FUNCTION_TYPE eType, void (T::*pFunc)(CCollider*, CCollider*),
		T* pObj)
	{
		m_tFunction[eType].bEnable = true;
		// bind �Լ��� �̿��ؼ� function ��ü�� ������� �� �ִ�. �Ϲ� �����Լ��� �Լ� �ּҸ� �־��ְ�
		// ������� �� ������ ����Լ��� �Լ��ּҿ� ȣ�� ��ü�� ��� �־��־�� �Ѵ�.
		m_tFunction[eType].func = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
	}

protected:
	bool CollisionRectToRect(const RECTANGLE& rc1, const RECTANGLE& rc2);
	bool CollisionSphereToSphere(const SPHERE& t1, const SPHERE& t2);
	bool CollisionSphereToRect(const SPHERE& tSphere, RECTANGLE rc);
	bool CollisionRectToPoint(const RECTANGLE& rc, const POSITION& tPos);
	bool CollisionSphereToPoint(const SPHERE& tSphere, const POSITION& tPos);
	bool CollisionPixelToPoint(const PPIXEL24 pPixel, UINT iWidth, UINT iHeight,
		const POSITION& tPos);
	bool CollisionPixelToRect(const PPIXELCOLLIDERINFO pPixelInfo, const RECTANGLE& rc);
	bool CollisionRectToTileMap(const RECTANGLE& rc, TILEMAPCOLLIDERINFO& tInfo);
	bool CollisionPointToTileMap(const POSITION& pos, TILEMAPCOLLIDERINFO& tInfo);
	
public:
	void Destroy();
};

