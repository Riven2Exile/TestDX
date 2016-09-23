#ifndef _L_GUI_SLIDE_H
#define _L_GUI_SLIDE_H

#include "cGuiControl.h"

class cGuiProgress;
class cGuiButton;


class cGuiSlide : public cGuiControl
{
public:
	explicit cGuiSlide(cGuiControl* pfather);
	virtual ~cGuiSlide();

	void SetSlidePos(const UINT& pos);
	void SetSlideRange(const UINT& range);
	UINT GetSlidePos();
	UINT GetSlideRange();

protected:
	void StartDrag(cGuiButton* , const int& x, const int& y);
	void EndDrag(cGuiButton*, const int& x, const int& y);
	void SlidePosMove(cGuiButton*, const int& x, const int& y);
	// Change _ param -> pos

private:
	UINT _nPos;		//�������ڵĵ�
	UINT _nRange;	//��Χ
	bool _isDragging;	//�Ƿ��϶���
	int _x_screen_start_drag;
	int _y_screen_start_drag;

	int _x_bar_offset;	//Ϊ�˼��㻬����ƶ���Χ,������Ҫ֪����������ƫ��
	int _y_bar_offset;

	cGuiProgress *_pSlidePro;
	cGuiButton* _pSlideBtn;
};



#endif