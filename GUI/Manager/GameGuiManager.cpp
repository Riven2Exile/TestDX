#include "stdafx.h"
#include "GameGuiManager.h"
#include "GuiLayoutFileMgr.h"
#include "..\..\GameMain.h"


CGameGuiMgr::CGameGuiMgr()
{

}
CGameGuiMgr::~CGameGuiMgr()
{

}

CGameGuiMgr& CGameGuiMgr::Instance()
{
    static CGameGuiMgr inst;
    return inst;
}

void CGameGuiMgr::LoadGuiFile(const char* szPath)
{
    if(NULL == szPath)
        return ;



    // 
}


bool CGameGuiMgr::RegisterDlg(const char* pszName, cGuiControl *pDlg)
{
    if( NULL == pszName || NULL == pDlg)
        return false;

    // 先查找重复.. 以防止重复
    MAP_S2DLG::iterator itr = _mapDlg.find(pszName);
    if (itr != _mapDlg.end())
    {
        // !!!!!! 重复的UI
        printf("重复的UI :%s, 请检查! \n", pszName);
        return false;
    }
    else
    {
        _mapDlg[pszName] = pDlg; // GetName() -->  

        // --> todo: 解析json
        std::string str = DIR_UI_JSON;
        str += pszName;
        str += SUFFIX_UI;
        
		// 如果使用JSON
        //CGuiLayoutFileMgr::Instance().HandleALayoutFile(str.c_str());

		
		pDlg->Show(false);	//默认不显示
        CGameMain::Instance().AddGui(pDlg);

        return true;
    }
}


cGuiControl* CGameGuiMgr::FindControl(const char* pszName)
{
    MAP_S2DLG::iterator itr = _mapDlg.find(pszName);
    if (itr != _mapDlg.end())
    {
        return itr->second;
    }

    return NULL;
}