
#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <stdlib.h>
#include <typeinfo.h>
#include <algorithm>
#include <conio.h>
#include <functional>
#include <random>
#include <time.h>

using namespace std;

// 사용자정의 헤더파일
#include "Macro.h"

// TransparentBlt를 사용하기 위한 라이브러리를 추가해준다.
#pragma comment(lib, "msimg32")

// 경로 키
#define	ROOT_PATH		"RootPath"
#define	TEXTURE_PATH	"TexturePath"
#define	ANIMATION_PATH	"AnimationPath"
#define MAPDATA_PATH	"MapDataPath"
#define ITEM_PATH       "ItemPath"
#define DATA_PATH		"DataPath"

#define	PI		3.141592f
#define	GRAVITY	0.98f

// 맵 사이즈
#define	MAP_WIDTH	600
#define MAP_HEIGHT	520

template <typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator	iter = p.begin();
	typename T::iterator	iterEnd = p.end();

	while (iter != iterEnd)
	{
		SAFE_RELEASE((*iter));
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator	iter = p.begin();
	typename T::iterator	iterEnd = p.end();

	while (iter != iterEnd)
	{
		SAFE_RELEASE(iter->second);
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator	iter = p.begin();
	typename T::iterator	iterEnd = p.end();

	while (iter != iterEnd)
	{
		SAFE_DELETE((*iter));
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator	iter = p.begin();
	typename T::iterator	iterEnd = p.end();

	while (iter != iterEnd)
	{
		SAFE_DELETE(iter->second);
		++iter;
	}

	p.clear();
}

// 위치 정보 구조체
typedef struct _tagPosition
{
	float	x, y;

	_tagPosition() :
		x(0.f),
		y(0.f)
	{
	}

	_tagPosition(const _tagPosition& pos)
	{
		*this = pos;
	}

	_tagPosition(const POINT& pos)
	{
		*this = pos;
	}

	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	void operator =(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator =(const POINT& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator =(float fArr[2])
	{
		x = fArr[0];
		y = fArr[1];
	}

	void operator =(int iArr[2])
	{
		x = iArr[0];
		y = iArr[1];
	}

	_tagPosition operator +(const _tagPosition& pos)
	{
		_tagPosition	tResult;

		tResult.x = x + pos.x;
		tResult.y = y + pos.y;

		return tResult;
	}

	_tagPosition operator +(const POINT& pos)
	{
		_tagPosition	tResult;

		tResult.x = x + pos.x;
		tResult.y = y + pos.y;

		return tResult;
	}

	_tagPosition operator +(float f[2])
	{
		_tagPosition	tResult;

		tResult.x = x + f[0];
		tResult.y = y + f[1];

		return tResult;
	}

	void operator +=(const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	void operator +=(const POINT& pt)
	{
		x += pt.x;
		y += pt.y;
	}

	_tagPosition operator -(const _tagPosition& pos)
	{
		_tagPosition	tResult;

		tResult.x = x - pos.x;
		tResult.y = y - pos.y;

		return tResult;
	}

	_tagPosition operator -(const POINT& pos)
	{
		_tagPosition	tResult;

		tResult.x = x - pos.x;
		tResult.y = y - pos.y;

		return tResult;
	}

	_tagPosition operator -(float f[2])
	{
		_tagPosition	tResult;

		tResult.x = x - f[0];
		tResult.y = y - f[1];

		return tResult;
	}

	void operator -=(const _tagPosition& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	_tagPosition operator *(const _tagPosition& pos)
	{
		_tagPosition	tResult;

		tResult.x = x * pos.x;
		tResult.y = y * pos.y;

		return tResult;
	}

	_tagPosition operator *(float f[2])
	{
		_tagPosition	tResult;

		tResult.x = x * f[0];
		tResult.y = y * f[1];

		return tResult;
	}

	void operator *=(const _tagPosition& pos)
	{
		x *= pos.x;
		y *= pos.y;
	}

	bool operator ==(const _tagPosition& pos)
	{
		return x == pos.x && y == pos.y;
	}

	bool operator ==(const POINT& pos)
	{
		return x == pos.x && y == pos.y;
	}

	bool operator !=(const _tagPosition& pos)
	{
		return x != pos.x || y != pos.y;
	}

	bool operator !=(const POINT& pos)
	{
		return x != pos.x || y != pos.y;
	}
}POSITION, *PPOSITION, _SIZE, *_PSIZE;

typedef struct _tagRectangle
{
	float	fLeft;
	float	fTop;
	float	fRight;
	float	fBottom;

	_tagRectangle() :
		fLeft(0.f),
		fTop(0.f),
		fRight(0.f),
		fBottom(0.f)
	{
	}

	_tagRectangle(float fL, float fT, float fR, float fB) :
		fLeft(fL),
		fTop(fT),
		fRight(fR),
		fBottom(fB)
	{
	}

	_tagRectangle(const _tagRectangle& rc)
	{
		*this = rc;
	}

	void operator =(const _tagRectangle& rc)
	{
		fLeft = rc.fLeft;
		fTop = rc.fTop;
		fRight = rc.fRight;
		fBottom = rc.fBottom;
	}

	_tagRectangle operator +(const _tagRectangle& rc)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft + rc.fLeft;
		tRC.fTop = fTop + rc.fTop;
		tRC.fRight = fRight + rc.fRight;
		tRC.fBottom = fBottom + rc.fBottom;

		return tRC;
	}

	_tagRectangle operator +(const RECT& rc)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft + rc.left;
		tRC.fTop = fTop + rc.top;
		tRC.fRight = fRight + rc.right;
		tRC.fBottom = fBottom + rc.bottom;

		return tRC;
	}

	_tagRectangle operator +(const POSITION& pt)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft + pt.x;
		tRC.fTop = fTop + pt.y;
		tRC.fRight = fRight + pt.x;
		tRC.fBottom = fBottom + pt.y;

		return tRC;
	}

	_tagRectangle operator +(const POINT& pt)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft + pt.x;
		tRC.fTop = fTop + pt.y;
		tRC.fRight = fRight + pt.x;
		tRC.fBottom = fBottom + pt.y;

		return tRC;
	}

	// -
	_tagRectangle operator -(const _tagRectangle& rc)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft - rc.fLeft;
		tRC.fTop = fTop - rc.fTop;
		tRC.fRight = fRight - rc.fRight;
		tRC.fBottom = fBottom - rc.fBottom;

		return tRC;
	}

	_tagRectangle operator -(const RECT& rc)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft - rc.left;
		tRC.fTop = fTop - rc.top;
		tRC.fRight = fRight - rc.right;
		tRC.fBottom = fBottom - rc.bottom;

		return tRC;
	}

	_tagRectangle operator -(const POSITION& pt)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft - pt.x;
		tRC.fTop = fTop - pt.y;
		tRC.fRight = fRight - pt.x;
		tRC.fBottom = fBottom - pt.y;

		return tRC;
	}

	_tagRectangle operator -(const POINT& pt)
	{
		_tagRectangle	tRC;

		tRC.fLeft = fLeft - pt.x;
		tRC.fTop = fTop - pt.y;
		tRC.fRight = fRight - pt.x;
		tRC.fBottom = fBottom - pt.y;

		return tRC;
	}

	void operator -=(const POSITION& pt)
	{
		fLeft = fLeft - pt.x;
		fTop = fTop - pt.y;
		fRight = fRight - pt.x;
		fBottom = fBottom - pt.y;
	}
}RECTANGLE, *PRECTANGLE;

