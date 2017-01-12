#include "stdafx.h"
#include "wm_crash_dump.h "
#include <dbghelp.h>

#include <Windows.h>
#include <intrin.h>

#pragma comment(lib, "dbghelp.lib")

#define DUMP_PATH L"dump/"

void myInvalidParameterHandler(const wchar_t* expression,
							   const wchar_t* function, 
							   const wchar_t* file, 
							   unsigned int line, 
							   uintptr_t pReserved)
{
#ifdef _WIN64
	__debugbreak();
#else
	__asm int 3;
#endif // _WIN64
}

void myPurecallHandler(void)
{
#ifdef _WIN64
	__debugbreak();
#else
	__asm int 3;
#endif // _WIN64
}
DWORD CCrashDump::m_DumpType = MiniDumpWithIndirectlyReferencedMemory;

static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDisableFun(__in LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	return NULL;
}
LPCSTR g_lpszKey = "";
CCrashDump::CCrashDump(LPCSTR lpKey)
{	
    ::SetUnhandledExceptionFilter(CCrashDump::TopLevelExceptionFilter);
    if (lpKey[0])
    {
	    AddVectoredExceptionHandler(FALSE, CCrashDump::TopLevelExceptionFilterFirst);
    }

	m_DumpType = MiniDumpWithFullMemory; //默认打fulldump
	unsigned char code[8];
	int size = 0;
	code[size++] = 0x33;
	code[size++] = 0xc0;
	code[size++] = 0xc2;
	code[size++] = 0x08;
	code[size++] = 0x00;
	SIZE_T dw = 0;
	DWORD dwOldFlag = 0, dwTempFlag = 0;

    if (lpKey[0])
    {
        //VirtualProtect(AddVectoredExceptionHandler, size, PAGE_READWRITE, &dwOldFlag);
		//WriteProcessMemory(INVALID_HANDLE_VALUE, AddVectoredExceptionHandler, code, size, &dw);
		//VirtualProtect(AddVectoredExceptionHandler, size, dwOldFlag, &dwTempFlag);

    }

	code[3] = 0x04;
    //VirtualProtect(SetUnhandledExceptionFilter, size, PAGE_READWRITE, &dwOldFlag);
	//WriteProcessMemory(INVALID_HANDLE_VALUE, SetUnhandledExceptionFilter, code, size, &dw);
	//VirtualProtect(SetUnhandledExceptionFilter, size, dwOldFlag, &dwTempFlag);


	//_set_invalid_parameter_handler(myInvalidParameterHandler);
	//_set_purecall_handler(myPurecallHandler);
    CreateDirectory(DUMP_PATH, NULL);
    g_lpszKey = lpKey;
}


CCrashDump::~CCrashDump()
{

}

void CCrashDump::AddTime(LPTSTR lpStr)
{
	if (!lpStr)
	{
		return;
	}

	SYSTEMTIME st;
	GetLocalTime(&st);
	//format dump2010-03-08-15:58
	::wsprintf(lpStr, _T("%s%d-%02d-%02d-%02d-%02d.dmp"), lpStr, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

}

typedef BOOL (WINAPI* MINIDUMP_WRITE_DUMP)(
			  IN HANDLE hProcess,
			  IN DWORD ProcessId,
			  IN HANDLE hFile,
			  IN MINIDUMP_TYPE DumpType,
			  IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
			  IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
			  IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
			  );

DWORD WINAPI CCrashDump::threadFunc(LPVOID lpParam)
{
    PEXCEPTION_POINTERS ExceptionInfo = (PEXCEPTION_POINTERS)lpParam;
#ifdef _CLIENT
    CAntiBotDataSeg oo;
    oo.OnEnd();
#endif
    LONG ret = EXCEPTION_CONTINUE_SEARCH;

    TCHAR chDumpModule[MAX_PATH] = {0};

    wsprintf(chDumpModule, L"%s%s%s-%x", DUMP_PATH, L"my_app"/*AfxGetApp()->m_pszExeName*/, L"_ver_"/*GetVersion().GetString()*/, ExceptionInfo->ExceptionRecord->ExceptionAddress);

    AddTime(chDumpModule);
    HANDLE hFile = CreateFile(
        chDumpModule,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL /*| FILE_FLAG_WRITE_THROUGH*/,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, L"DUMP DIR",L"",0);
        return ret;
    }
    MINIDUMP_EXCEPTION_INFORMATION eInfo;
    eInfo.ThreadId = GetCurrentThreadId();
    eInfo.ExceptionPointers = ExceptionInfo;
    eInfo.ClientPointers = FALSE;

#ifdef _SERVER
    BOOL bResult = ::MiniDumpWriteDump(
        GetCurrentProcess(),
        GetCurrentProcessId(), 
        hFile,
        MiniDumpWithFullMemory,
        &eInfo,
        NULL,
        NULL);
#else
    BOOL bResult = MiniDumpWriteDump(
        GetCurrentProcess(),
        GetCurrentProcessId(), 
        hFile,
        (MINIDUMP_TYPE)m_DumpType,
        &eInfo,
        NULL,
        NULL);
#endif

    if (bResult)
    {
        ret = EXCEPTION_EXECUTE_HANDLER;
    }

    CloseHandle(hFile);

#ifdef _CLIENT
    char strCmd[256] = {};
    wsprintf(strCmd, "ftpdump.exe %s", chDumpModule);
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效
    si.wShowWindow = TRUE; // 此成员设为TRUE的话则显示新建进程的主窗口
    ::CreateProcess(0, strCmd, 0, 0, 0, 0, 0, 0, &si, &pi);
#endif
    ::TerminateProcess(GetCurrentProcess(), 0);
    return 0;
}

