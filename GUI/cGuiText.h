#ifndef _L_GUITEXT_H
#define _L_GUITEXT_H

#include "cGuiControl.h"

///// 标签可以加文字, 支持单一颜色

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

	DWORD _dwTextColor;		//文字颜色
};

#endif