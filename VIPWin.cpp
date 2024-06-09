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
	DDX_Control(pDX, IDC_BUTTON3, Button_Del);
	DDX_Text(pDX, IDC_EDIT1, addnamestr);
	DDX_Text(pDX, IDC_EDIT2, addmarkstr);
}


BEGIN_MESSAGE_MAP(VIPWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &VIPWin::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &VIPWin::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON2, &VIPWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &VIPWin::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// VIPWin 消息处理程序


BOOL VIPWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//IDC_LIST1(List Control)

	VIP_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	VIP_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	VIP_list.InsertColumn(1, _T("会员号"), LVCFMT_CENTER, 120);
	VIP_list.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 120);
	VIP_list.InsertColumn(3, _T("积分"), LVCFMT_CENTER, 120);
	GetDlgItem(IDC_TIPS1)->SetWindowTextW(TEXT("姓名"));
	GetDlgItem(IDC_TIPS2)->SetWindowTextW(TEXT("积分"));
	for(int i=0;i<8;++i) VIP_list.InsertItem(i, _T(""));
	VIP_list.SetItemText(0, 0, _T("1")); VIP_list.SetItemText(0, 1, _T("张三")); VIP_list.SetItemText(0, 2, _T("100"));
	VIP_list.SetItemText(1, 0, _T("2")); VIP_list.SetItemText(1, 1, _T("李四")); VIP_list.SetItemText(1, 2, _T("600"));
	VIP_list.SetItemText(2, 0, _T("3")); VIP_list.SetItemText(2, 1, _T("王五")); VIP_list.SetItemText(2, 2, _T("500"));
	VIP_list.SetItemText(3, 0, _T("4")); VIP_list.SetItemText(3, 1, _T("陆六")); VIP_list.SetItemText(3, 2, _T("1000"));
	VIP_list.SetItemText(4, 0, _T("5")); VIP_list.SetItemText(4, 1, _T("钱七")); VIP_list.SetItemText(4, 2, _T("900"));
	VIP_list.SetItemText(5, 0, _T("6")); VIP_list.SetItemText(5, 1, _T("大强")); VIP_list.SetItemText(5, 2, _T("100"));
	VIP_list.SetItemText(6, 0, _T("7")); VIP_list.SetItemText(6, 1, _T("小丽")); VIP_list.SetItemText(6, 2, _T("100"));
	VIP_list.SetItemText(7, 0, _T("8")); VIP_list.SetItemText(7, 1, _T("敏敏")); VIP_list.SetItemText(7, 2, _T("100"));
	return TRUE; //正常处理时返回true
}


void VIPWin::OnBnClickedButton1()
{
	if (Mode == 0) {
		Mode = 1;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"确定添加");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"取消");
		ChoosedID = -1;
		Button_Del.EnableWindow(0);
	}else if (Mode == 1) {
		Mode = 0;
		UpdateData(true);
		if (addnamestr != "") {
			if (addmarkstr == "")
				addmarkstr = "0";
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
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加会员");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改会员");
		ChoosedID = -1;
		Button_Del.EnableWindow(1);
	}
	else if (Mode == 2) {
		UpdateData(true);
		VIP_list.SetItemText(ChoosedID, 1, addnamestr);
		VIP_list.SetItemText(ChoosedID, 2, addmarkstr);
		Mode = 0;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加会员");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改会员");
		Button_Del.EnableWindow(1);
		ChoosedID = -1;
	}
}


void VIPWin::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (Mode != 1) {
		int nIndex = -1;
		nIndex = VIP_list.GetNextItem(nIndex, LVNI_SELECTED);
		if (nIndex != -1) {
			addnamestr = VIP_list.GetItemText(nIndex, 1);
			addmarkstr = VIP_list.GetItemText(nIndex, 2);
			ChoosedID = nIndex;
			UpdateData(false);
		}
		*pResult = 0;
	}
}


void VIPWin::OnBnClickedButton2()
{
	if (Mode == 0) {
		int nIndex = -1;
		nIndex = VIP_list.GetNextItem(nIndex, LVNI_SELECTED);
		if (ChoosedID == -1) {
			addnamestr = "先用鼠标于列表中选择";
			addmarkstr = "";
			UpdateData(false);
			ChoosedID = -1;
		}
		else {
			Mode = 2;
			GetDlgItem(IDC_BUTTON1)->SetWindowText(L"确定修改");
			GetDlgItem(IDC_BUTTON2)->SetWindowText(L"取消");
			Button_Del.EnableWindow(0);
		}
	}
	else if (Mode == 1 || Mode == 2) {
		Mode = 0;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加会员");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改会员");
		Button_Del.EnableWindow(1);
		ChoosedID = -1;
	}
}


void VIPWin::OnBnClickedButton3()
{
	if (ChoosedID != -1) {
		VIP_list.DeleteItem(ChoosedID);
		ChoosedID = -1;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
	}
}


void VIPWin::OnClose()
{
	ShowWindow(SW_HIDE);
}
