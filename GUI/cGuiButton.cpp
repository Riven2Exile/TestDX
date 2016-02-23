#include "cGuiButton.h"

#include "cCommonGuiHead.h"

cGuiButton::cGuiButton(cGuiControl* pFather):cGuiControl(pFather)
{
    SetCtrlType(kCT_GuiButton);

    _btnState = kBS_Normal;
    _pFun = NULL;
}

cGuiButton::~cGuiButton()
{

}
///////////////
void cGuiButton::SetBtnStateImage(eBtnState state, const char* szName)
{
    if(state < kBS_Normal || state >= kBS_Num)
        return ;

    _strImage[state] = szName;
}
void cGuiButton::SetBtnState(eBtnState e)
{
    _btnState = e;
}

cGuiButton::eBtnState cGuiButton::GetBtnState()
{
    return _btnState;
}

/////////////
int cGuiButton::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return 1;

    if (GetBtnState() == kBS_Disable)
    {
        return 0;
    }

    // TODO .. ����Դ�������ʽ��
    if (IsAt(x, y))
    {
        if (GetBtnState() == kBS_Clicked && nFlag & LMK_LBUTTON)
        {
            // ����
        }
        else
        {
            HandleMouseOn();
        }
    }
    else
    {
        if (GetBtnState() == kBS_Clicked && nFlag & LMK_LBUTTON)
        {
            // ����
        }
        else
        {
            HandleMouseLeave();
        }
    }

}

int cGuiButton::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return 1;

    if (IsAt(x, y))
    {
        if (GetBtnState() == kBS_Disable)
        {
            return 0;
        }
        else
        {
            SetBtnState(kBS_Clicked);
            SetTexture(_strImage[kBS_Clicked].c_str());
            return 0;
        }
    }

    return 1;
}

int cGuiButton::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
{
    if (IsShow() == false)
        return 1;

    bool bAt = IsAt(x, y);

    if(GetBtnState() == kBS_Disable && bAt)
        return 0;   //��Ϣ��ֹ

    if (GetBtnState() == kBS_Clicked && bAt )
    {
        // ���а�ť.. todo: �Զ��庯��? 
        OnBtnClicked();
        
    }
    
    SetBtnState(kBS_Normal);
    SetTexture(_strImage[kBS_Normal].c_str());
    
    
    return 1;
}

/////// ��Ϣ��ҵ����Ӧ
void cGuiButton::SetClickFun(CtrlClickFun pF)
{
    _pFun = pF;
}

int cGuiButton::OnBtnClicked()
{
    printf("cGuiButton::OnBtnClicked\n");
    if (_pFun)
    {
        (this->*_pFun)(GetID());
    }
    return 1;
}



void cGuiButton::HandleMouseOn()
{
    this->SetTexture(_strImage[kBS_MouseOn].c_str());
}
void cGuiButton::HandleMouseLeave()
{
    this->SetTexture(_strImage[kBS_Normal].c_str());
}