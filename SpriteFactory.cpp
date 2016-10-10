
#include <map>
#include "SpriteFactory.h"
#include "CSprite.h"
#include "CMSprite.h"

std::map<void*, iSprite*> g_map_sprite;

///// д����������
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

// ����ʹ��,,,��Ϊ���಻֪������Ĵ�С...ÿ�ζ����ƶ�4...
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