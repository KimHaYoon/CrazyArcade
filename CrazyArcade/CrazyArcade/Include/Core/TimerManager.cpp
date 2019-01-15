#include "TimerManager.h"
#include "Timer.h"

DEFINITION_SINGLE(CTimerManager)

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
	Safe_Release_Map(m_mapTimer);
}

bool CTimerManager::Init()
{
	CreateTimer("MainTimer");

	return true;
}

CTimer * CTimerManager::CreateTimer(const string & strKey)
{
	// ���� ���� Ű�� ����ϴ� Ÿ�̸Ӱ� �ִ����� üũ�ؼ� ���� ��� �ش� Ÿ�̸Ӹ�
	// ��ȯ���ش�.
	CTimer*	pTimer = FindTimer(strKey);

	if (pTimer)
		return pTimer;

	pTimer = new CTimer;

	if (!pTimer->Init())
	{
		SAFE_DELETE(pTimer);
		return NULL;
	}

	m_mapTimer.insert(make_pair(strKey, pTimer));

	return pTimer;
}

CTimer * CTimerManager::FindTimer(const string & strKey)
{
	unordered_map<string, CTimer*>::iterator	iter = m_mapTimer.find(strKey);

	if (iter == m_mapTimer.end())
		return NULL;

	return iter->second;
}
