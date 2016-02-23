#include "stdafx.h"
#include "GuiLayoutFileMgr.h"
#include "..\..\ToolLib\json\include\json\reader.h"
#include "GameGuiManager.h"
#include <assert.h>



#define CHECK(str) strcmp(szKey, str) == 0


// const char* g_strCfg[nCT_MaxNum][] = 
// {
//     {"type", "name", },
// };

CGuiLayoutFileMgr::CGuiLayoutFileMgr()
{
    Init();
}

CGuiLayoutFileMgr::~CGuiLayoutFileMgr()
{

}

////////

CGuiLayoutFileMgr& CGuiLayoutFileMgr::Instance()
{
    static CGuiLayoutFileMgr inst;
    return inst;
}

void CGuiLayoutFileMgr::Init()
{
    // 普通
    const char* arrNormal[] = {"type", "name", "id", "pos", "width", "height", "image", "visul"};
    int nSize = sizeof(arrNormal) / sizeof(arrNormal[0]);
    for (int i = 0; i < nSize; ++i)
    {
        _pFun[ arrNormal[i] ] = (FuncParse)&CGuiLayoutFileMgr::Parse; //类成员的函数指针的引用  (强转..!)
    }
    // _pFun["name"]   = (FuncParse)&CGuiLayoutFileMgr::Parse;

    //子控件
    _pFun[ "subCtrl" ] = (FuncParse)&CGuiLayoutFileMgr::ParseAddSubCtrl;
   
    //按钮
    _pFun["image_btn"] = (FuncParse)&CGuiLayoutFileMgr::ParseBtn;
}


bool CGuiLayoutFileMgr::LoadAllLayoutFile()
{
    // path 
    HandleALayoutFile("D:/Cplusplus_Workplace/TestDX/Game/UI/TestDlg.ui");
    

    return true;
}


bool CGuiLayoutFileMgr::LoadALayoutFile(const char* pszName, Json::Value& Value)
{
    Json::Reader reader;
    FILE *pfile = fopen(pszName, "r");
    if (pfile)
    {
        int nlen = 0;
        fseek(pfile, 0, SEEK_END);
        nlen = ftell(pfile);
        fseek(pfile, 0, SEEK_SET);
        char* pBuf = new char[nlen];
        fread(pBuf, 1, nlen, pfile);
        fclose(pfile);
        reader.parse(pBuf, Value);
        delete[] pBuf;
    }
    return true;
}


bool CGuiLayoutFileMgr::HandleALayoutFile(const char* pszName)
{
    Json::Value v;
    LoadALayoutFile(pszName, v);

    //默认属性  对话框有什么属性
    Json::Value::Members m = v.getMemberNames();
    int nSize = m.size();
    Json::Value v2;
    Json::Value v3;
    v2 = v.get("type",v2); // 应该设定一些固定的默认值的Value对象 

    v2 = v.get("name", v2);
    cGuiControl * pCtrl = CGameGuiMgr::Instance().FindControl(v2.asCString());
    if (pCtrl)
    {
        Json::Value::Members::iterator itr = m.begin();
        for ( ; itr != m.end(); ++itr)
        {
            v2 = v.get(*itr, v2);
            const char* szKey = (*itr).c_str();
            MAP_FUN::iterator itr = _pFun.find(szKey);
            if (itr != _pFun.end())
            {
                FuncParse p = itr->second;
                (this->*p)(pCtrl, szKey, v2); //parse 调用类的函数指针!!!
            }
        }
    }

    //对话框什么属性, 按钮什么属性
    // 对话框名字找类

    return true;
}

cGuiControl* CGuiLayoutFileMgr::CreateControl(Json::Value v)
{
    Json::Value vT;
    vT = v.get("type", vT);
    const char* szKey = vT.asCString();

    if (CHECK("button"))
    {
		assert(0);
        return NULL;//new cGuiButton;
    }
    else if (CHECK("lable"))
    {
		assert(0);
        return NULL;//new cGuiLable;
    }

    if (szKey)
    {
        printf("不存在的控件类型%s\n", szKey);
    } 

    return NULL;
}

bool CGuiLayoutFileMgr::Parse(cGuiControl * pCtrl, const char* szKey, Json::Value v)
{
    if (CHECK("id")){   
        pCtrl->SetID(v.asInt());
    }
    else if (CHECK("height")){
        pCtrl->SetHeight(v.asInt());
    }
    else if (CHECK("width") ){
        pCtrl->SetWidth( v.asInt() );
    }
    else if (CHECK("pos")) {
        pCtrl->SetPos(v[0].asInt(), v[1].asInt());
    }
    else if (CHECK("image")) {
        pCtrl->SetTexture( v.asCString() );
    }
    else if (CHECK("visul")) {
        pCtrl->Show(v.asInt());
    }



    return true;
}


bool CGuiLayoutFileMgr::ParseAddSubCtrl(cGuiControl *pCtrl, const char* szKey, Json::Value v)
{
    if (CHECK("subCtrl"))
    {
        // 递归搞起
        int n = v.type();
        int nSize = v.size();
        for (int i = 0; i < nSize; ++i)
        {
            Json::Value obj;
            obj = v[i];
            
            cGuiControl *pCtrlSub = CreateControl(obj);
            if (pCtrlSub)
            {
                Json::Value::Members m = obj.getMemberNames();
                Json::Value v2;
                v2 = obj.get("type",v2); // 应该设定一些固定的默认值的Value对象 

                v2 = obj.get("name", v2);
                {
                    Json::Value::Members::iterator itr = m.begin();
                    for ( ; itr != m.end(); ++itr)
                    {
                        v2 = obj.get(*itr, v2);
                        const char* szKeyS = (*itr).c_str();
                        MAP_FUN::iterator itr = _pFun.find(szKeyS);
                        if (itr != _pFun.end())
                        {
                            FuncParse p = itr->second;
                            (this->*p)(pCtrlSub, szKeyS, v2); //parse 调用类的函数指针!!!
                        }
                    }
                }

                pCtrl->AddControl(pCtrlSub); //添加子控件
            }

        }
    }

    return true;
}

bool CGuiLayoutFileMgr::ParseBtn(cGuiControl* pCtrl, const char* szKey, Json::Value v)
{
    cGuiButton* pBtn = dynamic_cast<cGuiButton*>(pCtrl);
    if (pBtn)
    {
        if (CHECK("image_btn"))
        {
            pBtn->SetBtnStateImage(cGuiButton::kBS_Normal, v[0].asCString());
            pBtn->SetBtnStateImage(cGuiButton::kBS_MouseOn, v[1].asCString());
            pBtn->SetBtnStateImage(cGuiButton::kBS_Clicked, v[2].asCString());
            pBtn->SetBtnStateImage(cGuiButton::kBS_Disable, v[3].asCString());
        }
        
        return true;
    }
    else
    {
        return false;
    }
}







#undef CHECK