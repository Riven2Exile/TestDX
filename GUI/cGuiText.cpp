#include "cGuiText.h"

cGuiText::cGuiText(cGuiControl* pFather) :cGuiControl(pFather)
, _dwTextColor(0xff000000) //默认黑色
{
	_sprite->setVisible(false);//不可显示
	SetCtrlType(kCT_GuiLable);
}

cGuiText::~cGuiText()
{

}

/////////////////

void cGuiText::SetText(const char* str)
{
	if (str) {
		_strText = str;

		//设置宽高
		SetHeight(24);
		SetWidth(12 * _strText.length());
	}
}

const char* cGuiText::GetText()
{
	return _strText.c_str();
}

void cGuiText::SetTextColor(const DWORD& dwColor)
{
	_dwTextColor = dwColor;
}

DWORD cGuiText::GetTextColor() const{
	return _dwTextColor;
}
