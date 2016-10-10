/*
    �򵥵�������� (������Ҫ�ù۲�����?)
*/

#ifndef _TEXTUTRE_H
#define _TEXTUTRE_H

#include <string>
#include <map>


struct IDirect3DTexture9;

struct stTexInfo
{
	IDirect3DTexture9* pTex;
	int weight;	//���
	int height;	//�߶�
	std::string szKey;		//����ؼ��֣������õ�
	std::string szfilename; //��������

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