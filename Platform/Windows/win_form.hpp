// Õë¶ÔwindowsµÄ´°Ìå

#ifndef _WIN_FORM_H
#define _WIN_FORM_H

#include "../../GUI/cCommonGuiHead.h"



class CWinForm : public cGuiForm
{
public:
	explicit CWinForm(cGuiControl* pFather);
	virtual ~CWinForm();



	void SetWindowsHandle(const HWND& h);
	virtual void SetPos(const int& x, const int& y);
	void SetSize(const int& w, const int& h);

protected:
	HWND _hwnd;
};


#endif