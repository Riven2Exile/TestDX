#include "stdafx.h"
#include "TestLogicDlg.h"

/*
不同控件的响应形式不一样, 响应的话，可能应该需要在不同的子类去做
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
    _btnAdd = (cGuiButton *)FindControl(111);
	_edit_ctrl = (cGuiEdit*)FindControl(108);

    //// 控件注册函数... 函数为成员函数 m_btn->SetClickFun(CTestLogicDlg::funName);
    _btn->SetClickFun((CtrlClickFun)&CTestLogicDlg::OnButtonClick);
    _btnAdd->SetClickFun((CtrlClickFun)&CTestLogicDlg::OnButtonClick);

	_edit_ctrl->SetEnterReturnCallback(std::bind(&CTestLogicDlg::OnEditComplate, this, std::placeholders::_1)); //注册编辑结束函数
}

// 可以多个按钮用同一个响应函数
void CTestLogicDlg::OnButtonClick(int id)
{
    if (id == 110)
    {
        printf("CTestLogicDlg::OnButtonClick 110\n");
    }
    else if (id == 111)
    {
        // todo: 进度条加
    }
    //return 1;
}

void CTestLogicDlg::OnEditComplate(cGuiControl* pCtrl)
{

	printf("edit ok,  text is  %s\n", ((cGuiEdit*)pCtrl)->GetText());
}