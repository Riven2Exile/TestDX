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
	UINT _nPos;		//滑块所在的点
	UINT _nRange;	//范围
	bool _isDragging;	//是否拖动中
	int _x_screen_start_drag;
	int _y_screen_start_drag;

	int _x_bar_offset;	//为了计算滑块的移动范围,所以需要知道进度条的偏移
	int _y_bar_offset;

	cGuiProgress *_pSlidePro;
	cGuiButton* _pSlideBtn;
};



#endif