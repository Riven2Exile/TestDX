#include "stdafx.h"
#include "cGuiMgr.h"
#include "cCommonGuiHead.h"

cGuiMgr::cGuiMgr():cGuiForm(nullptr){
}

cGuiMgr::~cGuiMgr(){

}

bool cGuiMgr::Init()
{
//     _pRoot = new cGuiForm;;
// 
// 
//     // todo: ���ÿ��...
//     _pRoot->Show(true);
//     _pRoot->SetWidth(1);
//     _pRoot->SetHeight(1);
//     _pRoot->SetAlpha(0); //͸��
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

    /// ������ֻ������⣬ ʹ������Ĵ���
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


/////// ���
void cGuiMgr::Resort()
{

}


/////// ��Ϣ����
eGuiEventResult cGuiMgr::OnMouseMove(const int& x, const int& y, const eMouseKeyStateMask& nFlag)
{
    return ForEachUIMsg2(&cGuiControl::OnMouseMove, x, y, nFlag);

    //return 1;
}

eGuiEventResult cGuiMgr::OnMouseWheel(const int& x, const int& y, const int& delta, const eMouseKeyStateMask& state){
	return ForEachUIMouseWheel(&cGuiControl::OnMouseWheel, x, y, delta, state);
}

eGuiEventResult cGuiMgr::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    //return ForEachUIMsg2(&cGuiControl::OnLButtonDown, x, y, nFlag);

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


//     if (_pRoot)
//     {
//         return _pRoot->OnLButtonDown(x, y, nFlag);
//     }
    return kGER_None;
}

eGuiEventResult cGuiMgr::OnLButtonUp(const int& x, const int& y, const eMouseKeyStateMask& nFlag)
{
    return ForEachUIMsg2(&cGuiControl::OnLButtonUp, x, y, nFlag);

    //return 1;
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