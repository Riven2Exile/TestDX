#include "cGuiForm.h"
#include "cCommonGuiHead.h"

cGuiForm::cGuiForm(cGuiControl* pFather):cGuiControl(pFather),_bClicked(false),
                    _dragX(0),
                    _dragY(0)
                    
{
    SetCtrlType(kCT_GuiForm); //需要指定类型

    //如果是对话框的话，默认可以拖动
    SetDrag(true);

    
}

cGuiForm::cGuiForm():cGuiControl(NULL),_bClicked(false),
_dragX(0),
_dragY(0)
{
	SetCtrlType(kCT_GuiForm); //需要指定类型

	//如果是对话框的话，默认可以拖动
	SetDrag(true);
}

cGuiForm::~cGuiForm()
{

}

//////////
void cGuiForm::SetName(const char* pszName /* = */ )
{
    _strName = pszName;
}

//////////
void cGuiForm::Show(bool bShow /*= true*/)
{
    cGuiControl::Show(bShow);
}

void cGuiForm::SetOffSet(const int& x, const int& y){
	_offsetX = x;
	_offsetY = y;

	int fx = 0, fy = 0; //可以得到最终的屏幕坐标
	int tx = 0, ty = 0;
	cGuiControl *pTempFather = _pFather;
	while (pTempFather)
	{
		pTempFather->GetOffSet(tx, ty);
		fx += tx;
		fy += ty;
		pTempFather = pTempFather->GetFather();
	}

	_sprite->SetX(fx + x);
	_sprite->SetY(fy + y);
}

//////////
int cGuiForm::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    //先给子控件继续传消息
    if(cGuiControl::OnMouseMove(x, y, nFlag) == 0)
        return 0;

    if (CanDrag() && _bClicked && nFlag & LMK_LBUTTON )
    {
        // 处理拖动
        int xx = 0, yy = 0;
        GetPos(xx, yy);
		// 其实这里应该要算上对话框的offset移动
		_offsetX += (x - _dragX - xx);
		_offsetY += (y - _dragY - yy);
		//SetOffSet(_offsetX + (x - _dragX - xx), _offsetY + (y - _dragY - yy));
        AddAllOffset(x - _dragX - xx, y - _dragY - yy);
    }
    else
    {
        _bClicked = false;
    }
    return 1;
}

int cGuiForm::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    if(IsShow() == false)
        return 1;

    //先给子控件继续传消息
    if (cGuiControl::OnLButtonDown(x, y, nFlag) == 0)
        return 0;

    if (IsAt(x, y))
    {
        _bClicked = true;
        int xx = 0, yy = 0;
        GetPos(xx, yy);
        _dragX = x - xx;
        _dragY = y - yy;

        return 0; //消息被捕获，不再往下传递
    }
   
    return 1;
}

int cGuiForm::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    cGuiControl::OnLButtonUp(x, y, nFlag);  //先给子控件继续传消息


    return 1;
}