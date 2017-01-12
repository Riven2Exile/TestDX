/*	
	
*/
#pragma once

class CCrashDump
{
public:
	CCrashDump(LPCSTR lpKey = "");
	~CCrashDump();
	static void DumpFile(LPTSTR lpName);
	static void DumpMiniFile(LPTSTR lpName);
	static int DumpThread(PEXCEPTION_POINTERS ExceptionInfo);
    static DWORD& DumpType() { return m_DumpType; }
protected:
	static LONG WINAPI TopLevelExceptionFilter(PEXCEPTION_POINTERS ExceptionInfo);
	static LONG WINAPI TopLevelExceptionFilterFirst(PEXCEPTION_POINTERS ExceptionInfo);
    static DWORD WINAPI threadFunc(LPVOID lpParam);

	static void AddTime(LPTSTR lpStr);

	static LONG DumpFileByName(LPTSTR lpName, PEXCEPTION_POINTERS ExceptionInfo, int dumpType);
	//static CString GetVersion();
    static DWORD m_DumpType;
private:
};
