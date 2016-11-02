#include "stdafx.h"
#include "TestLogicDlg.h"

/*
��ͬ�ؼ�����Ӧ��ʽ��һ��, ��Ӧ�Ļ�������Ӧ����Ҫ�ڲ�ͬ������ȥ��
*/



CTestLogicDlg::CTestLogicDlg(cGuiControl* pFather) : cGuiForm(pFather){

}

CTestLogicDlg::~CTestLogicDlg()
{

}
////////////////////

void CTestLogicDlg::Init()
{
    ////
    _btn = (cGuiButton *)FindControl(110);
    //_btnAdd = (cGuiButton *)FindControl(111);
	_edit_ctrl = (cGuiEdit*)FindControl(108);

    //// �ؼ�ע�ắ��... ����Ϊ��Ա���� m_btn->SetClickFun(CTestLogicDlg::funName);
    if(_btn)_btn->SetClickFun(std::bind( &CTestLogicDlg::OnButtonClick, this, std::placeholders::_1));
    //if(_btnAdd) _btnAdd->SetClickFun(std::bind( &CTestLogicDlg::OnButtonClick, this,std::placeholders::_1));

	if (_edit_ctrl)
	{
		_edit_ctrl->SetEnterReturnCallback(std::bind(&CTestLogicDlg::OnEditComplate, this, std::placeholders::_1)); //ע��༭��������
	}
	
}

// ���Զ����ť��ͬһ����Ӧ����
void CTestLogicDlg::OnButtonClick(cGuiButton *pBtn)
{
	int id = pBtn->GetID();
    if (id == 110)
    {
        printf("CTestLogicDlg::OnButtonClick 110\n");
    }
    else if (id == 111)
    {
        // todo: ��������
    }
    //return 1;
}

void CTestLogicDlg::OnEditComplate(cGuiControl* pCtrl)
{

	printf("edit ok,  text is  %s\n", ((cGuiEdit*)pCtrl)->GetText());
}