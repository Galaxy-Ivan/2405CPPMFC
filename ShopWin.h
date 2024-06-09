#pragma once
#include "afxdialogex.h"


// ShopWin 对话框

class ShopWin : public CDialogEx
{
	DECLARE_DYNAMIC(ShopWin)

public:
	ShopWin(CWnd* pParent = nullptr);
	virtual ~ShopWin();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ShopWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void TotalSumTextUpdate();
	CListCtrl Shop_list;
	afx_msg void OnNMClickList11(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CString addnamestr, addmarkstr, addtimesstr;
	int ChoosedID = -1, ChoosePlace = -1;// ChoosePlace: -1->None 1->up 2->down
public:
	CButton Del_Button;
	afx_msg void OnBnClickedButton1();
	CListCtrl Choose_list;
	afx_msg void OnNMClickList14(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton2();
	CButton PayMeByWeChat;
	afx_msg void OnBnClickedButton3();
};
