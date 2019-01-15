#include "Mouse.h"
#include "../Collider/ColliderPoint.h"
#include "../Core.h"

CMouse::CMouse()
{
}

CMouse::CMouse(const CMouse & mouse)	:
	CObj(mouse)
{
	m_ptMousePos = mouse.m_ptMousePos;
	m_ptMouseMove = mouse.m_ptMouseMove;
	m_hWnd = mouse.m_hWnd;
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(m_hWnd, &m_ptMousePos);

	memset(&m_ptMouseMove, 0, sizeof(POINT));

	m_tPos = m_ptMousePos;

	m_tPivot.x = 0.f;
	m_tPivot.y = 0.f;

	// ����Ʈ �浹ü�� ������ش�.
	POSITION	tPos = m_ptMousePos;
	CColliderPoint*	pPoint = CColliderPoint::Create("Mouse", tPos);

	pPoint->AddCollisionFunction<CMouse>(CFT_ENTER, &CMouse::CollisionEnter, this);
	pPoint->AddCollisionFunction<CMouse>(CFT_TRIGGER, &CMouse::CollisionTrigger, this);
	pPoint->AddCollisionFunction<CMouse>(CFT_LEAVE, &CMouse::CollisionLeave, this);

	AddCollider(pPoint);

	DisableCamera();

	SetTexture("MouseNormal", L"Mouse.bmp", true);
	ShowCursor(FALSE);

	return true;
}

void CMouse::Input(float fTime)
{
}

void CMouse::Update(float fTime)
{
	CObj::Update(fTime);

	// ���콺 ��ġ�� ���´�.
	POINT	ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	m_ptMouseMove.x = ptMouse.x - m_ptMousePos.x;
	m_ptMouseMove.y = ptMouse.y - m_ptMousePos.y;

	m_ptMousePos = ptMouse;

	m_tPos = m_ptMousePos;
}

void CMouse::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
#ifdef _DEBUG
	wchar_t str[128] = {};
	wsprintfW(str, L"%d %d", m_ptMousePos.x, m_ptMousePos.y);
	TextOutW(hDC, 100, 100, str, lstrlenW(str));
#endif
}

CMouse * CMouse::Clone()
{
	return new CMouse(*this);
}

void CMouse::CollisionEnter(CCollider * p1, CCollider * p2)
{
}

void CMouse::CollisionTrigger(CCollider * p1, CCollider * p2)
{
}

void CMouse::CollisionLeave(CCollider * p1, CCollider * p2)
{
}
