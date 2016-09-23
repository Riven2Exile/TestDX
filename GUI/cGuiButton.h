#ifndef _L_GUIBUTTON_H
#define _L_GUIBUTTON_H


#include "cGuiControl.h"
#include <functional>

class cGuiButton;

typedef void (cGuiControl::*CtrlClickFun)(int);
typedef std::function<void(cGuiButton* pBtn)> Fun_Btn;
typedef std::function<void(cGuiButton*, const int&, const int&)> Fun_BtnMouse;

class cGuiButton : public cGuiControl
{
public:
    enum eBtnState{
        kBS_Normal,     //普通态
        kBS_MouseOn,    //光标浮动态
        kBS_Clicked,    //选中态
        kBS_Disable,    //无效态

        kBS_Num,
    };


    explicit cGuiButton(cGuiControl* pFather);
    virtual ~cGuiButton();

    void SetBtnStateImage(eBtnState state, const char* szName);
    void SetBtnState(eBtnState e);
    inline eBtnState GetBtnState();

    ////// 消息处理
    int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);

    ///// 消息业务响应
    void SetClickFun(CtrlClickFun);
	void SetPressDownFun(Fun_BtnMouse func);
	void SetPressUpFun(Fun_BtnMouse func);
	void SetPressedMouseMoveFun(Fun_BtnMouse func);

	// 按下, 放开,   ?长按?

private:

    /////// 消息的业务响应..
    int OnBtnClicked();
    CtrlClickFun _pFun;

	Fun_BtnMouse _pFunPressDown;
	Fun_BtnMouse _pFunPressUp;
	Fun_BtnMouse _pFunPressedMouseMove; //按住的时候鼠标动

    //////
    void HandleMouseOn();
    void HandleMouseLeave();
    // 其他三态

    eBtnState _btnState;            //按钮状态
    std::string _strImage[kBS_Num]; //所用的纹理
};


#endif