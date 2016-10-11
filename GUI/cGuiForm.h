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

	virtual void SetOffSet(const int& x, const int& y);

    ////////// 消息处理
    //int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag);
    //int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
    //int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);

private:
    

    std::string _strName;   //界面名
};


#endif