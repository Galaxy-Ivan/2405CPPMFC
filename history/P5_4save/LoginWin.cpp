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
	DDX_Text(pDX, IDC_EDIT1, UserNamestr);
	DDX_Text(pDX, IDC_EDIT2, Passwordstr);
	//DDX_Text(pDX, IDC_EDIT3, "账户：");
	CString Text = L"账户：";
	DDX_Text(pDX, IDC_EDIT4, Text);
	Text = L"密码：";
	DDX_Text(pDX, IDC_EDIT3, Text);
}


BEGIN_MESSAGE_MAP(LoginWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginWin::OnBnClickedButton2)
END_MESSAGE_MAP()


// LoginWin 消息处理程序

void LoginWin::OnBnClickedButton1()
{
	UpdateData(true);
	if (UserNamestr == "admin") {
		if (Passwordstr == "123456") {
			Logined = true;
			UserNamestr = "";
			UpdateData(false);
			CDialog::EndDialog(0);
		}
		UserNamestr = "密码错误";
		Passwordstr = "";
	}
	else UserNamestr = "账户错误";
	UpdateData(false);
	
	// TODO: 在此添加控件通知处理程序代码
}


void LoginWin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::EndDialog(0);
}


BOOL LoginWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
