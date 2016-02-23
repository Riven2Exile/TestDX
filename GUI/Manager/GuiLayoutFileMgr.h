#ifndef GUI_LAYOUT_FILE_MGR_H
#define GUI_LAYOUT_FILE_MGR_H

#include "..\..\ToolLib\json\include\json\value.h"

/// UI �����ļ�����


class Json::Value;


//�ؼ�����

enum eCtrlType
{
    kCT_dlg     = 0,    //�Ի���
    kCT_button  = 1,    //��ť
    kCT_lable   = 2,    //��ǩ

    nCT_MaxNum,   //���ֵ
};

class CGuiLayoutFileMgr;

// ����ֵ��Ϊvoid��Ȼ����? 
typedef bool (CGuiLayoutFileMgr::*FuncParse)(cGuiControl * pCtrl, const char*, Json::Value) ;
//typedef bool (*pFunFun) (const char*, Json::Value) ;

class CGuiLayoutFileMgr
{
public:
    CGuiLayoutFileMgr();
    virtual ~CGuiLayoutFileMgr();

    static CGuiLayoutFileMgr& Instance();

    bool LoadAllLayoutFile(); // ��������UI�����ļ�

    bool LoadALayoutFile(const char* pszName, Json::Value& Value);

    bool HandleALayoutFile(const char* pszName);    //���벢����һ��UI�����ļ�


    cGuiControl* CreateControl(Json::Value v);   //�ؼ�����
    bool Parse(cGuiControl * pCtrl,const char* szKey, Json::Value v);
    bool ParseAddSubCtrl(cGuiControl *pCtrl, const char* szKey, Json::Value v); //�����ӿؼ�
    bool ParseBtn(cGuiControl* pCtrl, const char* szKey, Json::Value v);        //��ť��������

private:

    void Init();

    

    // ���ֽ�����
    //void 


    // ͨ��key , value ������ ͬʲô����������
    typedef std::map<std::string, FuncParse> MAP_FUN;
    MAP_FUN _pFun;
};


#endif