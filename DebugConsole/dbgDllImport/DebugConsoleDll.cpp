
#include "DebugConsoleDll.h"

DebugConsoleDll::DebugConsoleDll()
{
	hDll = NULL;
	dbgPrint = NULL;
}

void DebugConsoleDll::inital()
{
	hDll = LoadLibrary(L"DebugConsole.dll");
	if (hDll)
	{
		// ��ȡ������ַ
		dbgPrint = (DebugFunc)GetProcAddress(hDll, "dbg");
	}
}
