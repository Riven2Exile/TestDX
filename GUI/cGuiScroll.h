#ifndef _L_GUI_SCROLL_H
#define _L_GUI_SCROLL_H

#include "cGuiControl.h"

class cGuiButton;

/*
	滚动条, 先实现纵向的滚动条

	而进度条的跨幅跟内容有关，而这些内容可以是控件,或者其他东东, 抽象起来其实是总高度,或者总宽度


	1. 点击两侧按钮 (按照最基本单位移动)
	2. 拉动中间条
	3. 滚轮
	4. 按住中间的空隙...
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

	// 3. 中间的滑块可以伸缩 (之后再考虑!)

	// 4. 子控件被截断
	
	void SetScrollPos(const UINT& pos);
	void SetRange(const UINT& range); //这个东西是否要废弃?


protected:



	void StartDrag(cGuiButton*, const int& x, const int& y);
	void EndDrag(cGuiButton*, const int& x, const int& y);
	void ScrollPosMove(cGuiButton*, const int& x, const int& y);

	//todo: 鼠标滚轮~

private:
	Scroll_Type _scroll_type;	//滚动类型

	UINT _scroll_range;	//范围
	UINT _pos;		//当前点

	cGuiButton* _pBtnUp;
	cGuiButton* _pBtnDown;
	cGuiButton* _pBtn_Mid_up_Down;
};


#endif