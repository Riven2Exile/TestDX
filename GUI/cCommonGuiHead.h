//// 给逻辑层用于包头文件

#ifndef _COMMON_GUI_HEAD_H
#define _COMMON_GUI_HEAD_H

#include "cGuiButton.h"
#include "cGuiForm.h"
#include "cGuiLable.h"
#include "cGuiProgress.h"
#include "cGuiScroll.h"
#include "cGuiSlide.h"
#include "cGuiList.h"
#include "cGuiContainer.h"
#include "cGuiEdit.h"


#define DIR_UI_JSON "UI/"
#define SUFFIX_UI ".ui"




/////////// Gui消息
// Windows平台下
#ifdef _WINDOWS
#include <Windows.h>

enum eMouseKeyStateMask
{
	kMK_None	= 0,			//none key press down.
	LMK_CONTROL = MK_CONTROL,	//The CTRL key is down.
	LMK_LBUTTON = MK_LBUTTON,	//The left mouse button is down.
	LMK_MBUTTON = MK_MBUTTON,	//The middle mouse button is down.
	LMK_RBUTTON = MK_RBUTTON,	//The right mouse button is down.
	LMK_SHIFT	= MK_SHIFT,		//The SHIFT key is down.
	LMK_XBUTTON1 = MK_XBUTTON1,	//The first X button is down.
	LMK_XBUTTON2 = MK_XBUTTON2, //The second X button is down.
};


enum eVirtualKey{
	LVK_BACK	= VK_BACK,	//BACKSPACE key
	LVK_TAB		= VK_TAB,	//TAB key
	LVK_CLEAR	= VK_CLEAR,	//CLEAR key
	LVK_RETURN	= VK_RETURN,	//ENTER key
	LVK_SHIFT	= VK_SHIFT,	//SHIFT key
	LVK_CONTROL = VK_CONTROL,	//CTRL key
	LVK_ALT		= VK_MENU,	//ALT key
	LVK_PAUSE = VK_PAUSE,	//PAUSE key
	LVK_CAPITAL = VK_CAPITAL,	//CAPS LOCK key
	LVK_ESCAPE = VK_ESCAPE,	//ESC key
	LVK_SPACE = VK_SPACE,	//SPACEBAR
	LVK_PageUp = VK_PRIOR,	//PAGE UP key
	LVK_PageDown = VK_NEXT,	//PAGE DOWN key
	LVK_END = VK_END,	//END key
	LVK_HOME = VK_HOME, //HOME key
	LVK_LEFT = VK_LEFT,	//LEFT ARROW key
	LVK_UP = VK_UP,		//UP ARROW key
	LVK_RIGHT = VK_RIGHT,	//RIGHT ARROW key
	LVK_DOWN = VK_DOWN,		//DOWN ARROW key


	LVK_SNAPSHOT = VK_SNAPSHOT, // PRINT SCREEN key
	LVK_INSERT = VK_INSERT,	//INS key
	LVK_DELETE = VK_DELETE,	//DEL key
};


enum eGuiEventResult{
	kGER_None		= 0,	//未处理,继续往下传递
	kGER_Processed	= 1,	//已经处理
};

#else
// in the future 写其他平台相关性的东西

#endif // _WINDOWS




#endif  //_COMMON_GUI_HEAD_H