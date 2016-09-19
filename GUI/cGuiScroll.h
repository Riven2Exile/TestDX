#ifndef _L_GUI_SCROLL_H
#define _L_GUI_SCROLL_H

#include "cGuiControl.h"

class cGuiButton;

/*
	滚动条, 先实现纵向的滚动条
*/

class cGuiScroll : public cGuiControl
{
public:
	explicit cGuiScroll(cGuiControl *pFather);
	virtual ~cGuiScroll();

	enum Scroll_Type{
		kST_Up_Down = 1,
		kST_Left_Right = 2,
		kST_All = 3,  // up down left right
	};

	// 0. 设置滚动类型
	void SetScrollType(Scroll_Type eType);

	// 1. 设置宽度和高度 父类

	// 2. 滚动条有范围，以及滚动一段量

	// 3. 中间的滑块可以伸缩

	// 4. 子控件被截断



	virtual int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
private:
	Scroll_Type _scroll_type;	//滚动类型

	cGuiButton* _pBtnUp;
	cGuiButton* _pBtnDown;
	cGuiButton* _pBtn_Mid_up_Down;
};


#endif