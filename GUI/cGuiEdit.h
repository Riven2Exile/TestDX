
#ifndef _L_GUI_EDIT_H
#define _L_GUI_EDIT_H

#include "cGuiControl.h"

// ��ͨ�༭��

class cGuiEdit : public cGuiControl
{
public:
	explicit cGuiEdit(cGuiControl*);
	virtual ~cGuiEdit();


	virtual void Draw();


protected:
	virtual void run(const DWORD& dwElaspe);


	bool _bShowCursor;
	int _cursor_pos;	//���λ��

	std::string _edit_string; //�༭�������
};



#endif