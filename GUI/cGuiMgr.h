
#ifndef _L_GUI_MGR_H
#define _L_GUI_MGR_H

#include "cGuiForm.h"

class cGuiControl;
class cGuiForm;

class cGuiMgr : public cGuiForm
{
    
public:
	explicit cGuiMgr(cGuiControl* pFather);
    virtual ~cGuiMgr();

    bool Init();

	void Update(const DWORD& dwElaspe);
    void Draw();

    // 层次
    void Resort();

    // 数据
    void AddCtrl(cGuiControl *pCtrl); //加一个对话框.. 后面再考虑id
    void RemoveCtrl(unsigned int id);

	void SetWindowHandle(HWND h){
		_hwnd = h;
	}
	virtual void SetPos(const int& x, const int& y);
	void SetSize(const int& w, const int& h);

	HWND GetWindowHandle() { return _hwnd; }

    // 消息处理
	eGuiEventResult OnMouseMove(const int& x, const int& y, const eMouseKeyStateMask& nFlag);
	eGuiEventResult OnMouseWheel(const int& x, const int& y, const int& delta, const eMouseKeyStateMask& state);
	eGuiEventResult OnLButtonUp(const int& x, const int& y, const eMouseKeyStateMask& nFlag);
    eGuiEventResult OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);
	eGuiEventResult OnChar(const unsigned int& wparam, const unsigned long& lparam);

private:
    template<typename T>
    void ForEachUI(T fn){
        for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
            itr != _listCtrl.end();
            ++itr)
        {
            ((*itr)->*fn)();
        }
    }

	template<typename T, typename P>
	void ForEachUIParam(T fn, const P& param){
		for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
			itr != _listCtrl.end();
			++itr)
		{
			((*itr)->*fn)(param);
		}
	}

    template<typename T>
	eGuiEventResult ForEachUIMsg2(T fn, const int& x, const int& y, const eMouseKeyStateMask& nFlag){
        for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
            itr != _listCtrl.end();
            ++itr)
        {
			if (((*itr)->*fn)(x, y, nFlag) == kGER_Processed)
				return kGER_Processed;
        }

        return kGER_None;
    }

	template<typename T>
	eGuiEventResult ForEachUIMouseWheel(T fn, const int& x, const int& y, const int& delta, const eMouseKeyStateMask& nFlag){
		for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
			itr != _listCtrl.end();
			++itr)
		{
			if (((*itr)->*fn)(x, y, delta, nFlag) == kGER_Processed)
				return kGER_Processed;
		}

		return kGER_None;
	}

    //cGuiForm* _pRoot;
    //std::list<cGuiControl*> _listCtrl;
	HWND _hwnd;
};


#endif