#include "Collider.h"
#include "../Object/Obj.h"
#include "../Core/Math.h"

CCollider::CCollider()
{
	for (int i = 0; i < CFT_END; ++i)
	{
		m_tFunction[i].bEnable = false;
	}
}

CCollider::CCollider(const CCollider & collider)
{
	*this = collider;

	for (int i = 0; i < CFT_END; ++i)
	{
		m_tFunction[i].bEnable = false;
	}
}

CCollider::~CCollider()
{

	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}

CObj * CCollider::GetObj()
{
	m_pObj->AddRef();
	return m_pObj;
}

void CCollider::SetObj(CObj * pObj)
{
	m_pObj = pObj;

	m_tPrevPos = pObj->GetPos();
}

void CCollider::Update(float fTime)
{
	POSITION	tPos = m_pObj->GetPos();

	m_tMove = tPos - m_tPrevPos;
	m_tPrevPos = tPos;
}

void CCollider::Move()
{
	POSITION	tPos = m_pObj->GetPos();

	m_tMove = tPos - m_tPrevPos;
	m_tPrevPos = tPos;
}

void CCollider::AddCollisionFunction(COLLISION_FUNCTION_TYPE eType, void(*pFunc)(CCollider *, CCollider *))
{
	m_tFunction[eType].bEnable = true;
	m_tFunction[eType].func = bind(pFunc, placeholders::_1, placeholders::_2);
}

void CCollider::CollisionEnter(CCollider * pColl)
{
	if (m_tFunction[CFT_ENTER].bEnable)
		m_tFunction[CFT_ENTER].func(this, pColl);
}

void CCollider::CollisionTrigger(CCollider * pColl)
{
	if (m_tFunction[CFT_TRIGGER].bEnable)
		m_tFunction[CFT_TRIGGER].func(this, pColl);
}

void CCollider::CollisionLeave(CCollider * pColl)
{
	if (m_tFunction[CFT_LEAVE].bEnable)
		m_tFunction[CFT_LEAVE].func(this, pColl);
}

void CCollider::AddCollisionCollider(CCollider * pColl)
{
	m_CollisionList.push_back(pColl);
}

bool CCollider::CheckCollisionList(CCollider * pColl)
{
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pColl)
			return true;
	}

	return false;
}

void CCollider::DeleteCollisionList(CCollider * pColl)
{
	list<CCollider*>::iterator	iter;
	list<CCollider*>::iterator	iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pColl)
		{
			m_CollisionList.erase(iter);
			break;
		}
	}
}

bool CCollider::CollisionRectToRect(const RECTANGLE & rc1, const RECTANGLE & rc2)
{
	if (rc1.fLeft > rc2.fRight)
		return false;

	else if (rc1.fRight < rc2.fLeft)
		return false;

	else if (rc1.fTop > rc2.fBottom)
		return false;

	else if (rc1.fBottom < rc2.fTop)
		return false;

	return true;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & t1, const SPHERE & t2)
{
	return t1.fRadius + t2.fRadius >= CMath::GetDistance(t1.tCenter, t2.tCenter);
}

bool CCollider::CollisionSphereToRect(const SPHERE & tSphere, RECTANGLE rc)
{
	// Center�� �簢�� ���� ���� Ȥ�� ���� ���� �ȿ� ���������� �Ǵ��Ѵ�.
	if ((rc.fLeft <= tSphere.tCenter.x && tSphere.tCenter.x <= rc.fRight) ||
		(rc.fTop <= tSphere.tCenter.y && tSphere.tCenter.y <= rc.fBottom))
	{
		// �簢���� ������ ũ�⸸ŭ Ȯ���Ѵ�.
		rc.fLeft -= tSphere.fRadius;
		rc.fTop -= tSphere.fRadius;
		rc.fRight += tSphere.fRadius;
		rc.fBottom += tSphere.fRadius;

		return CollisionRectToPoint(rc, tSphere.tCenter);
	}

	// ������ 4�� �ٱ� ������ ������ ���
	else
	{
		POSITION	tPos(rc.fLeft, rc.fTop);

		if (CollisionSphereToPoint(tSphere, tPos))
			return true;

		tPos = POSITION(rc.fRight, rc.fTop);

		if (CollisionSphereToPoint(tSphere, tPos))
			return true;

		tPos = POSITION(rc.fLeft, rc.fBottom);

		if (CollisionSphereToPoint(tSphere, tPos))
			return true;

		tPos = POSITION(rc.fRight, rc.fBottom);

		if (CollisionSphereToPoint(tSphere, tPos))
			return true;
	}

	return false;
}