// Sphere
typedef struct _tagSphere
{
	POSITION	tCenter;
	float		fRadius;

	_tagSphere() :
		tCenter(0.f, 0.f),
		fRadius(0.f)
	{
	}

	_tagSphere(const _tagSphere& rhs)
	{
		*this = rhs;
	}

	_tagSphere(float x, float y, float r) :
		tCenter(x, y),
		fRadius(r)
	{
	}

	_tagSphere(const POSITION& tC, float r) :
		tCenter(tC),
		fRadius(r)
	{
	}

	_tagSphere(const POINT& tC, float r) :
		tCenter(tC.x, tC.y),
		fRadius(r)
	{
	}

	void operator =(const _tagSphere& tSphere)
	{
		tCenter = tSphere.tCenter;
		fRadius = tSphere.fRadius;
	}

	_tagSphere operator +(const _tagSphere& tSphere)
	{
		_tagSphere	tSp;

		tSp.tCenter = tCenter + tSphere.tCenter;
		tSp.fRadius = fRadius + tSphere.fRadius;

		return tSp;
	}

	_tagSphere operator +(const POSITION& tC)
	{
		_tagSphere	tSphere;

		tSphere.tCenter = tCenter + tC;
		tSphere.fRadius = fRadius;

		return tSphere;
	}

	_tagSphere operator +(const POINT& pt)
	{
		_tagSphere	tSphere;

		tSphere.tCenter = tCenter + pt;
		tSphere.fRadius = fRadius;

		return tSphere;
	}

	void operator +=(const _tagSphere& tSphere)
	{
		tCenter += tSphere.tCenter;
		fRadius += tSphere.fRadius;
	}

	void operator +=(const POSITION& tPos)
	{
		tCenter += tPos;
	}

	void operator +=(const POINT& pt)
	{
		tCenter += pt;
	}

	// -
	_tagSphere operator -(const _tagSphere& tSphere)
	{
		_tagSphere	tSp;

		tSp.tCenter = tCenter - tSphere.tCenter;
		tSp.fRadius = fRadius - tSphere.fRadius;

		return tSp;
	}

	_tagSphere operator -(const POSITION& tPos)
	{
		_tagSphere	tSphere;

		tSphere.tCenter = tCenter - tPos;
		tSphere.fRadius = fRadius;

		return tSphere;
	}

	_tagSphere operator -(const POINT& pt)
	{
		_tagSphere	tSphere;

		tSphere.tCenter = tCenter - pt;
		tSphere.fRadius = fRadius;

		return tSphere;
	}

	void operator -=(const POSITION& pt)
	{
		tCenter -= pt;
	}
}SPHERE, *PSPHERE;

