#ifndef _L_GUI_SCROLL_H
#define _L_GUI_SCROLL_H

#include "cGuiControl.h"

class cGuiButton;

/*
	������, ��ʵ������Ĺ�����
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

	// 0. ���ù�������
	void SetScrollType(Scroll_Type eType);

	// 1. ���ÿ�Ⱥ͸߶� ����

	// 2. �������з�Χ���Լ�����һ����

	// 3. �м�Ļ����������

	// 4. �ӿؼ����ض�



	virtual int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
private:
	Scroll_Type _scroll_type;	//��������

	cGuiButton* _pBtnUp;
	cGuiButton* _pBtnDown;
	cGuiButton* _pBtn_Mid_up_Down;
};


#endif