#ifndef _L_GUITEXT_H
#define _L_GUITEXT_H

#include "cGuiControl.h"

///// ��ǩ���Լ�����, ֧�ֵ�һ��ɫ

class cGuiText : public cGuiControl
{
public:
	explicit cGuiText(cGuiControl* pFather);
	virtual ~cGuiText();

	void SetText(const char* str);
	const char* GetText();

	void SetTextColor(const DWORD& dwColor);
	DWORD GetTextColor() const;

private:

	DWORD _dwTextColor;		//������ɫ
};

#endif