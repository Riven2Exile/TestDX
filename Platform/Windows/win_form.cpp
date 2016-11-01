#include "stdafx.h"
#include "win_form.hpp"

CWinForm::CWinForm(cGuiControl* pFather) : cGuiForm(pFather)
{

}

CWinForm::~CWinForm(){

}



void CWinForm::SetWindowsHandle(const HWND& h){
	_hwnd = h;
}

void CWinForm::SetPos(const int& x, const int& y){
	__super::SetPos(x, y);

	::SetWindowPos(_hwnd, NULL, x, y, get_width(), get_height(), SWP_SHOWWINDOW);
}

void CWinForm::SetSize(const int& w, const int& h){
	__super::SetWidth(w);
	__super::SetHeight(h);

	::SetWindowPos(_hwnd, NULL, GetScreenPosX(), GetScreenPosY(), get_width(), get_height(), SWP_SHOWWINDOW);
}