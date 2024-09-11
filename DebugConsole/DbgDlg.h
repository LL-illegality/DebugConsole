#pragma once
#include "afxdialogex.h"
#include <chrono>
#include <iomanip>
#include <sstream>

// DbgDlg 对话框

class DbgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DbgDlg)

public:
	DbgDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DbgDlg();
	void dlgPrint(LPCTSTR s);
	void onCmdInput(LPCTSTR s);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DBG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedSendCommand();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
public:
	CEdit logEdit;
	CButton sendButton;
	CEdit cmdEdit;
	cmdParseFunction cmdParse = nullptr;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
