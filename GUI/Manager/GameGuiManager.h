#ifndef GAME_GUI_MANAGER_H
#define GAME_GUI_MANAGER_H

/*
    ������ʹ�õ�gui �������� ��������и��ֶԻ��� ,  ����һ�²���ϵͳ������
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


    MAP_S2DLG _mapDlg;      //���Ҽ��� ..Ϊ�˲���
    MAP_I2DLG _mapID2Dlg;    //���Ҽ��� ..Ϊ�˲��� (��������map����, ����ͨ�������map���ɱ�map )

    LIST_DLG _listDlg;    //���漯�� ..Ϊ�˻���˳�� ..����ָ��
};

#endif