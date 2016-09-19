#include "cGuiLable.h"

cGuiLable::cGuiLable(cGuiControl* pFather) :cGuiControl(pFather)
{
    SetCtrlType(kCT_GuiLable);
}

cGuiLable::~cGuiLable()
{

}

/////////////////

void cGuiLable::SetText(const char* str)
{
	if (str) {
		_strText = str;

		//…Ë÷√øÌ∏ﬂ
		SetHeight(24);
		SetWidth(12 * _strText.length());
	}
}

const char* cGuiLable::GetText()
{
	return _strText.c_str();
}

void cGuiLable::SetTextColor(const DWORD& dwColor)
{
	_dwTextColor = dwColor;
}

DWORD cGuiLable::GetTextColor() const{
	return _dwTextColor;
}
