
#ifndef _L_GUI_EDIT_H
#define _L_GUI_EDIT_H

#include "cGuiControl.h"

// 普通编辑框

class cGuiEdit : public cGuiControl
{
public:
	explicit cGuiEdit(cGuiControl*);
	virtual ~cGuiEdit();


	virtual void Draw();


protected:
	virtual void run(const DWORD& dwElaspe);


	bool _bShowCursor;
	int _cursor_pos;	//光标位置

	std::string _edit_string; //编辑框的内容
};



#endif