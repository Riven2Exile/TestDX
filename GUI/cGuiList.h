#ifndef _L_GUI_LIST_H
#define _L_GUI_LIST_H

/*
	�б�

	�����Զ����ʽ�� ĳһ�еı���,  ������Ҫע�����ĳһ���ؼ�������
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


	void AddAListCtrl(const stCustomCtrlPack& data);	//��������һ��
	void AddAListCtrl(const UINT& index, const stCustomCtrlPack& data);

	bool DeleteAListCtrl(const UINT& index); //todo:!

protected:

	//�Զ���ؼ��б�
	std::list<cGuiContainer*> _gui_list_ctrl;
};





#endif