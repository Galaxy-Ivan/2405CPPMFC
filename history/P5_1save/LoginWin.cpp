// LoginWin.cpp: 实现文件
//

#include "pch.h"
#include "P5.h"
#include "afxdialogex.h"
#include "LoginWin.h"


// LoginWin 对话框

IMPLEMENT_DYNAMIC(LoginWin, CDialogEx)

LoginWin::LoginWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LoginWin, pParent)
{

}

LoginWin::~LoginWin()
{
}

void LoginWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginWin::OnBnClickedButton1)
END_MESSAGE_MAP()


// LoginWin 消息处理程序


void LoginWin::OnBnClickedButton1()
{
	Logined = !Logined;
	// TODO: 在此添加控件通知处理程序代码
}
