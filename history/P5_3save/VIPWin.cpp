// VIPWin.cpp: 实现文件
//

#include "pch.h"
#include "P5.h"
#include "afxdialogex.h"
#include "VIPWin.h"


// VIPWin 对话框

IMPLEMENT_DYNAMIC(VIPWin, CDialogEx)

VIPWin::VIPWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIPWin, pParent)
{

}

VIPWin::~VIPWin()
{
}

void VIPWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, VIP_list);
	DDX_Text(pDX, IDC_EDIT1, addnamestr);
	DDX_Text(pDX, IDC_EDIT2, addmarkstr);
}


BEGIN_MESSAGE_MAP(VIPWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &VIPWin::OnBnClickedButton1)
END_MESSAGE_MAP()


// VIPWin 消息处理程序


BOOL VIPWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	
	// TODO:  在此添加额外的初始化
	//IDC_LIST1(List Control)
	
	VIP_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	VIP_list.InsertColumn(0, _T("会员号"), LVCFMT_CENTER, 120);
	VIP_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 120);
	VIP_list.InsertColumn(2, _T("积分"), LVCFMT_CENTER, 120);
	GetDlgItem(IDC_TIPS1)->SetWindowTextW(TEXT("姓名"));
	GetDlgItem(IDC_TIPS2)->SetWindowTextW(TEXT("积分"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void VIPWin::OnBnClickedButton1()
{
	if (Mode == 0) {
		Mode = 1;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(true);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"确定添加");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"取消");
	}else if (Mode == 1) {
		Mode = 0;
		// TODO: 在此添加控件通知处理程序代码
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加会员");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改");
		UpdateData(true);
		int list_row = VIP_list.GetItemCount();
		VIP_list.InsertItem(list_row, _T(""));
		CString strnum, strnum1; int Lens = 0;
		for (int i = list_row + 1; i; i /= 10, Lens++)
			strnum1 += char(i % 10 + 48);
		for (int i = 0; i < Lens; ++i) {
			strnum += strnum1[Lens - i - 1];
		}
		VIP_list.SetItemText(list_row, 0, strnum);
		VIP_list.SetItemText(list_row, 1, addnamestr);
		VIP_list.SetItemText(list_row, 2, addmarkstr);
	}
}