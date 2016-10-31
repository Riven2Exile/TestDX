
#ifndef _L_GUI_EDIT_H
#define _L_GUI_EDIT_H

#include "cGuiControl.h"

// 普通编辑框


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
	int _cursor_pos;	//光标位置
	int _word_size;		//文字个数, 汉字和子母都当做一个 word

	std::string _edit_string; //编辑框的内容

	normal_cb_fun _edit_enter_cb_fun;

	// 字母和汉字的判断相关
};



#endif