
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
		// 获取函数地址
		dbgPrint = (DebugFunc)GetProcAddress(hDll, "dbg");
	}
}