bool CCollider::CollisionRectToPoint(const RECTANGLE & rc, const POSITION & tPos)
{
	if (rc.fLeft > tPos.x)
		return false;

	else if (rc.fRight < tPos.x)
		return false;

	else if (rc.fTop > tPos.y)
		return false;

	else if (rc.fBottom < tPos.y)
		return false;

	return true;
}

bool CCollider::CollisionSphereToPoint(const SPHERE & tSphere, const POSITION & tPos)
{
	float	fDist = CMath::GetDistance(tSphere.tCenter, tPos);

	return fDist <= tSphere.fRadius;
}

bool CCollider::CollisionPixelToPoint(const PPIXEL24 pPixel, UINT iWidth, UINT iHeight, 
	const POSITION & tPos)
{
	return false;
}

bool CCollider::CollisionPixelToRect(const PPIXELCOLLIDERINFO pPixelInfo, const RECTANGLE & rc)
{
	for (int i = (int)rc.fTop; i <= (int)rc.fBottom; ++i)
	{
		for (int j = (int)rc.fLeft; j <= (int)rc.fRight; ++j)
		{
			int	iAddr = i * pPixelInfo->iWidth + j;
			if (pPixelInfo->vecPixel[iAddr].r == pPixelInfo->tCollPixel.r &&
				pPixelInfo->vecPixel[iAddr].g == pPixelInfo->tCollPixel.g &&
				pPixelInfo->vecPixel[iAddr].b == pPixelInfo->tCollPixel.b)
			{
				pPixelInfo->tIntersectPos.x = j;
				pPixelInfo->tIntersectPos.y = i;
				return true;
			}
		}
	}

	return false;
}

bool CCollider::CollisionRectToTileMap(const RECTANGLE & rc, TILEMAPCOLLIDERINFO & tInfo)
{
	if (rc.fRight < 0)
		return false;
	else if (rc.fLeft >= tInfo.iTileX * tInfo.iTileSizeX)
		return false;
	else if (rc.fBottom < 0)
		return false;
	
	else if (rc.fTop >= tInfo.iTileY * tInfo.iTileSizeY)
		return false;

	int iStartX = (int)rc.fLeft / tInfo.iTileSizeX;
	int iEndX = (int)rc.fRight / tInfo.iTileSizeX;
	int iStartY = (int)rc.fTop / tInfo.iTileSizeY;
	int iEndY = (int)rc.fBottom / tInfo.iTileSizeY;

	for (int i = iStartY; i <= iEndY; ++i)
	{
		for (int j = iStartX; j <= iEndX; ++j)
		{
			if (tInfo.vecTileFlag[i * tInfo.iTileX + j] == TF_NOMOVE)
			{
				tInfo.tIntersectRC.fLeft = j * tInfo.iTileSizeX;
				tInfo.tIntersectRC.fTop = i * tInfo.iTileSizeY;
				tInfo.tIntersectRC.fRight = (j + 1) * tInfo.iTileSizeX;
				tInfo.tIntersectRC.fBottom = (i + 1) * tInfo.iTileSizeY;

				return true;
			}
		}
	}

	return false;
}

bool CCollider::CollisionPointToTileMap(const POSITION & pos, TILEMAPCOLLIDERINFO & tInfo)
{
	if (pos.x < 0)
		return false;

	else if (pos.x >= tInfo.iTileX * tInfo.iTileSizeX)
		return false;

	else if (pos.y < 0)
		return false;

	else if (pos.y >= tInfo.iTileY * tInfo.iTileSizeY)
		return false;

	int idx = (int)pos.y / tInfo.iTileSizeY * tInfo.iTileX + (int)pos.x / tInfo.iTileSizeX;

	if (tInfo.vecTileFlag[idx] == TF_NOMOVE)
		return true;

	return false;
}

void CCollider::Destroy()
{
	delete	this;
}
