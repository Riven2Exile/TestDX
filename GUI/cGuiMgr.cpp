#include "stdafx.h"
#include "cGuiMgr.h"
#include "cCommonGuiHead.h"

cGuiMgr::cGuiMgr(cGuiControl* pFather) :cGuiForm(pFather){
	SetDrag(true);
	SetID(10086);
}

cGuiMgr::~cGuiMgr(){

}

void cGuiMgr::SetPos(const int& x, const int& y)
{
	__super::SetPos(x, y);

	::SetWindowPos(_hwnd, NULL, x, y, get_width(), get_height(), SWP_SHOWWINDOW);
}

void cGuiMgr::SetSize(const int& w, const int& h){
	__super::SetWidth(w);
	__super::SetHeight(h);

	::SetWindowPos(_hwnd, NULL, GetScreenPosX(), GetScreenPosY(), get_width(), get_height(), SWP_SHOWWINDOW);
}

bool cGuiMgr::Init()
{
//     _pRoot = new cGuiForm;;
// 
// 
//     // todo: 设置宽高...
//     _pRoot->Show(true);
//     _pRoot->SetWidth(1);
//     _pRoot->SetHeight(1);
//     _pRoot->SetAlpha(0); //透明
    return true;
}

void cGuiMgr::Update(const DWORD& dwElaspe)
{
	ForEachUIParam(&cGuiControl::Update, dwElaspe);
//     if (_pRoot)
//     {
//         _pRoot->Update();
//     }
}
void cGuiMgr::Draw()
{
    //ForEachUI(&cGuiControl::Draw);

    /// 如果出现绘制问题， 使用下面的代码
    for ( std::list<cGuiControl*>::reverse_iterator itr = _listCtrl.rbegin();
        itr != _listCtrl.rend();
        ++itr)
    {
        (*itr)->Draw();
    }
//     if (_pRoot)
//     {
//         _pRoot->Draw();
//     }
}


void cGuiMgr::AddCtrl(cGuiControl *pCtrl)
{
    if(NULL == pCtrl)
        return ;
    
    _listCtrl.push_back(pCtrl);
    //_pRoot->AddControl(pCtrl);
}

void cGuiMgr::RemoveCtrl(unsigned int id)
{
    // todo:..
}


/////// 层次
void cGuiMgr::Resort()
{

}


/////// 消息处理
eGuiEventResult cGuiMgr::OnMouseMove(const int& x, const int& y, const eMouseKeyStateMask& nFlag)
{
    eGuiEventResult rt = ForEachUIMsg2(&cGuiControl::OnMouseMove, x, y, nFlag);

    if (kGER_None == rt)
    {
		//控件本身
		static POINT pos_screen;
		::GetCursorPos(&pos_screen);
		//printf("screen %d,%d\n", pos_screen.x, pos_screen.y);
		if (CanDrag() && _bClicked && nFlag & LMK_LBUTTON)
		{
			// 处理拖动
			int xx = 0, yy = 0;
			GetPos(xx, yy);
			// 其实这里应该要算上对话框的offset移动
			_offsetX += (pos_screen.x - _dragX - xx);
			_offsetY += (pos_screen.y - _dragY - yy);
			//AddAllOffset(x - _dragX - xx, y - _dragY - yy);
			SetPos(_offsetX, _offsetY);
			return kGER_Processed;
		}
		else
		{
			_bClicked = false;
			return kGER_None;
		}
    }

	return rt;
}

eGuiEventResult cGuiMgr::OnMouseWheel(const int& x, const int& y, const int& delta, const eMouseKeyStateMask& state){
	return ForEachUIMouseWheel(&cGuiControl::OnMouseWheel, x, y, delta, state);
}

eGuiEventResult cGuiMgr::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
        itr != _listCtrl.end();
        ++itr)
    {
        if( (*itr)->OnLButtonDown(x, y, nFlag) == kGER_Processed)
        {
            cGuiControl *pCtrl = (*itr);
            itr = _listCtrl.erase(itr);

            _listCtrl.push_front(pCtrl);
			return kGER_Processed;
        }
    }


	//控件自身(转化成屏幕坐标)
	static POINT pos_screen;
	::GetCursorPos(&pos_screen);
	if (IsAt(pos_screen.x, pos_screen.y))
	{
		_bClicked = true;
		int xx = 0, yy = 0;
		GetPos(xx, yy);
		_dragX = pos_screen.x - xx;
		_dragY = pos_screen.y - yy;

		return kGER_Processed; //消息被捕获，不再往下传递
	}

    //return kGER_None;
}

eGuiEventResult cGuiMgr::OnLButtonUp(const int& x, const int& y, const eMouseKeyStateMask& nFlag)
{
    eGuiEventResult rt = ForEachUIMsg2(&cGuiControl::OnLButtonUp, x, y, nFlag);

	if (rt == kGER_None)
	{
		rt = __super::OnLButtonUp(x, y, nFlag);
	}

	return rt;
}

eGuiEventResult cGuiMgr::OnChar(const unsigned int& wparam, const unsigned long& lparam){
	for ( auto& p : _listCtrl)
	{
		if (p->OnChar(wparam, lparam) == kGER_Processed)
		{
			return kGER_Processed;
		}
	}
	return kGER_None;
}