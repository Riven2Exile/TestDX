#ifndef _L_GUILABLE_H
#define _L_GUILABLE_H

#include "cGuiControl.h"

///// 标签可以加文字, 支持单一颜色

class cGuiLable : public cGuiControl
{
public:
    explicit cGuiLable(cGuiControl* pFather);
    virtual ~cGuiLable();

	void SetText(const char* str);
	const char* GetText();

	void SetTextColor(const DWORD& dwColor);
	DWORD GetTextColor() const;

private:
	
	DWORD _dwTextColor;		//文字颜色
};

#endif