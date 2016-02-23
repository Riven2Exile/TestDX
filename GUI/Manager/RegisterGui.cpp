#include "stdafx.h"
#include "GameGuiManager.h"
#include "RegisterGui.h"
#include "..\BusinessLogic\TestDlg.h"


//// 尽量做成自动由编辑器生成
//         而编辑器需要做的事情就是设定路径 即 RegisterGui.cpp的路径 (灵活)
// 包含 include ,  

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



