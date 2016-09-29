#include "cGuiList.h"
#include "cGuiContainer.h"


cGuiList::cGuiList(cGuiControl* pFather) : cGuiControl(pFather)
{
	SetCtrlType(kCT_GuiList);
}

cGuiList::~cGuiList(){

}



////
void cGuiList::AddAListCtrl(const stCustomCtrlPack& data)
{
	cGuiContainer* pCon = new cGuiContainer(this);
	int height = 0;
	int weight = 0;
	int yy = 0;
	for (auto var : data.listCtrl){
		pCon->AddControl(var);
		if (var->GetOffSetY() + var->get_height() > height){
			height = var->GetOffSetY() + var->get_height();
		}
		if (var->GetOffSetX() + var->get_width()> weight) {
			weight = var->GetOffSetX() + var->get_width();
		}
	}

	if (_gui_list_ctrl.size() > 0) {
		cGuiControl *pCtrl = _gui_list_ctrl.back();
		if (pCtrl) {
			yy += (pCtrl->GetOffSetY() + pCtrl->get_height());
		}
	}

	pCon->SetWidth(weight);
	pCon->SetHeight(height);
	pCon->SetOffSet(0, yy);

	_gui_list_ctrl.push_back(pCon);
	AddControl(pCon);

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
