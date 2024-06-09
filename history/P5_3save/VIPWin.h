#pragma once
#include "afxdialogex.h"


// VIPWin 对话框

class VIPWin : public CDialogEx
{
	DECLARE_DYNAMIC(VIPWin)

public:
	VIPWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VIPWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIPWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl VIP_list;
	afx_msg void OnBnClickedButton1();
private:
	CString addnamestr, addmarkstr;
	int Mode = 0;//查看=0，添加=1，修改=2
};
