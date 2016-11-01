
#include "cGuiControl.h"
#include "cCommonGuiHead.h"
#include "Text\TextInterface.h"

//#include "..\iSprite.h"


cGuiControl::cGuiControl(cGuiControl* pFather): _id(0), _bShow(true), _bDrag(false)
//,_offsetX(0)
//,_offsetY(0)
,_strText("")
, _bFocus(false)
,_bClicked(false)
,_dragX(0)
,_dragY(0)
, _bMouseOn(false)
{
	_pFather = pFather;
    _sprite = CreateSprite(ST_MX);
    _sprite->LoadAImage("", g_pDevice);
	SetTexture("empty");
	SetOffSet(0, 0);
}

cGuiControl::~cGuiControl()
{

}

////////////////////////
void cGuiControl::SetPos(const int& x, const int& y)
{
    _sprite->SetX(x);
    _sprite->SetY(y);
}

void cGuiControl::GetPos(int& x, int& y)
{
    x = _sprite->GetX();
    y = _sprite->GetY();
}
int cGuiControl::GetScreenPosX(){
	return _sprite->GetX();
}
int cGuiControl::GetScreenPosY(){
	return _sprite->GetY();
}

void cGuiControl::SetOffSet(const int& x, const int& y)
{
	_offsetX = x;
	_offsetY = y;
 
	int fx = 0, fy = 0; //可以得到最终的屏幕坐标
	int tx = 0, ty = 0;

	cGuiControl *pTempFather = _pFather;
	while (pTempFather && pTempFather->_pFather) //最最顶层不算偏移,所以有 && pTempFather->_pFather
	{
		pTempFather->GetOffSet(tx, ty);
		fx += tx;
		fy += ty;
		pTempFather = pTempFather->_pFather;
	}

	_sprite->SetX(fx+x);
	_sprite->SetY(fy+y);


 	for(LIST_CTRL::iterator itr = _listCtrl.begin(); itr != _listCtrl.end(); ++itr ){
		(*itr)->AddAllOffset(x, y);
 	}
}
void cGuiControl::GetOffSet(int& x, int& y)
{
	x = _offsetX;
	y = _offsetY;
}
void cGuiControl::SetOffSetX(const int& x){
	SetOffSet(x, _offsetY);
}
void cGuiControl::SetOffSetY(const int& y){
	SetOffSet(_offsetY, y);
}

void cGuiControl::AddAllOffset(const int& x, const int& y)
{
    _sprite->SetX( int(_sprite->GetX()) + x);
    _sprite->SetY( int(_sprite->GetY()) + y);
    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end();
        ++itr)
    {
        (*itr)->AddAllOffset(x, y);
    }
}

void cGuiControl::SetWidth(float fw)
{
    _sprite->setWidth(fw);
}
void cGuiControl::SetHeight(float fh)
{
    _sprite->setHeight(fh);
}

int cGuiControl::get_width(){
	return _sprite->getWidth();
}

int cGuiControl::get_height(){
	return _sprite->getHeight();
}

ControlType cGuiControl::GetCtrlType()
{
    return _ctrlType;
}

void cGuiControl::SetCtrlType(ControlType type)
{
    _ctrlType = type;
}

void cGuiControl::SetClip(FRECT &rc)
{
    _sprite->setClip(true);
    _sprite->setClipRect(rc);
}

void cGuiControl::SetTexture(const char* szName)
{
    if(szName == NULL)
        return ;

    _sprite->setTexture(CTextureMgr::instance().getTexture(szName));
}

void cGuiControl::SetAlpha(unsigned int al)
{
    _sprite->SetAlpha(al);
}
unsigned int cGuiControl::GetAlpha()
{
    return _sprite->GetAlpha();
}

void cGuiControl::SetID(unsigned int id)
{
    _id = id;
}

void cGuiControl::SetDrag(bool bDrag){
    _bDrag = bDrag;
}
bool cGuiControl::CanDrag(){
    return _bDrag;
}


void cGuiControl::AddControl(cGuiControl* pCtrl)
{
    pCtrl->SetFatherCtrl(this); //记录父控件ID (如果要删除父控件,一定要先删除子控件)
    _listCtrl.push_back(pCtrl);
}

bool cGuiControl::DeleteControl(const int& ctrlid){
	for (auto itr = _listCtrl.begin(); itr != _listCtrl.end(); ++itr){
		if ((*itr)->GetID() == ctrlid)
		{
			_listCtrl.erase(itr);
			return true;
		}
	}
	return false;
}

cGuiControl* cGuiControl::FindControl(int id /* = -1 */)
{
    if (id == _id)
    {
        return this;
    }

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end();
        ++itr)
    {
        if ((*itr)->GetID() == id)
        {
            return (*itr);
        }
        else
        {
            cGuiControl* pCtrl = (*itr)->FindControl(id);
            if (pCtrl)
            {
                return pCtrl;
            }
        }
    }

    return NULL;
}

void cGuiControl::SetFatherCtrl(cGuiControl* pCtrl)
{
    _pFather = pCtrl;
}


void cGuiControl::Update(const DWORD& dwElaspe)
{
    _sprite->Update();

    // 子控件
    if (_listCtrl.size())
    {
        std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
        for ( ; itr != _listCtrl.end(); ++itr)
        {
            (*itr)->Update(dwElaspe);
        }
    }

	run(dwElaspe);
}

