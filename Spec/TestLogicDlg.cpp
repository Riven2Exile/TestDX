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
    _btnAdd = (cGuiButton *)FindControl(111);

    //// �ؼ�ע�ắ��... ����Ϊ��Ա���� m_btn->SetClickFun(CTestLogicDlg::funName);
    _btn->SetClickFun((CtrlClickFun)&CTestLogicDlg::OnButtonClick);
    _btnAdd->SetClickFun((CtrlClickFun)&CTestLogicDlg::OnButtonClick);
}

// ���Զ����ť��ͬһ����Ӧ����
void CTestLogicDlg::OnButtonClick(int id)
{
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