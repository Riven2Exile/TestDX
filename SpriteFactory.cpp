
#include <map>
#include "SpriteFactory.h"
#include "CSprite.h"
#include "CMSprite.h"

std::map<void*, iSprite*> g_map_sprite;

///// 写个工厂方法
iSprite* CreateSprite(SpriteType nType)
{
	if (ST_MX == nType)
	{
		iSprite* p = new CSprite;
		g_map_sprite[p] = p;
		return p;
	}
	else if (ST_3D == nType)
	{
		iSprite* p = new CMSprite;
		g_map_sprite[p] = p;
		return p;
	}

	return nullptr;
}

void ReleaseSprite(iSprite* p){

}

void ResetDeviceLost(){
	for (auto& v : g_map_sprite)
	{
		
	}
}

// 不能使用,,,因为基类不知道子类的大小...每次都是移动4...
iSprite* CreateSprite(SpriteType nType, unsigned int nSize)
{
	if (ST_MX == nType)
	{
		return new CSprite[nSize];
	}
	else if (ST_3D == nType)
	{
		return new CMSprite[nSize];
	}

	return nullptr;
}