// 24Bit Pixel
typedef struct _tagPixel24
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}PIXEL24, *PPIXEL24;

typedef struct _tagPixelColliderInfo
{
	vector<PIXEL24>		vecPixel;
	UINT		iWidth;
	UINT		iHeight;
	PIXEL24		tCollPixel;
	POSITION	tIntersectPos;
}PIXELCOLLIDERINFO, *PPIXELCOLLIDERINFO;

enum ANIMATION_TYPE
{
	AT_LINE,
	AT_ALL
};

enum ANIMATION_OPTION
{
	AO_ONCE,
	AO_LOOP
};

// Collider Type
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_PIXEL,
	CT_POINT,
	CT_TILEMAP
};

// Button State
enum BUTTON_STATE
{
	BS_NONE,
	BS_MOUSEON,
	BS_CLICK
};

// Scene Change
enum SCENE_CHANGE
{
	SC_NONE,
	SC_CHANGE
};

// Tile
enum ITEM_INFO
{
	II_NONE,
	II_BUBBLE,
	II_FLASK,
	II_SPEED,
	II_BOOM,
	II_REDDEVIL,
	II_SHOES
};

enum EDIT_MODE
{
	EM_FLAG,
	EM_TILE
};

enum TILE_FLAG
{
	TF_NONE,
	TF_NOMOVE
};

enum MAP_TYPE
{
	MT_ONE,
	MT_TWO
};

enum TILE_IMAGE
{
	TI_NONE,
	TI_BOX0,
	TI_BOX1,
	TI_BOX2,
	TI_HOUSE0,
	TI_HOUSE1,
	TI_HOUSE2,
	TI_MOVETREE,
	TI_NOMOVETREE,						// map1
	TI_BOX3,
	TI_BOX4,
	TI_BOX5,
	TI_BOX6,
	TI_BOX7								// map2
};


typedef struct _tagTileMapColliderInfo
{
	UINT					iTileX;
	UINT					iTileY;
	UINT					iTileSizeX;
	UINT					iTileSizeY;
	vector<TILE_FLAG>		vecTileFlag;
	RECTANGLE				tIntersectRC;
}TILEMAPCOLLIDERINFO, *PTILEMAPCOLLIDERINFO;

// Monster AI

enum MONSTER_ANIMATION
{
	MA_DOWN,
	MA_LEFT,
	MA_RIGHT,
	MA_UP,
	MA_DIE
};
