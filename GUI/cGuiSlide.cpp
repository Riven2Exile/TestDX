#include "cGuiSlide.h"
#include "cGuiProgress.h"
#include "cGuiButton.h"

cGuiSlide::cGuiSlide(cGuiControl* pfather) : cGuiControl(pfather)
, _pSlidePro(nullptr)
, _pSlideBtn(nullptr)
, _isDragging(false)
, _x_screen_start_drag(0)
, _y_screen_start_drag(0)
{
	this->SetCtrlType(kCT_GuiSlide);
	_pSlideBtn = new cGuiButton(this);
	_pSlideBtn->SetBtnStateImage(cGuiButton::kBS_Normal, "slide_btn");
	_pSlideBtn->SetBtnStateImage(cGuiButton::kBS_MouseOn, "slide_btn");
	_pSlideBtn->SetBtnStateImage(cGuiButton::kBS_Clicked, "slide_btn");
	_pSlideBtn->SetBtnStateImage(cGuiButton::kBS_Disable, "slide_btn");
	_pSlideBtn->SetWidth(11);
	_pSlideBtn->SetHeight(17);
	_pSlideBtn->SetOffSet(20, -1);
	_pSlideBtn->SetPressDownFun(std::bind(&cGuiSlide::StartDrag, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pSlideBtn->SetPressUpFun(std::bind(&cGuiSlide::EndDrag, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pSlideBtn->SetPressedMouseMoveFun(std::bind(&cGuiSlide::SlidePosMove, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	AddControl(_pSlideBtn);

	_pSlidePro = new cGuiProgress(this);
	//m_pPro->SetBackImage("slide_background");
	_pSlidePro->SetBarImage("slide_bar");
	_pSlidePro->SetWidth(93);
	_pSlidePro->SetHeight(7);
	_x_bar_offset = 5;
	_y_bar_offset = 3;
	_pSlidePro->SetOffSet(_x_bar_offset, _y_bar_offset);
	AddControl(_pSlidePro);

	this->SetTexture("slide_background");
	SetWidth(103);
	SetHeight(13);


	_nPos = 0;
	_nRange = 100;
	// 驱动一下滑块的位置
	SetSlidePos(25);

	//SetOffSet(0, 0);// 【CGuiContrl的构造函数中,不是执行cGuiSlide::SetOffSet】
}


cGuiSlide::~cGuiSlide()
{

}


////////////////
void cGuiSlide::StartDrag(cGuiButton* pBtn, const int& x, const int& y){
	printf("guiSlide start drag!\n");
	//调用自定义函数
	_isDragging = true;
	_x_screen_start_drag = x;
	_y_screen_start_drag = y;
}

void cGuiSlide::EndDrag(cGuiButton* pBtn, const int& x, const int& y){
	printf("guiSlied end drag!\n");
	//调用自定义函数
	_isDragging = false;
}

void cGuiSlide::SlidePosMove(cGuiButton* pBtn, const int& x, const int& y){
	//可能触发 SetSlide
	if (_nRange && _pSlidePro->get_width() && x - _pSlidePro->GetScreenPosX() >= 0){
		//if (_pSlidePro->IsAt(x, y))
		{
			float factor = (x - _pSlidePro->GetScreenPosX()) / (float)_pSlidePro->get_width();
			SetSlidePos(factor * _nRange);
		}
	}
}


void cGuiSlide::SetSlidePos(const UINT& pos){
	// judge and change view
	if (pos <= _nRange)
	{
		this->_nPos = pos;
		//todo: change slide button
		if (_nRange && this->_pSlideBtn->get_width()){
			float factor = pos / (float)_nRange;
			int btn_x_start = _pSlidePro->GetOffSetX() - _pSlideBtn->get_width() / 2.0f;  //偏移左边
			
			int xx = 0, yy = 0;
			_pSlideBtn->SetOffSetX( btn_x_start + int(factor * _pSlidePro->get_width()) );

			// 进度条变动
			_pSlidePro->SetProgress(_nPos / (float)_nRange * 100);
		}
		//m_pPro->get_width();
	}
}

void cGuiSlide::SetSlideRange(const UINT& range){
	if (_nPos > range)
	{
		this->_nPos = range;
		this->_nRange = range;
		// todo: change view ?
		SetSlidePos(_nPos);
	}
	else{
		_nRange = range;
		// todo: change view ?
	}
}

UINT cGuiSlide::GetSlidePos(){
	return _nPos;
}
UINT cGuiSlide::GetSlideRange(){
	return _nRange;
}