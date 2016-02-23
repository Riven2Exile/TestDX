#include "stdafx.h"
#include "GameGuiManager.h"
#include "RegisterGui.h"
#include "..\BusinessLogic\TestDlg.h"


//// ���������Զ��ɱ༭������
//         ���༭����Ҫ������������趨·�� �� RegisterGui.cpp��·�� (���)
// ���� include ,  

#define REGISTRT_GUI(className,name) \
    { \
        className *p = new className; \
        if(p) \
        { \
            CGameGuiMgr::Instance().RegisterDlg(name, p); \
        } \
    }\




CRegisterGui::CRegisterGui()
{
    printf("start register gui! \n");
    // todo: load all gui layout config

    // todo: register gui
    REGISTRT_GUI(CTestDlg, "CTestDlg");

}



