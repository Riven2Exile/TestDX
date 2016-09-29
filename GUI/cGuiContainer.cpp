#include "cGuiContainer.h"


cGuiContainer::cGuiContainer(cGuiControl* pFather) : cGuiControl(pFather)
{
	SetCtrlType(kCT_GuiContainer);
}

cGuiContainer::~cGuiContainer(){

}