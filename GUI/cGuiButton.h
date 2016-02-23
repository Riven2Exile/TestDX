#ifndef _L_GUIBUTTON_H
#define _L_GUIBUTTON_H


#include "cGuiControl.h"

typedef void (cGuiControl::*CtrlClickFun)(int);

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

private:

    /////// ��Ϣ��ҵ����Ӧ..
    int OnBtnClicked();
    CtrlClickFun _pFun;

    //////
    void HandleMouseOn();
    void HandleMouseLeave();
    // ������̬

    eBtnState _btnState;            //��ť״̬
    std::string _strImage[kBS_Num]; //���õ�����
};


#endif