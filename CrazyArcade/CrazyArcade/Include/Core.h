#pragma once

#include "GameFramework.h"

class CCore
{
private:
	CCore();
	~CCore();

private:
	static CCore*	m_pInst;

public:
	static CCore* GetInst()
	{
		// m_pInst�� NULL�� ��� �����Ҵ� ���ش�.
		// NULL�� �ƴ� ��� �׳� ��ȯ�Ѵ�. m_pInst�� static ��� �����̹Ƿ� Ŭ���� ��������
		// ������ �����ϹǷ� CCoreŬ������ �̿��ؼ� ������ ��� ��ü�� �����ϴ� �����̱� ��
		// ���� �ѹ� �����ϸ� �������ʹ� ������ �༮�� �����ϰ� ��ȯ�޾� ����ϰ� �ȴ�.
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	static bool	m_bLoop;

private:
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	UINT			m_iWidth;
	UINT			m_iHeight;
	HDC				m_hDC;
	class CTexture*	m_pBackBuffer;

public:
	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HDC GetDC()	const
	{
		return m_hDC;
	}

	UINT GetWidth()	const
	{
		return m_iWidth;
	}

	UINT GetHeight()	const
	{
		return m_iHeight;
	}

public:
	bool Init(HINSTANCE hInst, const wchar_t* pTitle, const wchar_t* pClass, int iIconID,
		UINT iWidth, UINT iHeight);
	int Run();

private:
	void Logic();
	int Input(float fTime);
	int Update(float fTime);
	void Collision(float fTime);
	void Render(float fTime);

private:
	ATOM WindowRegisterClass(TCHAR* pClass, int iIconID);
	BOOL InitWindow(TCHAR* pClass, TCHAR* pTitle, UINT iWidth, UINT iHeight);

public:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

