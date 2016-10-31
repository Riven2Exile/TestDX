#include "cGuiButton.h"

#include "cCommonGuiHead.h"

cGuiButton::cGuiButton(cGuiControl* pFather):cGuiControl(pFather)
{
    SetCtrlType(kCT_GuiButton);

    _btnState = kBS_Normal;
    _pFun = NULL;
}

cGuiButton::~cGuiButton()
{

}
///////////////
void cGuiButton::SetBtnStateImage(eBtnState state, const char* szName)
{
    if(state < kBS_Normal || state >= kBS_Num)
        return ;

    _strImage[state] = szName;

	if (GetBtnState() == state)
	{
		SetTexture(szName);
	}
}
void cGuiButton::SetBtnState(eBtnState e)
{
    _btnState = e;
}

cGuiButton::eBtnState cGuiButton::GetBtnState()
{
    return _btnState;
}

/////////////
eGuiEventResult cGuiButton::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return kGER_None;

    if (GetBtnState() == kBS_Disable)
    {
		return kGER_None;
    }

    // TODO .. 最好以触发的形式来
    if (IsAt(x, y))
    {
        if (GetBtnState() == kBS_Clicked && nFlag & LMK_LBUTTON)
        {
            // 保持
			if (_pFunPressedMouseMove){
				_pFunPressedMouseMove(this, x, y);
			}
        }
        else
        {
            HandleMouseOn();
        }

		
    }
    else
    {
        if (GetBtnState() == kBS_Clicked && nFlag & LMK_LBUTTON)
        {
            // 保持
			if (_pFunPressedMouseMove){
				_pFunPressedMouseMove(this, x, y);
			}
        }
        else
        {
            HandleMouseLeave();
        }
    }

	if (CanDrag() && _bClicked && nFlag & LMK_LBUTTON)
	{
		// 处理拖动
		int xx = 0, yy = 0;
		GetPos(xx, yy);
		// 其实这里应该要算上对话框的offset移动
		_offsetX += (x - _dragX - xx);
		_offsetY += (y - _dragY - yy);
		//SetOffSet(_offsetX + (x - _dragX - xx), _offsetY + (y - _dragY - yy));
		AddAllOffset(x - _dragX - xx, y - _dragY - yy);
		return kGER_Processed;
	}
}

eGuiEventResult cGuiButton::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
		return kGER_None;

    if (IsAt(x, y))
    {
        if (GetBtnState() == kBS_Disable)
        {
			return kGER_None;
        }
        else
        {
			_bClicked = true;
            SetBtnState(kBS_Clicked);
            SetTexture(_strImage[kBS_Clicked].c_str());
			//控件自身

			{
				int xx = 0, yy = 0;
				GetPos(xx, yy);
				_dragX = x - xx;
				_dragY = y - yy;
			}
			if (_pFunPressDown){
				_pFunPressDown(this, x, y);
			}
			return kGER_Processed;
        }
    }

	return kGER_None;
}

eGuiEventResult cGuiButton::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return kGER_None;

    bool bAt = IsAt(x, y);

    if(GetBtnState() == kBS_Disable && bAt)
        return kGER_None;   //消息终止

    if (GetBtnState() == kBS_Clicked && bAt )
    {
        // 命中按钮.. todo: 自定义函数? 
        OnBtnClicked();

		if (_pFunPressUp){
			_pFunPressUp(this, x, y);
		}
    }
    
	_bClicked = false;
    SetBtnState(kBS_Normal);
    SetTexture(_strImage[kBS_Normal].c_str());
    
    
    return kGER_Processed;
}

/////// 消息的业务响应
void cGuiButton::SetClickFun(CtrlClickFun pF)
{
    _pFun = pF;
}

void cGuiButton::SetPressDownFun(Fun_BtnMouse func){
	_pFunPressDown = func;
}
void cGuiButton::SetPressUpFun(Fun_BtnMouse func){
	_pFunPressUp = func;
}
void cGuiButton::SetPressedMouseMoveFun(Fun_BtnMouse func){
	_pFunPressedMouseMove = func;
}

int cGuiButton::OnBtnClicked()
{
    printf("cGuiButton::OnBtnClicked\n");
    if (_pFun)
    {
        (this->*_pFun)(GetID());
    }
    return 1;
}



void cGuiButton::HandleMouseOn()
{
    this->SetTexture(_strImage[kBS_MouseOn].c_str());
}
void cGuiButton::HandleMouseLeave()
{
    this->SetTexture(_strImage[kBS_Normal].c_str());
}