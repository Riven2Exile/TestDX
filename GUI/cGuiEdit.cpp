
#include "cGuiEdit.h"

cGuiEdit::cGuiEdit(cGuiControl* pFather) : cGuiControl(pFather)
{
	SetCtrlType(kCT_GuiEdit);
	_bShowCursor = false;
	_cursor_pos = 0;

	SetGainFocusCallBack(std::bind(&cGuiEdit::callback_get_focus, this, std::placeholders::_1));
	SetLoseFocusCallBack(std::bind(&cGuiEdit::callback_lose_focus, this, std::placeholders::_1));
}

cGuiEdit::~cGuiEdit(){

}

///////

void cGuiEdit::Draw(){
	__super::Draw();

	// 画文字
	if (_strText.size())
	{
		TextOutput(GetScreenPosX(), GetScreenPosY(), _strText.c_str());
	}
	
	if (_bShowCursor)
	{
		TextOutput(GetScreenPosX(), GetScreenPosY(), "|");
	}
}


void cGuiEdit::run(const DWORD& dwElaspe)
{
	//光标闪烁 "|"
	static DWORD e = 0;
	e += dwElaspe;
	if (e >= 500)
	{
		_bShowCursor = !_bShowCursor;
		e -= 500;
	}


}




int cGuiEdit::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag){
	if (__super::OnLButtonDown(x, y, nFlag) == 0)
	{
		return 0;
	}

	// 如果命中本控件， 也当做处理
	if (IsAt(x, y))
	{
		if (IsFocus() == false)
		{
			if (GetFather()){
				GetFather()->ClearChildFocus(this); //清除掉兄弟的焦点
			}

			SetFocus(true); //获得焦点
			if (_cb_gain_focus){
				_cb_gain_focus(this);
			}
		}
		return 0;
	}
}

void cGuiEdit::callback_get_focus(cGuiControl* pCtrl){
	_bShowCursor = true;
}

void cGuiEdit::callback_lose_focus(cGuiControl* pCtrl){
	_bShowCursor = false;
}