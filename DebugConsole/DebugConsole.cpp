// DebugConsole.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "DebugConsole.h"
#include "DbgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// 唯一的 CDebugConsoleApp 对象

CDebugConsoleApp theApp;
DbgDlg dlgDebug;

extern "C" __declspec(dllexport) BOOL PASCAL dbg(LPCTSTR s)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	dlgDebug.dlgPrint(s);
	return true;
}

extern "C" __declspec(dllexport) BOOL PASCAL setCmdParseFunc(cmdParseFunction func)
{
	dlgDebug.cmdParse = func;
    return true;
}

// CDebugConsoleApp

BEGIN_MESSAGE_MAP(CDebugConsoleApp, CWinApp)
END_MESSAGE_MAP()


// CDebugConsoleApp 构造

CDebugConsoleApp::CDebugConsoleApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// CDebugConsoleApp 初始化

BOOL CDebugConsoleApp::InitInstance()
{
	CWinApp::InitInstance();
	setlocale(LC_ALL, "zh_CN.UTF-8");
	dlgDebug.EnableDynamicLayout();
	dlgDebug.Create(IDD_DBG, CWnd::FindWindowW(L"SysListView32", NULL));
	dlgDebug.ShowWindow(SW_SHOW);
	dbg(L"Launched Successfully");
	dbg(L"DebugConsole DLL by LL");
	dbg(L"Type 'help' for the command list");
	return TRUE;
}
