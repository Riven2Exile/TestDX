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
	std::string szKey;		//纹理关键字，查找用的
	std::string szfilename; //纹理名字

	stTexInfo():pTex(0),weight(0),height(0){

	}

	void LightClear(){
		weight = 0;
		height = 0;
		szKey = "";
		szfilename = "";
		pTex = nullptr;
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
    


//     IDirect3DTexture9* getTexture(const char* strKey);
//     IDirect3DTexture9* getTexture(std::string strKey);

	const stTexInfo* getTexture(std::string strKey) const;
	const stTexInfo* getTexture(const char* strKey) const;


	void DeviceReset();

private:
	typedef std::map<unsigned int, stTexInfo> MAP_TEX;
    MAP_TEX m_data;
};



#endif