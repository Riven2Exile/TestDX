#ifndef _WIN_CLIPBOARD_H
#define _WIN_CLIPBOARD_H


// windows clipboard ������


class CWinClipBoard
{
public:
	static CWinClipBoard& Instance() {
		static CWinClipBoard inst;
		return inst;
	}


	void SetHandle(const HWND& h);

	bool Copy(const char* );
	bool Paste(std::string & str);

protected:
	HWND _hwnd;
};




#endif