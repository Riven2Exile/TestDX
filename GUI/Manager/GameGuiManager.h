#ifndef GAME_GUI_MANAGER_H
#define GAME_GUI_MANAGER_H

/*
    单窗口使用的gui 管理器， 里面可能有各种对话框 ,  想象一下操作系统的桌面
*/


class CGameGuiMgr
{
public:
    CGameGuiMgr();
    virtual ~CGameGuiMgr();

    static CGameGuiMgr& Instance();
    
    void LoadGuiFile(const char* szName);

    bool RegisterDlg(const char* pszName, cGuiControl *pDlg);

    cGuiControl* FindControl(const char* pszName);

private:
    typedef std::map<std::string, cGuiControl*> MAP_S2DLG;
    typedef std::map<DWORD, cGuiControl*> MAP_I2DLG;
    typedef std::list<cGuiControl*> LIST_DLG;


    MAP_S2DLG _mapDlg;      //查找集合 ..为了查找
    MAP_I2DLG _mapID2Dlg;    //查找集合 ..为了查找 (如果上面的map载完, 可以通过上面的map生成本map )

    LIST_DLG _listDlg;    //界面集合 ..为了绘制顺序 ..引用指针
};

#endif