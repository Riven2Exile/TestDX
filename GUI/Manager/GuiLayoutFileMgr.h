#ifndef GUI_LAYOUT_FILE_MGR_H
#define GUI_LAYOUT_FILE_MGR_H

#include "..\..\ToolLib\json\include\json\value.h"

/// UI 布局文件管理


class Json::Value;


//控件类型

enum eCtrlType
{
    kCT_dlg     = 0,    //对话框
    kCT_button  = 1,    //按钮
    kCT_lable   = 2,    //标签

    nCT_MaxNum,   //最大值
};

class CGuiLayoutFileMgr;

// 返回值设为void居然错了? 
typedef bool (CGuiLayoutFileMgr::*FuncParse)(cGuiControl * pCtrl, const char*, Json::Value) ;
//typedef bool (*pFunFun) (const char*, Json::Value) ;

class CGuiLayoutFileMgr
{
public:
    CGuiLayoutFileMgr();
    virtual ~CGuiLayoutFileMgr();

    static CGuiLayoutFileMgr& Instance();

    bool LoadAllLayoutFile(); // 加载所有UI布局文件

    bool LoadALayoutFile(const char* pszName, Json::Value& Value);

    bool HandleALayoutFile(const char* pszName);    //载入并处理一个UI布局文件


    cGuiControl* CreateControl(Json::Value v);   //控件工厂
    bool Parse(cGuiControl * pCtrl,const char* szKey, Json::Value v);
    bool ParseAddSubCtrl(cGuiControl *pCtrl, const char* szKey, Json::Value v); //增加子控件
    bool ParseBtn(cGuiControl* pCtrl, const char* szKey, Json::Value v);        //按钮特殊属性

private:

    void Init();

    

    // 各种解析了
    //void 


    // 通过key , value 来决定 同什么函数来解析
    typedef std::map<std::string, FuncParse> MAP_FUN;
    MAP_FUN _pFun;
};


#endif