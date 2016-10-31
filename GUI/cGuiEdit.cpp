
#include "cGuiEdit.h"
#include "cCommonGuiHead.h"


extern char_code edit_char_code;


cGuiEdit::cGuiEdit(cGuiControl* pFather) : cGuiControl(pFather)
, _word_size(0)
, _cursor_pos(0)
{
	SetCtrlType(kCT_GuiEdit);
	_bShowCursor = false;
	_cursor_pos = 0;

	SetGainFocusCallBack(std::bind(&cGuiEdit::callback_get_focus, this, std::placeholders::_1));
	SetLoseFocusCallBack(std::bind(&cGuiEdit::callback_lose_focus, this, std::placeholders::_1));
}

cGuiEdit::~cGuiEdit(){

}

///////

const char* cGuiEdit::GetText(){
	return _strText.c_str();
}

void cGuiEdit::Draw(){
	__super::Draw();

	// 画文字
	if (_strText.size())
	{
		TextOutput(GetScreenPosX(), GetScreenPosY(), _strText.c_str());
	}
	
	if (_bFocus && _bShowCursor)
	{
		TextOutput(GetScreenPosX() + _cursor_pos * 6 - 1, GetScreenPosY(), "|"); //字体宽度
	}
}


void cGuiEdit::run(const DWORD& dwElaspe)
{
	//光标闪烁 "|"
	static DWORD e = 0;
	e += dwElaspe;
	if (e >= 500)
	{
		_bShowCursor = !_bShowCursor;
		e -= 500;
	}
}

void cGuiEdit::SetEnterReturnCallback(normal_cb_fun cb){
	_edit_enter_cb_fun = cb;
}


eGuiEventResult cGuiEdit::OnChar(const unsigned int& wparam, const unsigned long& lparam){
	if (__super::OnChar(wparam, lparam) == kGER_Processed){
		return kGER_Processed;
	}

	if (_bFocus)
	{
		// 开始处理
 		static char wc[3] = "";
		edit_char_code(wparam, sizeof(wparam), (char*)&wc, sizeof(wc));
// 		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, (LPCWCH)&wparam, sizeof(wparam), wc, 3, NULL, NULL);
// 		char *p = "一";
		char ch = wc[0];
		bool zhongwen = (byte)wc[0] > 0x7f;
		
		if (zhongwen == false)
		{
			if (LVK_BACK == ch) //退格
			{
				if (_cursor_pos > 0 && _strText.length() >= _cursor_pos) {
					//如果有两个char,则需要判断是否为中文
					if (_cursor_pos >= 2) {
						if ((byte)_strText.at(_cursor_pos - 2) > 0x7f)
						{
							if ((byte)_strText.at(_cursor_pos - 1) <= 0x7f)
							{
								//英文
								_strText = _strText.erase(_cursor_pos - 1, 1);
								_cursor_pos -= 1;
							}
							else{
								//中文
								_strText = _strText.erase(_cursor_pos - 2, 2);
								_cursor_pos -= 2;
							}
							
						}
						else{
							_strText = _strText.erase(_cursor_pos - 1, 1);
							--_cursor_pos;
						}
					}
					else{
						//肯定是英文
						_strText = _strText.erase(_cursor_pos - 1, 1);
						--_cursor_pos;
					}
				}
				return kGER_Processed;
			}
			else if (LVK_RETURN == wparam) //回车键
			{
				if (_edit_enter_cb_fun){
					_edit_enter_cb_fun(this);
				}
				//再考虑要不要失去焦点一次?
				return kGER_Processed;
			}
			
	
			//英文
			++this->_cursor_pos;
		}
		else{
			//中文
			_cursor_pos += 2;
		}


		_strText.append(wc);
		
		++this->_word_size;
#ifdef _DEBUG
		printf("on char :%s  是否中文:%d\n", wc, zhongwen);
#endif
	}

	return kGER_None;
}

eGuiEventResult cGuiEdit::OnKeyDown(const unsigned int& wparam, const unsigned long& lparam){
	if (__super::OnKeyDown(wparam, lparam) == kGER_Processed){
		return kGER_Processed;
	}

	if (_bFocus)
	{
		if (VK_LEFT == wparam)
		{
			if (_cursor_pos > 0)
			{
				//可能有bug
				if ((byte)_strText.at(_cursor_pos - 1) > 0x7f)
				{
					_cursor_pos -= 2;
				}
				else{
					--_cursor_pos;
				}
			}
			return kGER_Processed;
		}
		else if(VK_RIGHT == wparam){
			if (_strText.length() > _cursor_pos)
			{
				if ((byte)_strText.at(_cursor_pos) > 0x7f)
				{
					_cursor_pos += 2;
				}
				else{
					++_cursor_pos;
				}
			}
			return kGER_Processed;
		}
		else if (LVK_DELETE == wparam) //删除键
		{
			if (_cursor_pos < _strText.length())
			{
				if ((byte)_strText.at(_cursor_pos) > 0x7f)
				{
					_strText = _strText.erase(_cursor_pos, 2);
				}
				else{
					_strText = _strText.erase(_cursor_pos, 1);
				}
			}
			return kGER_Processed;
		}
	}
	return kGER_None;
}


void cGuiEdit::callback_get_focus(cGuiControl* pCtrl){
	_bShowCursor = true;
}

void cGuiEdit::callback_lose_focus(cGuiControl* pCtrl){
	_bShowCursor = false;
}