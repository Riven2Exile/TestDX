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

    // �Ȳ����ظ�.. �Է�ֹ�ظ�
    MAP_S2DLG::iterator itr = _mapDlg.find(pszName);
    if (itr != _mapDlg.end())
    {
        // !!!!!! �ظ���UI
        printf("�ظ���UI :%s, ����! \n", pszName);
        return false;
    }
    else
    {
        _mapDlg[pszName] = pDlg; // GetName() -->  

        // --> todo: ����json
        std::string str = DIR_UI_JSON;
        str += pszName;
        str += SUFFIX_UI;
        
		// ���ʹ��JSON
        //CGuiLayoutFileMgr::Instance().HandleALayoutFile(str.c_str());

		
		pDlg->Show(false);	//Ĭ�ϲ���ʾ
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