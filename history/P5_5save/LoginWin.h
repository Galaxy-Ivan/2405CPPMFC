#pragma once
#include "afxdialogex.h"


// LoginWin 对话框

class LoginWin : public CDialogEx
{
	DECLARE_DYNAMIC(LoginWin)

public:
	LoginWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LoginWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	bool Logined = true;
	CString UserNamestr;
	CString Passwordstr;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
