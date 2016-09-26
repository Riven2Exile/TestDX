#include "cGuiList.h"


cGuiList::cGuiList(cGuiControl* pFather) : cGuiControl(pFather)
{
	SetCtrlType(kCT_GuiList);
}

cGuiList::~cGuiList(){

}



////
void cGuiList::AddAListCtrl(const stCustomCtrlPack& data)
{
	_gui_list_ctrl.push_back(data);
	for (auto var : data.listCtrl){
		AddControl(var);
	}
}

void cGuiList::AddAListCtrl(const UINT& index, const stCustomCtrlPack& data)
{
	printf("todo: cGuiList::AddAListCtrl\n");
}

bool cGuiList::DeleteAListCtrl(const UINT& index)
{
	printf("todo: cGuiList::DeleteAListCtrl\n");
	return false;
}
