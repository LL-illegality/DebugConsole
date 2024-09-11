// DebugConsole.h: DebugConsole DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include <chrono>
#include <iomanip>
#include <sstream>


// CDebugConsoleApp
// 有关此类实现的信息，请参阅 DebugConsole.cpp
//
typedef void (*cmdParseFunction)(LPCTSTR s);

class CDebugConsoleApp : public CWinApp
{
public:
	CDebugConsoleApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern "C" __declspec(dllexport) BOOL PASCAL dbg(LPCTSTR s);
extern "C" __declspec(dllexport) BOOL PASCAL setCmdParseFunc(cmdParseFunction func);
