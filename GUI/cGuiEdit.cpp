
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

	// ������
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
	//�����˸ "|"
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

	// ������б��ؼ��� Ҳ��������
	if (IsAt(x, y))
	{
		if (IsFocus() == false)
		{
			if (GetFather()){
				GetFather()->ClearChildFocus(this); //������ֵܵĽ���
			}

			SetFocus(true); //��ý���
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