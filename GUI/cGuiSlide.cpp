#include "cGuiSlide.h"
#include "cGuiProgress.h"
#include "cGuiButton.h"

cGuiSlide::cGuiSlide(cGuiControl* pfather) : cGuiControl(pfather)
, m_pPro(nullptr)
, m_pBtn(nullptr)
{
	this->SetCtrlType(kCT_GuiSlide);
	m_pBtn = new cGuiButton(this);
	m_pBtn->SetBtnStateImage(cGuiButton::kBS_Normal, "slide_btn");
	m_pBtn->SetBtnStateImage(cGuiButton::kBS_MouseOn, "slide_btn");
	m_pBtn->SetBtnStateImage(cGuiButton::kBS_Clicked, "slide_btn");
	m_pBtn->SetBtnStateImage(cGuiButton::kBS_Disable, "slide_btn");
	m_pBtn->SetWidth(11);
	m_pBtn->SetHeight(17);
	AddControl(m_pBtn);

	m_pPro = new cGuiProgress(this);
	//m_pPro->SetBackImage("slide_background");
	m_pPro->SetBarImage("slide_bar");
	m_pPro->SetWidth(93);
	m_pPro->SetHeight(7);
	AddControl(m_pPro);

	this->SetTexture("slide_background");
	SetWidth(103);
	SetHeight(13);

	//SetOffSet(0, 0);// 【CGuiContrl的构造函数中,不是执行cGuiSlide::SetOffSet】
}


cGuiSlide::~cGuiSlide()
{

}

void cGuiSlide::SetOffSet(const int& x, const int& y)
{
	cGuiControl::SetOffSet(x, y);

	int fx = 0, fy = 0;
	GetPos(fx, fy);
	m_pPro->SetOffSet(x, y);
	m_pBtn->SetPos(fx, fy);
}
