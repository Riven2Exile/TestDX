#include "cGuiProgress.h"
#include "cCommonGuiHead.h"


cGuiProgress::cGuiProgress(cGuiControl* pFather):cGuiControl(pFather)
{
    SetCtrlType(kCT_GuiProcess);

    _pBar = new cGuiLable(this);
	_pBack = new cGuiLable(this);

	AddControl(_pBar);
	AddControl(_pBack);
    _nPos = max_pos;
}

cGuiProgress::~cGuiProgress()
{

}


void cGuiProgress::SetBarImage(const char* szName)
{
	_pBar->SetTexture(szName);
}

void cGuiProgress::SetBackImage(const char* szName)
{
    //SetTexture(szName);
	_pBack->SetTexture(szName);
}

void cGuiProgress::SetOffSet(const int& x, const int& y)
{
	cGuiControl::SetOffSet(x, y);

	int fx = 0, fy = 0;
	GetPos(fx, fy);
	_pBar->SetPos(fx , fy);
	_pBack->SetPos(fx, fy);
}


void cGuiProgress::SetProgress(unsigned int nPos)
{
	float r = 1.0f;
    // fix
    if (nPos > max_pos)
    {
        nPos = max_pos;
    }

	if (nPos != max_pos)
	{
		r = nPos / (float)max_pos;
	}

	FRECT fRC;
	fRC.right = r;
    _pBar->SetClip(fRC); //Ç°¾°Ìõ
}

void cGuiProgress::SetWidth(float fw)
{
	cGuiControl::SetWidth(fw);
	_pBack->SetWidth(fw);
	_pBar->SetWidth(fw);
}
void cGuiProgress::SetHeight(float fh)
{
	cGuiControl::SetHeight(fh);
	_pBack->SetHeight(fh);
	_pBar->SetHeight(fh);
}