//// ���߼������ڰ�ͷ�ļ�

#include "cGuiButton.h"
#include "cGuiForm.h"
#include "cGuiLable.h"
#include "cGuiProgress.h"
#include "cGuiScroll.h"
#include "cGuiSlide.h"



#define DIR_UI_JSON "UI/"
#define SUFFIX_UI ".ui"






/////////// Gui��Ϣ
// Windowsƽ̨��
#ifdef _WINDOWS
#include <Windows.h>
#define LMK_CONTROL MK_CONTROL  //The CTRL key is down.
#define LMK_LBUTTON MK_LBUTTON  //The left mouse button is down.
#define LMK_MBUTTON MK_MBUTTON  //The middle mouse button is down.
#define LMK_RBUTTON MK_RBUTTON  //The right mouse button is down.
#define LMK_SHIFT   MK_SHIFT    //The SHIFT key is down.
#define LMK_XBUTTON1    MK_XBUTTON1 //The first X button is down.
#define LMK_XBUTTON2    MK_XBUTTON2 //The second X button is down.

#else
// in the future д����ƽ̨����ԵĶ���

#endif // _WINDOWS
