
/*  游戏逻辑主框架 



1. 用于update
    --> 帧数管理

2. 用于draw



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

// 绘制流
struct MDDrawDynamic
{
    //混合选项~

    //纹理~

    //使用了多少个
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



    /////// 输入相关...
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

    iSprite* m_sp[TEST_SIZE];//test大量
    
    //控件
    cGuiButton *m_pCtrlTest;
    cGuiControl *m_pDlgTest;

    cGuiForm *m_pCtrlDlg2;

    // 动画
    CFAnimation m_AniAuto;  //自动
    CFAnimation m_Ani;


    // GUI管理
    cGuiMgr _gui;

    //积木
    /*Tetris::*/TetrisWorldView* _pTWorld;


private:
    void registerMessage();
    void initAnimation();
};


iSprite* CreateSprite(SpriteType nType);

#endif