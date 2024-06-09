// LibraryWin.cpp: 实现文件
//

#include "pch.h"
#include "P5.h"
#include "afxdialogex.h"
#include "LibraryWin.h"


// LibraryWin 对话框

IMPLEMENT_DYNAMIC(LibraryWin, CDialogEx)

LibraryWin::LibraryWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Library, pParent)
{

}

LibraryWin::~LibraryWin()
{
}

void LibraryWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LibraryWin, CDialogEx)
END_MESSAGE_MAP()


// LibraryWin 消息处理程序
