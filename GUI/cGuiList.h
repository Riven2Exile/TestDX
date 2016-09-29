#ifndef _L_GUI_LIST_H
#define _L_GUI_LIST_H

/*
	列表

	可以自定义格式化 某一列的表现,  而且需要注意控制某一个控件的需求
*/

#include "cGuiControl.h"
#include <vector>

struct stCustomCtrlPack
{
	std::vector<cGuiControl*> listCtrl;
};


class cGuiContainer;



class cGuiList : public cGuiControl
{
public:
	cGuiList(cGuiControl* pFather);
	virtual ~cGuiList();


	void AddAListCtrl(const stCustomCtrlPack& data);	//单独增加一列
	void AddAListCtrl(const UINT& index, const stCustomCtrlPack& data);

	bool DeleteAListCtrl(const UINT& index); //todo:!

protected:

	//自定义控件列表
	std::list<cGuiContainer*> _gui_list_ctrl;
};





#endif