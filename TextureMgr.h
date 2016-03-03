/*
    简单的纹理管理 (后面需要用观察者吗?)
*/

#ifndef _TEXTUTRE_H
#define _TEXTUTRE_H

#include <string>
#include <map>


struct IDirect3DTexture9;

struct stTexInfo
{
	IDirect3DTexture9* pTex;
	int weight;	//宽度
	int height;	//高度

	stTexInfo():pTex(0),weight(0),height(0){

	}
};


// BKDR Hash Function
unsigned int BKDRHash(const char *str);



class CTextureMgr
{
public:
    CTextureMgr();
    ~CTextureMgr();

    static CTextureMgr& instance(){
        static CTextureMgr inst;
        return inst;
    }

    void addTexture(const char* szName, std::string strKey);
    void addTexture(IDirect3DTexture9* pTex, std::string strKey);
    


    IDirect3DTexture9* getTexture(const char* strKey);
    IDirect3DTexture9* getTexture(std::string strKey);

private:
	typedef std::map<unsigned int, stTexInfo> MAP_TEX;
    MAP_TEX m_data;
};



#endif