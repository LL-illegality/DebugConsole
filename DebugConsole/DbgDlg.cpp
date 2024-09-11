// DbgDlg.cpp: 实现文件
//

#include "pch.h"
#include "DebugConsole.h"
#include "afxdialogex.h"
#include "DbgDlg.h"
#include <string>
#include <codecvt>
#include <locale>


// DbgDlg 对话框

IMPLEMENT_DYNAMIC(DbgDlg, CDialogEx)

DbgDlg::DbgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DBG, pParent)
{

}

DbgDlg::~DbgDlg()
{
}

void DbgDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, logEdit);
    DDX_Control(pDX, IDOK, sendButton);
    DDX_Control(pDX, IDC_EDIT2, cmdEdit);
}

void DbgDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
    if (nChar == VK_RETURN)
    {
        CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
        OnBnClickedSendCommand();
    }
}

void DbgDlg::onCmdInput(LPCTSTR s)
{
    std::wstring ws = s;
    dlgPrint((L"Command: " + ws).c_str());
    if (ws == L"clear")
    {
        logEdit.SetWindowTextW(L"");
    }
    else if (ws == L"help")
    {
        dlgPrint(L"Commands: \r\n\tclear: clear the current screen;\r\n\thelp: show this list;\r\n\texit: exit the whole program");
    }
    else if (ws == L"exit")
    {
        dlgPrint(L"Exiting...");
        ::PostQuitMessage(0);
    }
    else
    {
        if (cmdParse != nullptr)
        {
            cmdParse(s);
        }
        else
        {
            dlgPrint(L"Unknown command");
        }
    }
}

void DbgDlg::dlgPrint(LPCTSTR s)
{
    std::wstring currStr;
    HWND hWnd = GetDlgItem(IDC_EDIT1)->m_hWnd;
    int len = ::GetWindowTextLengthW(hWnd);
    if (len > 0) {
        currStr.resize(len);
        ::GetWindowTextW(hWnd, &currStr[0], len + 1);
    }
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now;
    localtime_s(&tm_now, &time_t_now);
    auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::wstringstream wss;
    wss << std::put_time(&tm_now, L"%H:%M:%S");
    wss << L":" << std::setw(3) << std::setfill(L'0') << duration_in_ms.count();
    std::wstring currTime = wss.str();
    if (currStr != L"")
    {
        currStr.append(L"\r\n");
    }
    std::wstring newStr = currStr + L'[' + currTime + L"] " + s;
    ::SetWindowTextW(hWnd, newStr.c_str());
    logEdit.LineScroll(logEdit.GetLineCount());
}

void DbgDlg::OnBnClickedSendCommand()
{
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    GetDlgItemText(IDC_EDIT2, str);
    if (str != L"")
    {
        onCmdInput(str);
        GetDlgItem(IDC_EDIT2)->SetWindowTextW(L"");
    }
    if (str == L"et")
    {
        dlgPrint(L"et");
        ::SendMessageW(::GetForegroundWindow(), WM_HOTKEY, VK_RETURN, NULL);
    }
}


BEGIN_MESSAGE_MAP(DbgDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &DbgDlg::OnBnClickedSendCommand)
    ON_WM_KEYDOWN()
    ON_WM_HOTKEY()
END_MESSAGE_MAP()


// DbgDlg 消息处理程序


BOOL DbgDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        OnBnClickedSendCommand();
        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL DbgDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    RegisterHotKey(this->m_hWnd, 1, MOD_CONTROL | MOD_ALT, VK_RETURN);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void DbgDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nHotKeyId)
    {
    case 1:
        OnBnClickedSendCommand();
    }

    CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
