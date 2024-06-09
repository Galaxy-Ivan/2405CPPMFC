
// P5Dlg.h: 头文件
//

#pragma once
#include "LoginWin.h"
#include "VIPWin.h"
#include "LibraryWin.h"
#include "ShopWin.h"


// 主对话框
class CP5Dlg : public CDialogEx
{
public:
	CP5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_P5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	LoginWin LoginWin1;
	VIPWin VIPWin1;
	LibraryWin LibWin1;
	ShopWin ShopWin1;
public:
	afx_msg void OnBnClickedButton1();
	CString str1;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
