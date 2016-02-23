
#include "cGuiControl.h"
#include "cCommonGuiHead.h"

//#include "..\iSprite.h"


cGuiControl::cGuiControl(cGuiControl* pFather): _id(0), _bShow(true), _bDrag(false)
,_offsetX(0)
,_offsetY(0)
{
	_pFather = pFather;
    _sprite = CreateSprite(ST_MX);
    _sprite->LoadAImage("", g_pDevice);
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

void cGuiControl::SetOffSet(const int& x, const int& y)
{
	_offsetX = x;
	_offsetY = y;

	int fx = 0, fy = 0;
	if (_pFather)
	{
		_pFather->GetOffSet(fx, fy);
	}

	_sprite->SetX(fx+x);
	_sprite->SetY(fx+y);

// 	for(LIST_CTRL::iterator itr = _listCtrl.begin(); itr != _listCtrl.end(); ++itr ){
// 		itr->SetOffSet();
// 	}
}
void cGuiControl::GetOffSet(int& x, int& y)
{
	x = _offsetX;
	y = _offsetY;
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


void cGuiControl::Update()
{
    _sprite->Update();

    // 子控件
    if (_listCtrl.size())
    {
        std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
        for ( ; itr != _listCtrl.end(); ++itr)
        {
            (*itr)->Update();
        }
    }
}

void cGuiControl::Draw()
{
    // 
    if(false == _bShow)
        return ;

    _sprite->Draw();

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
int cGuiControl::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    
    if(IsShow() == false)
        return 1;

//     if ( CanDrag() && nFlag & LMK_LBUTTON) //处理拖动
//     {
//         int xx = 0, yy = 0;
//         GetPos(xx, yy);
//         AddAllOffset(x - xx, y - yy);
//     }

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
        if( (*itr)->OnMouseMove(x, y, nFlag) == 0)
        {
            return 0; //如果返回0, 表示后面的UI不用再处理了
        }
    }

    return 1;
}

int cGuiControl::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return 1;

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
        if( (*itr)->OnLButtonUp(x, y, nFlag) == 0)
        {
            return 0; //如果返回0, 表示后面的UI不用再处理了
        }
    }

    return 1;
}

int cGuiControl::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return 1;

    for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin(); 
        itr != _listCtrl.end(); 
        ++itr)
    {
        if( (*itr)->OnLButtonDown(x, y, nFlag) == 0)
        {
            return 0; //如果返回0, 表示后面的UI不用再处理了
        }
    }
    return 1;
}