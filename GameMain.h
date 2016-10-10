
/*  ��Ϸ�߼������ 



1. ����update
    --> ֡������

2. ����draw



*/

#ifndef GAME_MAIN_H
#define GAME_MAIN_H


#include "CSprite.h"
#include "Animation.h"
#include <time.h>

#include "Tetris/TetrisWorldView.h"
#include "GUI/cGuiMgr.h"

#define TEST_SIZE 200

class cGuiControl;
class cGuiButton;
class cGuiForm;
class cGuiMgr;

// ������
struct MDDrawDynamic
{
    //���ѡ��~

    //����~

    //ʹ���˶��ٸ�
};

enum eRegisterMessage
{

};



class CGameMain
{
public:
    CGameMain();
    ~CGameMain();

    static CGameMain& Instance(){
        static CGameMain inst;
        return inst;
    }

    void AddGui(cGuiControl* pCtrl);

    void init();
	void SetWndSize(int width, int height);

    void update(DWORD elasped);
    
    void draw();



    /////// �������...
    void OnLButtonDown(const WPARAM& wParam, const LPARAM& lParam);
    void OnLButtonUp(const WPARAM& wParam, const LPARAM& lParam);
    void OnRButtonDown(const WPARAM& wParam, const LPARAM& lParam);
    void OnRButtonUp(const WPARAM& wParam, const LPARAM& lParam);

    void OnChar(const WPARAM& wParam, const LPARAM& lParam);
    void OnKeyDown(const WPARAM& wParam, const LPARAM& lParam);
    void OnKeyUP(const WPARAM& wParam, const LPARAM& lParam);

    void OnMouseMove(const WPARAM& wParam, const LPARAM& lParam);
	void OnMouseWheel(const WPARAM& wParam, const LPARAM& lParam);


private:

    //test
    iSprite* m_pTest;
	iSprite* m_SpriteWhiteCube;

    iSprite* m_sp[TEST_SIZE];//test����
    
    //�ؼ�
    cGuiButton *m_pCtrlTest;
    cGuiControl *m_pDlgTest;

    cGuiForm *m_pCtrlDlg2;

    // ����
    CFAnimation m_AniAuto;  //�Զ�
    CFAnimation m_Ani;


    // GUI����
    cGuiMgr _gui;

    //��ľ
    /*Tetris::*/TetrisWorldView* _pTWorld;


private:
    void registerMessage();
    void initAnimation();
};


iSprite* CreateSprite(SpriteType nType);

#endif