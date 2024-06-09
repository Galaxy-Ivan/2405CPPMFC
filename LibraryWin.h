#pragma once
#include "afxdialogex.h"


// LibraryWin 对话框

class LibraryWin : public CDialogEx
{
	DECLARE_DYNAMIC(LibraryWin)

public:
	LibraryWin(CWnd* pParent = nullptr);
	virtual ~LibraryWin();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Library };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString addnamestr, addmarkstr;//别看了，从上一个窗体直接复制过来的，就问你能不能跑嘛
	int Mode = 0;//查看=0，添加=1，修改=2
	int ChoosedID = -1;
public:
	CListCtrl Book_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();
	CButton Button_Del;
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
