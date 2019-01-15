#include "Input.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_pCreate(NULL)
{
}

CInput::~CInput()
{
	SAFE_RELEASE(m_pMouse);

	unordered_map<string, PKEYINFO>::iterator	iter;
	unordered_map<string, PKEYINFO>::iterator	iterEnd = m_mapKey.end();
	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	
	m_mapKey.clear();
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	
	// 플레이어
	CreateKey(VK_LEFT, "MoveLeft");
	CreateKey(VK_RIGHT, "MoveRight");
	CreateKey(VK_UP, "MoveUp");
	CreateKey(VK_DOWN, "MoveDown");
	CreateKey(VK_LBUTTON, "MouseLButton");
	CreateKey(VK_RBUTTON, "MouseRButton");

	// Map
	//CreateKey(VK_CONTROL, '1', "FlagMode");
	//CreateKey(VK_CONTROL, '2', "TileMode");
	//CreateKey(VK_CONTROL, "Ctrl");
	//CreateKey(VK_F1, "OptionMove");
	//CreateKey(VK_F2, "OptionNoMove");
	//CreateKey(VK_F3, "OptionNone");
	//CreateKey(VK_CONTROL, 'S', "Save");
	//CreateKey(VK_CONTROL, 'O', "Load");

	//// 타일 이미지
	//CreateKey('1', "BOX0");
	//CreateKey('2', "BOX1");
	//CreateKey('3', "BOX2");
	//CreateKey('4', "HOUSE0");
	//CreateKey('5', "HOUSE1");
	//CreateKey('6', "HOUSE2");
	//CreateKey('7', "MOVETREE");
	//CreateKey('8', "NOMOVETREE");
	//CreateKey('9', "CROSSWALK0");
	//CreateKey('0', "CROSSWALK1");
	//CreateKey(VK_SHIFT, '1', "ROAD0");
	//CreateKey(VK_SHIFT, '2', "ROAD1");
	//CreateKey(VK_SHIFT, '3', "ROAD2");
	//CreateKey(VK_SHIFT, '4', "BLOCK0");
	//CreateKey(VK_SHIFT, '5', "BLOCK1");

	// 마우스 생성
	m_pMouse = new CMouse;

	m_pMouse->SetWindowHandle(m_hWnd);

	if (!m_pMouse->Init())
	{
		SAFE_RELEASE(m_pMouse);
		return false;
	}

	return true;
}

void CInput::Update(float fTime)
{
	m_pMouse->Update(fTime);

	unordered_map<string, PKEYINFO>::iterator	iter;
	unordered_map<string, PKEYINFO>::iterator	iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int	iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iPushCount;
		}

		// 벡터에 있는 키를 모두 눌렀을 경우
		if (iPushCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPush)
				iter->second->bDown = true;

			else
			{
				iter->second->bPush = true;
				iter->second->bDown = false;
			}
		}

		// 이전 프레임에 이 키를 누르고 있었을 경우
		else if (iter->second->bDown || iter->second->bPush)
		{
			iter->second->bUp = true;
			iter->second->bDown = false;
			iter->second->bPush = false;
		}

		else if (iter->second->bUp)
		{
			iter->second->bUp = false;
		}
	}
}

PKEYINFO CInput::FindKey(const string & strKey)	const
{
	unordered_map<string, PKEYINFO>::const_iterator	iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}

bool CInput::KeyDown(const string & strKey) const
{
	PKEYINFO pKey = FindKey(strKey);

	if (!pKey)
		return false;

	return pKey->bDown;
}

bool CInput::KeyPush(const string & strKey) const
{
	PKEYINFO pKey = FindKey(strKey);

	if (!pKey)
		return false;

	return pKey->bPush;
}

bool CInput::KeyUp(const string & strKey) const
{
	PKEYINFO pKey = FindKey(strKey);

	if (!pKey)
		return false;

	return pKey->bUp;
}
