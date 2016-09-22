#ifndef _L_GUI_SLIDE_H
#define _L_GUI_SLIDE_H

#include "cGuiControl.h"

class cGuiProgress;
class cGuiButton;


class cGuiSlide : public cGuiControl
{
public:
	explicit cGuiSlide(cGuiControl* pfather);
	virtual ~cGuiSlide();

	virtual void SetOffSet(const int& x, const int& y);

private:

	cGuiProgress *m_pPro;
	cGuiButton* m_pBtn;
};



#endif