#include "stdafx.h"
#include "cGuiMgr.h"
#include "cCommonGuiHead.h"

cGuiMgr::cGuiMgr(){
}

cGuiMgr::~cGuiMgr(){

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

void cGuiMgr::Update()
{
    ForEachUI(&cGuiControl::Update);
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
int cGuiMgr::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    return ForEachUIMsg2(&cGuiControl::OnMouseMove, x, y, nFlag);

//     for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
//         itr != _listCtrl.end();
//         ++itr)
//     {
//         (*itr)->OnMouseMove(x, y, nFlag);
//     }

//     if (_pRoot)
//     {
//         return _pRoot->OnMouseMove(x, y, nFlag);
//     }

    return 1;
}

int cGuiMgr::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    //return ForEachUIMsg2(&cGuiControl::OnLButtonDown, x, y, nFlag);

    for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
        itr != _listCtrl.end();
        ++itr)
    {
        if( (*itr)->OnLButtonDown(x, y, nFlag) == 0)
        {
            cGuiControl *pCtrl = (*itr);
            itr = _listCtrl.erase(itr);

            _listCtrl.push_front(pCtrl);
            return 0;
        }
    }


//     if (_pRoot)
//     {
//         return _pRoot->OnLButtonDown(x, y, nFlag);
//     }
    return 1;
}

int cGuiMgr::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    return ForEachUIMsg2(&cGuiControl::OnLButtonUp, x, y, nFlag);

//     for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
//         itr != _listCtrl.end();
//         ++itr)
//     {
//         (*itr)->OnLButtonUp(x, y, nFlag);
//     }


//     if (_pRoot)
//     {
//         return _pRoot->OnLButtonUp(x, y, nFlag);
//     }
    return 1;
}