#ifndef _L_GUI_SCROLL_H
#define _L_GUI_SCROLL_H

#include "cGuiControl.h"

class cGuiButton;

/*
	������, ��ʵ������Ĺ�����

	���������Ŀ���������йأ�����Щ���ݿ����ǿؼ�,������������, ����������ʵ���ܸ߶�,�����ܿ��


	1. ������ఴť (�����������λ�ƶ�)
	2. �����м���
	3. ����
	4. ��ס�м�Ŀ�϶...
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

	// 3. �м�Ļ���������� (֮���ٿ���!)

	// 4. �ӿؼ����ض�
	
	void SetScrollPos(const UINT& pos);
	void SetRange(const UINT& range); //��������Ƿ�Ҫ����?


protected:



	void StartDrag(cGuiButton*, const int& x, const int& y);
	void EndDrag(cGuiButton*, const int& x, const int& y);
	void ScrollPosMove(cGuiButton*, const int& x, const int& y);

	//todo: ������~

private:
	Scroll_Type _scroll_type;	//��������

	UINT _scroll_range;	//��Χ
	UINT _pos;		//��ǰ��

	cGuiButton* _pBtnUp;
	cGuiButton* _pBtnDown;
	cGuiButton* _pBtn_Mid_up_Down;
};


#endif