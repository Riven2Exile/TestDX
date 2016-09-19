#include "cGuiText.h"

cGuiText::cGuiText(cGuiControl* pFather) :cGuiControl(pFather)
, _dwTextColor(0xff000000) //Ĭ�Ϻ�ɫ
{
	_sprite->setVisible(false);//������ʾ
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

		//���ÿ��
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
