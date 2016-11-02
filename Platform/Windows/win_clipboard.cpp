
#include "stdafx.h"
#include "win_clipboard.h"


bool CWinClipBoard::Copy(const char* str)
{
	bool rv = true;
	char /*FAR*/ * PProg;
	do 
	{
		if (nullptr == str){
			rv = false; break;
		}

		if (!OpenClipboard(_hwnd))	{
			rv = false; break;
		}
		if (!::EmptyClipboard()){
			rv = false; break;
		}

		// 将字符串转换成宽字符串,然后再复制到剪贴板
		int nLen = strlen(str);
		HGLOBAL HProg = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (nLen + 1));
		if (HProg == NULL){
			::CloseClipboard();
			rv = false; break;
		}

		PProg = (char*)::GlobalLock(HProg);
		memset(PProg, 0, (nLen + 1));
		memcpy_s(PProg, nLen , str, nLen );
		::GlobalUnlock(HProg);

		if (!::SetClipboardData(CF_TEXT/*CF_UNICODETEXT*/, HProg))
		{

		}
		
	} while (0);
	
	::CloseClipboard();
	return rv;
}

void CWinClipBoard::SetHandle(const HWND& h)
{
	_hwnd = h;
}

bool CWinClipBoard::Paste(std::string & str)
{
	bool rv = true;
	HGLOBAL HClip;
	char FAR * PClip;
	do 
	{
		if (!OpenClipboard(_hwnd)){
			rv = false; break;
		}
		HClip = ::GetClipboardData(CF_TEXT/*CF_UNICODETEXT*/);
		if (HClip == NULL){
			::CloseClipboard();
			rv = false; break;
		}
		SIZE_T dwSize = ::GlobalSize(HClip);
		PClip = (char *)::GlobalLock(HClip);
		if (NULL == PClip){
			::CloseClipboard();
			rv = false; break;
		}

		str = PClip;
		::GlobalUnlock(HClip);
		::CloseClipboard();
	} while (0);
	
	return rv;
}

