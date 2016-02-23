#ifndef _L_GUIFORM_H
#define _L_GUIFORM_H

#include "cGuiControl.h"

class cGuiForm : public cGuiControl
{
public:
    explicit cGuiForm(cGuiControl* pFather);
	cGuiForm();
    virtual ~cGuiForm();

    virtual void SetName(const char* pszName = "");

    void Show(bool bShow /* = true */);

    ////////// 消息处理
    int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);

private:
    bool _bClicked;

    int _dragX;     // 拖动时， 在对话框的相对偏移
    int _dragY;

    std::string _strName;   //界面名
};


#endif