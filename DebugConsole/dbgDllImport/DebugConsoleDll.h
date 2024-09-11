#pragma once
#include <windows.h>

#define CallDebug(LPCTSTR) DebugConsoleDll::dbgPrint(LPCTSTR s)

typedef BOOL(*DebugFunc)(LPCTSTR s);

class DebugConsoleDll
{
	public:
		HINSTANCE hDll;
		void inital();
		DebugConsoleDll();
		static DebugFunc dbgPrint;
};

