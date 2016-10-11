#include "cGuiForm.h"
#include "cCommonGuiHead.h"

cGuiForm::cGuiForm(cGuiControl* pFather):cGuiControl(pFather)
{
    SetCtrlType(kCT_GuiForm); //��Ҫָ������

    //����ǶԻ���Ļ���Ĭ�Ͽ����϶�
    SetDrag(true);

    
}

cGuiForm::cGuiForm():cGuiControl(NULL)
{
	SetCtrlType(kCT_GuiForm); //��Ҫָ������

	//����ǶԻ���Ļ���Ĭ�Ͽ����϶�
	SetDrag(true);
}

cGuiForm::~cGuiForm()
{

}

//////////
void cGuiForm::SetName(const char* pszName /* = */ )
{
    _strName = pszName;
}

//////////
void cGuiForm::Show(bool bShow /*= true*/)
{
    cGuiControl::Show(bShow);
}

void cGuiForm::SetOffSet(const int& x, const int& y){
	_offsetX = x;
	_offsetY = y;

	int fx = 0, fy = 0; //���Եõ����յ���Ļ����
	int tx = 0, ty = 0;
	cGuiControl *pTempFather = _pFather;
	while (pTempFather)
	{
		pTempFather->GetOffSet(tx, ty);
		fx += tx;
		fy += ty;
		pTempFather = pTempFather->GetFather();
	}

	_sprite->SetX(fx + x);
	_sprite->SetY(fy + y);
}

//////////
// int cGuiForm::OnMouseMove(const int& x, const int& y, const unsigned int& nFlag)
// {
//     //�ȸ��ӿؼ���������Ϣ
//     if(cGuiControl::OnMouseMove(x, y, nFlag) == 0)
//         return 0;
// 
//     if (CanDrag() && _bClicked && nFlag & LMK_LBUTTON )
//     {
//         // �����϶�
//         int xx = 0, yy = 0;
//         GetPos(xx, yy);
// 		// ��ʵ����Ӧ��Ҫ���϶Ի����offset�ƶ�
// 		_offsetX += (x - _dragX - xx);
// 		_offsetY += (y - _dragY - yy);
// 		//SetOffSet(_offsetX + (x - _dragX - xx), _offsetY + (y - _dragY - yy));
//         AddAllOffset(x - _dragX - xx, y - _dragY - yy);
//     }
//     else
//     {
//         _bClicked = false;
//     }
//     return 1;
// }

// int cGuiForm::OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag)
// {
//     if(IsShow() == false)
//         return 1;
// 
//     //�ȸ��ӿؼ���������Ϣ
// 	if (cGuiControl::OnLButtonDown(x, y, nFlag) == 0){
// 		//���ӿؼ�������, ����������Ϊ���ؼ�Ҳ�л�ý���
// 		if (GetFather() && GetFather()->IsFocus() == false){
// 			GetFather()->ClearChildFocus(this); //������ֵܵĽ���
// 			SetFocus(true); //�Լ���ý���
// 			if (_cb_gain_focus){
// 				_cb_gain_focus(this);
// 			}
// 		}
// 		return 0;
// 	}
// 
//     if (IsAt(x, y))
//     {
//         _bClicked = true;
//         int xx = 0, yy = 0;
//         GetPos(xx, yy);
//         _dragX = x - xx;
//         _dragY = y - yy;
// 
//         return 0; //��Ϣ�����񣬲������´���
//     }
//    
//     return 1;
// }

// int cGuiForm::OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag)
// {
//     cGuiControl::OnLButtonUp(x, y, nFlag);  //�ȸ��ӿؼ���������Ϣ
// 
// 
//     return 1;
// }