void cGuiControl::Draw()
{
    // 
    if(false == _bShow)
        return ;

    _sprite->Draw();

	if (_strText.empty() == false)
	{
		int x = 0, y = 0;
// 		_pFather->GetOffSet(x, y);
// 		TextOutput(x + _sprite->GetX(), y +_sprite->GetY(), _strText.c_str());
		TextOutput(_sprite->GetX(), _sprite->GetY(), _strText.c_str());
	}

    // 子控件
    if (_listCtrl.size())
    {
        std::list<cGuiControl*>::reverse_iterator itr = _listCtrl.rbegin(); //反向画..先画的会被后画的盖住
        for ( ; itr != _listCtrl.rend(); ++itr)
        {
            (*itr)->Draw();
        }
    }
}

void cGuiControl::Show(bool bShow /* = true */)
{
    _bShow = bShow;
}

void cGuiControl::SetFocus(bool b){
	_bFocus = b;
}
bool cGuiControl::IsFocus(){
	return _bFocus;
}
void cGuiControl::ClearChildFocus(cGuiControl* pFocusCtrl){
	auto fun = [&](cGuiControl* p){
		if (p != pFocusCtrl && p->IsFocus())
		{
			p->SetFocus(false);
			if (p->_cb_lose_focus){
				p->_cb_lose_focus(p);
			}
		}
	};
	ForEachCtrlEx(fun);
}

////////// 判断
bool cGuiControl::IsAt(const int& x, const int& y)
{
    if (x >= _sprite->GetX()
        && (_sprite->GetX() + (int)_sprite->getWidth()) >= x
        && _sprite->GetY() <= y 
        && (_sprite->GetY() + (int)_sprite->getHeight()) >= y)
    {
        return true;
    }

    return false;
}

////////// 控件层次
void cGuiControl::MoveToFront(int id, bool bResort /* = false */)
{
    // 查找本层的控件
    for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin() ;
        itr != _listCtrl.end(); 
        ++itr )
    {
        if ( (*itr)->GetID() == id )
        {
            cGuiControl *pCtrl = (*itr);
            _listCtrl.erase(itr);
            _listCtrl.push_front(pCtrl); //放到队列前

            if (bResort)
            {
                Resort();
            }
        }
    }


}

void cGuiControl::Resort()
{
    // todo: 排序
}


////////// 消息
eGuiEventResult cGuiControl::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    
    if(IsShow() == false)
        return kGER_None;


    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
        if( (*itr)->OnMouseMove(x, y, nFlag) == kGER_Processed)
        {
			return kGER_Processed; //  表示后面的UI不用再处理了
        }
    }


	//控件本身
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
	else
	{
		_bClicked = false;
		return kGER_None;
	}

	
}

eGuiEventResult cGuiControl::OnMouseWheel(const int& x, const int& y, const int& delta, const enum eMouseKeyStateMask& state){
	if (IsShow() == false)
		return kGER_None;

	for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
		itr != _listCtrl.end();
		++itr)
	{
		if ((*itr)->OnMouseWheel(x, y, delta, state) == kGER_Processed)
		{
			return kGER_Processed; //表示后面的UI不用再处理了
		}
	}
}

eGuiEventResult cGuiControl::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return kGER_None;

	_bClicked = false;

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
		if ((*itr)->OnLButtonUp(x, y, nFlag) == kGER_Processed)
        {
			return kGER_Processed; //如果返回0, 表示后面的UI不用再处理了
        }
    }

    return kGER_None;
}

eGuiEventResult cGuiControl::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
		return kGER_None;

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
		cGuiControl *pCtrl = (*itr);
		if (pCtrl->IsAt(x, y))
		{
			if (pCtrl->OnLButtonDown(x, y, nFlag) == kGER_Processed) //子控件自定义的
			{
				if (IsFocus() == false)
				{
					if (pCtrl->GetFather()){
						pCtrl->GetFather()->ClearChildFocus(pCtrl); //清除掉兄弟的焦点
					}

					pCtrl->SetFocus(true); //获得焦点
					if (pCtrl->_cb_gain_focus){
						pCtrl->_cb_gain_focus(this);
					}
				}

				return kGER_Processed; //如果返回0, 表示后面的UI不用再处理了
			}
		}
    }


	//控件自身
	if (IsAt(x, y))
	{
		_bClicked = true;
		int xx = 0, yy = 0;
		GetPos(xx, yy);
		_dragX = x - xx;
		_dragY = y - yy;

		return kGER_Processed; //消息被捕获，不再往下传递
	}

	return kGER_None;
}

eGuiEventResult cGuiControl::OnChar(const unsigned int& wparam, const unsigned long& lparam){
	if (IsShow() == false){
		return kGER_None;
	}

	for (auto& p : _listCtrl) {
		if (p->OnChar(wparam, lparam) == kGER_Processed){
			return kGER_Processed;
		}
	}

	return kGER_None;
}

eGuiEventResult cGuiControl::OnKeyDown(const unsigned int& wparam, const unsigned long& lparam){
	if (IsShow() == false){
		return kGER_None;
	}

	for (auto& p : _listCtrl) {
		if (p->OnKeyDown(wparam, lparam) == kGER_Processed){
			return kGER_Processed;
		}
	}

	return kGER_None;
}

///// event
void cGuiControl::SetGainFocusCallBack(focus_cb_fun fun){
	_cb_gain_focus = fun;
}

void cGuiControl::SetLoseFocusCallBack(focus_cb_fun fun){
	_cb_lose_focus = fun;
}