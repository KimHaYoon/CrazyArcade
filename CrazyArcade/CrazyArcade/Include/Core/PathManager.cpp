#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

bool CPathManager::Init()
{
	// 실행파일이 있는 경로를 얻어온다.
	wchar_t strPath[MAX_PATH] = {};

	GetModuleFileNameW(NULL, strPath, MAX_PATH);

	for (int i = lstrlenW(strPath); i > 0; --i)
	{
		if (strPath[i - 1] == '\\' || strPath[i - 1] == '/')
		{
			memset(&strPath[i], 0, sizeof(wchar_t) * (MAX_PATH - i));
			break;
		}
	}
	wstring wstrPath(&strPath[0]);

	m_mapPath.insert(make_pair(ROOT_PATH, wstrPath));

	CreatePath(TEXTURE_PATH, L"Textures\\");
	CreatePath(ANIMATION_PATH, L"Animation\\");
	CreatePath(MAPDATA_PATH, L"MapData\\");
	CreatePath(ITEM_PATH, L"Item\\");

	return true;
}

bool CPathManager::CreatePath(const string & strKey, const wchar_t * pPath,
	const string & strBaseKey)
{
	if (FindPath(strKey))
		return false;

	// 기본 패스 정보를 얻어온다.
	wstring	strPath = FindPath(strBaseKey);
	strPath += pPath;

	m_mapPath.insert(make_pair(strKey, strPath));

	return true;
}

const wchar_t * CPathManager::FindPath(const string & strKey)
{
	unordered_map<string, wstring>::iterator	iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
		return NULL;

	return iter->second.c_str();
}

wstring CPathManager::FindPathFromWString(const string & strKey)
{
	unordered_map<string, wstring>::iterator	iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
		return L"";

	return iter->second;
}

const char * CPathManager::FindPathFromMultibyte(const string & strKey)
{
	const wchar_t* strFindPath = FindPath(strKey);

	if (!strFindPath)
		return NULL;

	char	strPath[MAX_PATH] = {};

	WideCharToMultiByte(CP_ACP, 0, strFindPath, -1,
		strPath, lstrlenW(strFindPath) + 1, NULL, NULL);

	m_strChangePath = strPath;

	return m_strChangePath.c_str();
}
