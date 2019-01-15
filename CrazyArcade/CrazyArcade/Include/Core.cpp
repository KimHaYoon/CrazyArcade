#include "Core.h"
#include "Core\Timer.h"
#include "Core\Camera.h"
#include "Core\Input.h"
#include "Core\PathManager.h"
#include "Core\TimerManager.h"
#include "Collider\CollisionManager.h"
#include "Object\ObjectManager.h"
#include "Scene\SceneManager.h"
#include "Resources\ResourcesManager.h"
#include "Resources\Texture.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;

CCore::CCore()	:
	m_pBackBuffer(NULL)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(3233);

#ifdef _DEBUG
	AllocConsole();
#endif
}


CCore::~CCore()
{
	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CInput);
	SAFE_RELEASE(m_pBackBuffer);
	DESTROY_SINGLE(CResourcesManager);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CObjectManager);
	DESTROY_SINGLE(CTimerManager);
	DESTROY_SINGLE(CSceneManager);
	ReleaseDC(m_hWnd, m_hDC);

#ifdef _DEBUG
	FreeConsole();
#endif // _DEBUG
}

bool CCore::Init(HINSTANCE hInst, const wchar_t * pTitle, const wchar_t * pClass, int iIconID,
	UINT iWidth, UINT iHeight)
{
	srand((unsigned)time(NULL));
	m_hInst = hInst;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	
	WindowRegisterClass((TCHAR*)pClass, iIconID);

	InitWindow((TCHAR*)pClass, (TCHAR*)pTitle, iWidth, iHeight);

	// GetDC �Լ� �տ� :: ���� ������ ����Լ� GetDC�� Win32API���� �����ϴ� GetDC�Լ���
	// Win32���� �����ϴ� �Լ��� ȣ���ϱ� ���� �տ� ::�� �ٿ��־���.
	m_hDC = ::GetDC(m_hWnd);

	// ī�޶� �ʱ�ȭ
	if (!GET_SINGLE(CCamera)->Init(0.f, 0.f, (float)iWidth, (float)iHeight))
		return false;

	// ��� ������ �ʱ�ȭ
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// Ÿ�̸� �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CTimerManager)->Init())
		return false;

	// ���ҽ� �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CResourcesManager)->Init(m_hInst, m_hDC))
		return false;

	// �Է°����ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CInput)->Init(m_hWnd))
		return false;

	// �浹 �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CCollisionManager)->Init())
		return false;

	// ������Ʈ �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CObjectManager)->Init())
		return false;

	// �������ڸ� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	// ����۸� ���´�.
	m_pBackBuffer = GET_SINGLE(CResourcesManager)->FindTexture("BackBuffer");

	return true;
}

int CCore::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// ������ ����Ÿ���� ���� else  �������� ���´�.
		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CCore::Logic()
{
	CTimer*	pTimer = GET_SINGLE(CTimerManager)->FindTimer("MainTimer");

	pTimer->Update();

	Input(pTimer->GetDeltaTime());
	if (Update(pTimer->GetDeltaTime()) == SC_CHANGE)
	{
		GET_SINGLE(CCollisionManager)->Clear();
		return;
	}
	Collision(pTimer->GetDeltaTime());
	Render(pTimer->GetDeltaTime());
}

int CCore::Input(float fTime)
{
	// �Է� ������ ������Ʈ
	GET_SINGLE(CInput)->Update(fTime);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		GET_SINGLE(CCamera)->SetTarget(NULL);

	GET_SINGLE(CCamera)->Input(fTime);
	GET_SINGLE(CSceneManager)->Input(fTime);

	return 0;
}

int CCore::Update(float fTime)
{
	GET_SINGLE(CCamera)->Update(fTime);
	return GET_SINGLE(CSceneManager)->Update(fTime);
}

void CCore::Collision(float fTime)
{
	// ���콺�� �浹 �����ڿ� ����Ѵ�.
	GET_SINGLE(CCollisionManager)->AddObject(GET_SINGLE(CInput)->GetMouse());
	GET_SINGLE(CCollisionManager)->Collision(fTime);
}

void CCore::Render(float fTime)
{
	// ��� �ȿ� �ִ� ��� ������Ʈ�� ����ۿ� �׸���.
	GET_SINGLE(CSceneManager)->Render(m_pBackBuffer->GetMemDC(), fTime);

	/*static POINT	ptStart, ptEnd;
	static bool		bStart;

	if (KEYDOWN("MouseLButton"))
	{
		GetCursorPos(&ptStart);
		ScreenToClient(m_hWnd, &ptStart);
		bStart = true;
	}

	else if (KEYUP("MouseLButton"))
	{
		GetCursorPos(&ptEnd);
		ScreenToClient(m_hWnd, &ptEnd);
	}

	if (bStart)
	{
		HDC	hBackDC = m_pBackBuffer->GetMemDC();
		MoveToEx(hBackDC, ptStart.x, ptStart.y, NULL);
		POINT	ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(m_hWnd, &ptCursor);

		LineTo(hBackDC, ptCursor.x, ptStart.y);
		LineTo(hBackDC, ptCursor.x, ptCursor.y);
		LineTo(hBackDC, ptStart.x, ptCursor.y);
		LineTo(hBackDC, ptStart.x, ptStart.y);
	}*/

	// ���������� ���콺�� ����ۿ� �׸���.
	GET_SINGLE(CInput)->GetMouse()->Render(m_pBackBuffer->GetMemDC(), fTime);

	// ���������� ����۸� ȭ�鿡 �׸���.
	BitBlt(m_hDC, 0, 0, m_iWidth, m_iHeight, m_pBackBuffer->GetMemDC(),
		0, 0, SRCCOPY);
}

ATOM CCore::WindowRegisterClass(TCHAR * pClass, int iIconID)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(iIconID));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY170825);
	wcex.lpszClassName = (LPCWSTR)pClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iIconID));

	return RegisterClassExW(&wcex);
}

BOOL CCore::InitWindow(TCHAR* pClass, TCHAR * pTitle, UINT iWidth, UINT iHeight)
{
	HWND hWnd = CreateWindowW((LPCWSTR)pClass, (LPCWSTR)pTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, iWidth, iHeight, nullptr, nullptr, m_hInst, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	// �������� Ŭ���̾�Ʈ ������ ���ϴ� ũ��� �����ϴ� ���
	RECT	rc = { 0, 0, iWidth, iHeight };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOMOVE | SWP_NOZORDER);

	m_hWnd = hWnd;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:	// Ű�� ������ ������ �޼����̴�.
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
