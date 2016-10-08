
#include "cGuiEdit.h"

cGuiEdit::cGuiEdit(cGuiControl* pFather) : cGuiControl(pFather)
{
	SetCtrlType(kCT_GuiEdit);
	_bShowCursor = false;
	_cursor_pos = 0;
}

cGuiEdit::~cGuiEdit(){

}

///////

void cGuiEdit::Draw(){
	__super::Draw();

	// »­ÎÄ×Ö
	if (_strText.size())
	{
		TextOutput(GetScreenPosX(), GetScreenPosY(), _strText.c_str());
	}
	
	if (_bShowCursor)
	{
		TextOutput(GetScreenPosX(), GetScreenPosY(), "|");
	}
}


void cGuiEdit::run(const DWORD& dwElaspe)
{
	//¹â±êÉÁË¸ "|"
	static DWORD e = 0;
	e += dwElaspe;
	if (e >= 500)
	{
		_bShowCursor = !_bShowCursor;
		e -= 500;
	}


}
