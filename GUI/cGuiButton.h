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
        kBS_Normal,     //��̬ͨ
        kBS_MouseOn,    //��긡��̬
        kBS_Clicked,    //ѡ��̬
        kBS_Disable,    //��Ч̬

        kBS_Num,
    };


    explicit cGuiButton(cGuiControl* pFather);
    virtual ~cGuiButton();

    void SetBtnStateImage(eBtnState state, const char* szName);
    void SetBtnState(eBtnState e);
    inline eBtnState GetBtnState();

    ////// ��Ϣ����
    int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);

    ///// ��Ϣҵ����Ӧ
    void SetClickFun(CtrlClickFun);
	void SetPressDownFun(Fun_BtnMouse func);
	void SetPressUpFun(Fun_BtnMouse func);
	void SetPressedMouseMoveFun(Fun_BtnMouse func);

	// ����, �ſ�,   ?����?

private:

    /////// ��Ϣ��ҵ����Ӧ..
    int OnBtnClicked();
    CtrlClickFun _pFun;

	Fun_BtnMouse _pFunPressDown;
	Fun_BtnMouse _pFunPressUp;
	Fun_BtnMouse _pFunPressedMouseMove; //��ס��ʱ����궯

    //////
    void HandleMouseOn();
    void HandleMouseLeave();
    // ������̬

    eBtnState _btnState;            //��ť״̬
    std::string _strImage[kBS_Num]; //���õ�����
};


#endif