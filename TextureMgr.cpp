#include "stdafx.h"
#include "TextureMgr.h"
#include <assert.h>

unsigned int BKDRHash(const char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}



extern IDirect3DDevice9 *g_pDevice;

CTextureMgr::CTextureMgr()
{

}
CTextureMgr::~CTextureMgr()
{

}

////////////////////////////////////////
void CTextureMgr::addTexture(const char* szName, std::string strKey)
{
    if(NULL == szName)
        return ;

    D3DXIMAGE_INFO info;
    D3DXGetImageInfoFromFileA(szName, &info);


	stTexInfo tInfo;
	tInfo.weight = info.Width;
	tInfo.height = info.Height;
	tInfo.szKey = strKey;
	tInfo.szfilename = szName;

    //// 原来的 D3DUSAGE_DYNAMIC ， D3DPOOL_DEFAULT
    int usage = 0; D3DUSAGE_DYNAMIC;
    int pool = D3DPOOL_MANAGED; D3DPOOL_DEFAULT;

	//IDirect3DTexture9* pTemp = NULL;

    D3DXCreateTextureFromFileExA(g_pDevice, szName, info.Width, info.Height, 
        info.MipLevels, usage, info.Format, (D3DPOOL)pool, D3DX_FILTER_NONE/*D3DX_FILTER_TRIANGLE*/,  // D3DPOOL_DEFAULT才可行。。
		D3DX_FILTER_NONE/*D3DX_FILTER_TRIANGLE*/, 0/*D3DCOLOR_ARGB(255,255,255,255)*/, NULL, NULL, /*&pTemp*/&tInfo.pTex); //坑.. D3DCOLOR_ARGB(255,255,255,255) --> 会将纹理中白色的点替换成黑色,0 禁用之

	
// 	g_pDevice->CreateTexture(info.Width, info.Height, info.MipLevels, 0, info.Format, D3DPOOL_SYSTEMMEM, &tInfo.pTex, NULL);
// 	g_pDevice->UpdateTexture(pTemp, tInfo.pTex);


	const unsigned int& n = BKDRHash(strKey.c_str());

	if (tInfo.pTex)
    {
#ifdef _DEBUG
		if (m_data.find(n) != m_data.end())
		{
			assert(!"纹理hash冲突");
		}
#endif

		m_data[n] = tInfo;
    }
}

void CTextureMgr::addTexture(IDirect3DTexture9* pTex, std::string strKey)
{
//     if (pTex)
//     {
//         m_data[BKDRHash(strKey.c_str())] = pTex;
//     }
}


// IDirect3DTexture9* CTextureMgr::getTexture(const char* szName)
// {
//     MAP_TEX::iterator itr = m_data.find(BKDRHash(szName));
//     if (itr != m_data.end())
//     {
//         return itr->second.pTex;
//     }
//     else
//         return NULL;
// }

// IDirect3DTexture9* CTextureMgr::getTexture(std::string szName)
// {
//     MAP_TEX::iterator itr = m_data.find(BKDRHash(szName.c_str()));
//     if (itr != m_data.end())
//     {
//         return itr->second.pTex;
//     }
//     else
//         return NULL;
// }

const stTexInfo* CTextureMgr::getTexture(std::string strKey) const{
	return getTexture(strKey.c_str());
}

const stTexInfo* CTextureMgr::getTexture(const char* strKey) const{
	auto itr = m_data.find(BKDRHash(strKey));
	if (itr != m_data.end())
	{
		return &itr->second;
	}
	else
		return NULL;
}

void CTextureMgr::DeviceReset(){
	for (auto & info : m_data) {
		info.second.pTex->Release();
		info.second.pTex = nullptr;
		addTexture(info.second.szfilename.c_str(), info.second.szKey.c_str());
	}
}