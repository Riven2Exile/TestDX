
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

	int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);

	virtual void run(const DWORD& dwElaspe);

	void callback_get_focus(cGuiControl* pCtrl);
	void callback_lose_focus(cGuiControl* pCtrl);

	bool _bShowCursor;
	int _cursor_pos;	//���λ��

	std::string _edit_string; //�༭�������
};



#endif