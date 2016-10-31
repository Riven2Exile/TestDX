
#ifndef _L_GUI_EDIT_H
#define _L_GUI_EDIT_H

#include "cGuiControl.h"

// ��ͨ�༭��


typedef int(*char_code) (unsigned int, unsigned long, char*, int);


class cGuiEdit : public cGuiControl
{
public:
	explicit cGuiEdit(cGuiControl*);
	virtual ~cGuiEdit();

	const char* GetText();

	virtual void Draw();

	void SetEnterReturnCallback(normal_cb_fun cb);

protected:
	virtual eGuiEventResult OnChar(const unsigned int& wparam, const unsigned long& lparam);
	virtual eGuiEventResult OnKeyDown(const unsigned int& wparam, const unsigned long& lparam);
	//int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);

	virtual void run(const DWORD& dwElaspe);

	void callback_get_focus(cGuiControl* pCtrl);
	void callback_lose_focus(cGuiControl* pCtrl);

	bool _bShowCursor;
	int _cursor_pos;	//���λ��
	int _word_size;		//���ָ���, ���ֺ���ĸ������һ�� word

	std::string _edit_string; //�༭�������

	normal_cb_fun _edit_enter_cb_fun;

	// ��ĸ�ͺ��ֵ��ж����
};



#endif