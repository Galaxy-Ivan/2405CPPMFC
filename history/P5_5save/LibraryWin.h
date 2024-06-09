#pragma once
#include "afxdialogex.h"


// LibraryWin 对话框

class LibraryWin : public CDialogEx
{
	DECLARE_DYNAMIC(LibraryWin)

public:
	LibraryWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LibraryWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Library };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
