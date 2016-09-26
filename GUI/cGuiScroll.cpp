#include "cGuiScroll.h"
#include "cGuiButton.h"

cGuiScroll::cGuiScroll(cGuiControl *pFather) : cGuiControl(pFather)
, _pBtnUp(nullptr)
, _pBtnDown(nullptr)
, _pBtn_Mid_up_Down(nullptr)
, _pos(0)
, _scroll_range(0)
{
	SetCtrlType(kCT_GuiScroll);
	SetScrollType(kST_Up_Down);
}

cGuiScroll::~cGuiScroll(){

}
////

void cGuiScroll::SetScrollType(Scroll_Type eType){
	_scroll_type = eType;
	if (eType == kST_Up_Down)
	{
		if (!_pBtnUp){
			_pBtnUp = new cGuiButton(_pFather);
			_pBtnUp->SetBtnStateImage(cGuiButton::kBS_Normal, "scroll_btn_up1");
			_pBtnUp->SetBtnStateImage(cGuiButton::kBS_MouseOn, "scroll_btn_up2");
			_pBtnUp->SetBtnStateImage(cGuiButton::kBS_Clicked, "scroll_btn_up3");
			_pBtnUp->SetBtnStateImage(cGuiButton::kBS_Disable, "scroll_btn_up4");
			_pBtnUp->SetWidth(15);
			_pBtnUp->SetHeight(15);
			AddControl(_pBtnUp); //先这么加, 如果层次有固定, 再放到Scroll本层
		}

		if (!_pBtn_Mid_up_Down){
			_pBtn_Mid_up_Down = new cGuiButton(_pFather);
			_pBtn_Mid_up_Down->SetBtnStateImage(cGuiButton::kBS_Normal, "scroll_btn_mid1");
			_pBtn_Mid_up_Down->SetBtnStateImage(cGuiButton::kBS_MouseOn, "scroll_btn_mid2");
			_pBtn_Mid_up_Down->SetBtnStateImage(cGuiButton::kBS_Clicked, "scroll_btn_mid3");
			_pBtn_Mid_up_Down->SetBtnStateImage(cGuiButton::kBS_Disable, "scroll_btn_mid4");
			_pBtn_Mid_up_Down->SetWidth(15);
			_pBtn_Mid_up_Down->SetHeight(32);
			int x = 0, y = 0;
			_pBtnUp->GetOffSet(x, y);
			_pBtn_Mid_up_Down->SetOffSet(x, y + _pBtnUp->get_height());

			_pBtn_Mid_up_Down->SetPressDownFun(std::bind(&cGuiScroll::StartDrag, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			_pBtn_Mid_up_Down->SetPressUpFun(std::bind(&cGuiScroll::EndDrag, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			_pBtn_Mid_up_Down->SetPressedMouseMoveFun(std::bind(&cGuiScroll::ScrollPosMove, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

			AddControl(_pBtn_Mid_up_Down);
		}
		
		if (!_pBtnDown){
			_pBtnDown = new cGuiButton(_pFather);
			_pBtnDown->SetBtnStateImage(cGuiButton::kBS_Normal, "scroll_btn_down1");
			_pBtnDown->SetBtnStateImage(cGuiButton::kBS_MouseOn, "scroll_btn_down2");
			_pBtnDown->SetBtnStateImage(cGuiButton::kBS_Clicked, "scroll_btn_down3");
			_pBtnDown->SetBtnStateImage(cGuiButton::kBS_Disable, "scroll_btn_down4");
			_pBtnDown->SetWidth(15);
			_pBtnDown->SetHeight(15);

			int x = 0, y = 0;
			_pBtn_Mid_up_Down->GetOffSet(x, y);
			_pBtnDown->SetOffSet(x, y + _pBtn_Mid_up_Down->get_height() + 50);
			AddControl(_pBtnDown);
		}
	}
	else if (eType == kST_Left_Right)
	{
	}
	else if (eType == kST_All)
	{
	}
}












void cGuiScroll::SetScrollPos(const UINT& pos){

}
void cGuiScroll::SetRange(const UINT& range){
	_scroll_range = range;
}






///////// 消息


void cGuiScroll::StartDrag(cGuiButton*, const int& x, const int& y)
{
	printf("GuiScroll start drag! \n");
}

void cGuiScroll::EndDrag(cGuiButton*, const int& x, const int& y)
{
	printf("GuiScroll end drag! \n");
}

void cGuiScroll::ScrollPosMove(cGuiButton*, const int& x, const int& y)
{
	//滑块移动
}