LONG WINAPI CCrashDump::TopLevelExceptionFilter( PEXCEPTION_POINTERS ExceptionInfo)
{
    static HANDLE hThread = NULL;
    static DWORD dwThreadID = 0;
    hThread = CreateThread(NULL, 0, threadFunc, (LPVOID)ExceptionInfo, 0, &dwThreadID);
    if ( WAIT_TIMEOUT == WaitForSingleObject(hThread, 200000))
    {
        threadFunc((LPVOID)ExceptionInfo);
    }
	return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI CCrashDump::TopLevelExceptionFilterFirst( PEXCEPTION_POINTERS ExceptionInfo)
{
    bool NeedDump = false;
    switch(ExceptionInfo->ExceptionRecord->ExceptionCode)
    {
    //case STATUS_WAIT_0:
    //case STATUS_ABANDONED_WAIT_0:
    //case STATUS_USER_APC:
    //case STATUS_TIMEOUT: 
    //case STATUS_PENDING: 
    //case DBG_EXCEPTION_HANDLED:
    //case DBG_CONTINUE:   
    //case STATUS_SEGMENT_NOTIFICATION:        
    //case DBG_TERMINATE_THREAD:              
    //case DBG_TERMINATE_PROCESS:               
    //case DBG_CONTROL_C:  
    //case DBG_CONTROL_BREAK:                   
    //case DBG_COMMAND_EXCEPTION:               
    //case STATUS_GUARD_PAGE_VIOLATION:         
    //case STATUS_DATATYPE_MISALIGNMENT:        
    //case STATUS_BREAKPOINT:                  
    //case STATUS_SINGLE_STEP:                  
    case DBG_EXCEPTION_NOT_HANDLED:           
    case STATUS_ACCESS_VIOLATION:             
    case STATUS_IN_PAGE_ERROR:                
    case STATUS_INVALID_HANDLE:               
    case STATUS_NO_MEMORY:                    
    //case STATUS_ILLEGAL_INSTRUCTION:          
    //case STATUS_NONCONTINUABLE_EXCEPTION:     
    //case STATUS_INVALID_DISPOSITION:          
    case STATUS_ARRAY_BOUNDS_EXCEEDED:
        {
            NeedDump = true;
        }
        break;
    case STATUS_FLOAT_DENORMAL_OPERAND:       
    case STATUS_FLOAT_DIVIDE_BY_ZERO:         
    case STATUS_FLOAT_INEXACT_RESULT:         
    case STATUS_FLOAT_INVALID_OPERATION:     
    case STATUS_FLOAT_OVERFLOW:               
    case STATUS_FLOAT_STACK_CHECK:            
    case STATUS_FLOAT_UNDERFLOW: 
        {
            //要产要minidump
        }
        break;
    case STATUS_INTEGER_DIVIDE_BY_ZERO:       
    //case STATUS_INTEGER_OVERFLOW:      整形溢出要不要当机？       
    //case STATUS_PRIVILEGED_INSTRUCTION:       
    case STATUS_STACK_OVERFLOW:               
    //case STATUS_CONTROL_C_EXIT:               
    //case STATUS_FLOAT_MULTIPLE_FAULTS:        
    //case STATUS_FLOAT_MULTIPLE_TRAPS:         
    //case STATUS_REG_NAT_CONSUMPTION:     
    //case STATUS_SXS_EARLY_DEACTIVATION:    
    //case STATUS_SXS_INVALID_DEACTIVATION: 
        {
            NeedDump = true;
        }
    }

    if (NeedDump)
    {
        static HANDLE hThread = NULL;
        hThread = CreateThread(NULL, 0, threadFunc, (LPVOID)ExceptionInfo, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        return EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
        if (g_lpszKey && g_lpszKey[0])
        {
            //ILog::WriteLog(g_lpszKey, "ExceptionCode:%x", ExceptionInfo->ExceptionRecord->ExceptionCode);
        }

    }
    return EXCEPTION_CONTINUE_SEARCH;
}

void CCrashDump::DumpFile(LPTSTR lpName)
{
	__try
	{
#ifdef _WIN64
		__debugbreak();
#else
		__asm int 3;
#endif // _WIN64
	}
	__except(DumpFileByName(lpName, GetExceptionInformation(), MiniDumpWithFullMemory), EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

void CCrashDump::DumpMiniFile(LPTSTR lpName)
{
	__try
	{
#ifdef _WIN64
		__debugbreak();
#else
		__asm int 3;
#endif // _WIN64
	}
	__except(DumpFileByName(lpName, GetExceptionInformation(), MiniDumpNormal), EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

int CCrashDump::DumpThread(PEXCEPTION_POINTERS ExceptionInfo)
{
	LONG ret = EXCEPTION_CONTINUE_SEARCH;

	TCHAR chDumpModule[MAX_PATH] = {0};
	::GetModuleFileName(NULL, chDumpModule, MAX_PATH);
	int len = lstrlen(chDumpModule);

	AddTime(chDumpModule);
	//chDumpModule
	HANDLE hFile = CreateFile(
		chDumpModule,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL /*| FILE_FLAG_WRITE_THROUGH*/,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return ret;
	}



	MINIDUMP_EXCEPTION_INFORMATION eInfo;
	eInfo.ThreadId = GetCurrentThreadId();
	eInfo.ExceptionPointers = ExceptionInfo;
	eInfo.ClientPointers = FALSE;

	BOOL bResult = MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(), 
		hFile,
		MiniDumpWithIndirectlyReferencedMemory,
		&eInfo,
		NULL,
		NULL);
	if (bResult)
	{
		ret = EXCEPTION_EXECUTE_HANDLER;
	}

	CloseHandle(hFile);
	return ret;
}

LONG CCrashDump::DumpFileByName(LPTSTR lpName, PEXCEPTION_POINTERS ExceptionInfo, int dumpType)
{
	TCHAR chDumpFile[MAX_PATH] = {0};
	lstrcpy(chDumpFile, lpName);
	AddTime(chDumpFile);

	HANDLE hFile = CreateFile(
		chDumpFile,
		GENERIC_WRITE|GENERIC_READ,
		FILE_SHARE_WRITE|FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	MINIDUMP_EXCEPTION_INFORMATION eInfo;
	eInfo.ThreadId = GetCurrentThreadId();
	eInfo.ExceptionPointers = ExceptionInfo;
	eInfo.ClientPointers = FALSE;

	BOOL bResult = MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(), 
		hFile,
		(MINIDUMP_TYPE)dumpType,
		&eInfo,
		NULL,
		NULL);

	CloseHandle(hFile);
	return EXCEPTION_EXECUTE_HANDLER;
}

// CString CCrashDump::GetVersion()
// {
// 	CString s;
// 	s.Format("VER%d.%02d.%02d%02d%d", MAJOR_VERSION, MINOR_VERSION, SVN_VERSION / 1000, ((SVN_VERSION - (SVN_VERSION % 10)) / 10) % 100, SVN_VERSION % 10);
// 	return s;
// }