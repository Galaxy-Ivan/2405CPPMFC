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
	DDX_Control(pDX, IDC_LIST1, Book_list);
	DDX_Control(pDX, IDC_BUTTON3, Button_Del);
	DDX_Text(pDX, IDC_EDIT1, addnamestr);
	DDX_Text(pDX, IDC_EDIT2, addmarkstr);
}


BEGIN_MESSAGE_MAP(LibraryWin, CDialogEx) //看不懂，也不知道是什么东西，一堆宏
	ON_BN_CLICKED(IDC_BUTTON1, &LibraryWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LibraryWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &LibraryWin::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &LibraryWin::OnNMClickList1)
END_MESSAGE_MAP()


// LibraryWin 消息处理程序


BOOL LibraryWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Book_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	Book_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Book_list.InsertColumn(1, _T("图书号"), LVCFMT_CENTER, 120);
	Book_list.InsertColumn(2, _T("图书名"), LVCFMT_CENTER, 200);
	Book_list.InsertColumn(3, _T("图书价格"), LVCFMT_CENTER, 120);
	GetDlgItem(IDC_TIPS1)->SetWindowTextW(TEXT("书名"));
	GetDlgItem(IDC_TIPS2)->SetWindowTextW(TEXT("价格"));
	for (int i = 0; i < 8; ++i) Book_list.InsertItem(i, _T(""));
	Book_list.SetItemText(0, 0, _T("1")); Book_list.SetItemText(0, 1, _T("C#2.0宝典")); Book_list.SetItemText(0, 2, _T("88"));
	Book_list.SetItemText(1, 0, _T("2")); Book_list.SetItemText(1, 1, _T("Java编程基础")); Book_list.SetItemText(1, 2, _T("55"));
	Book_list.SetItemText(2, 0, _T("3")); Book_list.SetItemText(2, 1, _T("J2SE桌面应用程序开发")); Book_list.SetItemText(2, 2, _T("60"));
	Book_list.SetItemText(3, 0, _T("4")); Book_list.SetItemText(3, 1, _T("数据库设计和应用")); Book_list.SetItemText(3, 2, _T("45"));
	Book_list.SetItemText(4, 0, _T("5")); Book_list.SetItemText(4, 1, _T("水浒伟")); Book_list.SetItemText(4, 2, _T("55"));
	Book_list.SetItemText(5, 0, _T("6")); Book_list.SetItemText(5, 1, _T("红楼梦")); Book_list.SetItemText(5, 2, _T("68"));
	Book_list.SetItemText(6, 0, _T("7")); Book_list.SetItemText(6, 1, _T("三国演义")); Book_list.SetItemText(6, 2, _T("78"));
	Book_list.SetItemText(7, 0, _T("8")); Book_list.SetItemText(7, 1, _T("地心游记")); Book_list.SetItemText(7, 2, _T("29"));
	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}


void LibraryWin::OnBnClickedButton1()
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
	}
	else if (Mode == 1) {
		Mode = 0;
		UpdateData(true);
		if (addnamestr != "") {
			if (addmarkstr == "")
				addmarkstr = "0";
			int list_row = Book_list.GetItemCount();
			Book_list.InsertItem(list_row, _T(""));
			CString strnum, strnum1; int Lens = 0;
			for (int i = list_row + 1; i; i /= 10, Lens++)
				strnum1 += char(i % 10 + 48);
			for (int i = 0; i < Lens; ++i) {
				strnum += strnum1[Lens - i - 1];
			}
			Book_list.SetItemText(list_row, 0, strnum);
			Book_list.SetItemText(list_row, 1, addnamestr);
			Book_list.SetItemText(list_row, 2, addmarkstr);
		}
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加书目");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改书目");
		ChoosedID = -1;
		Button_Del.EnableWindow(1);
	}
	else if (Mode == 2) {
		UpdateData(true);
		Book_list.SetItemText(ChoosedID, 1, addnamestr);
		Book_list.SetItemText(ChoosedID, 2, addmarkstr);
		Mode = 0;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加书目");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改书目");
		Button_Del.EnableWindow(1);
		ChoosedID = -1;
	}
}


void LibraryWin::OnBnClickedButton2()
{
	if (Mode == 0) {
		int nIndex = -1;
		nIndex = Book_list.GetNextItem(nIndex, LVNI_SELECTED);
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
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加书目");
		GetDlgItem(IDC_BUTTON2)->SetWindowText(L"修改书目");
		Button_Del.EnableWindow(1);
		ChoosedID = -1;
	}
}


void LibraryWin::OnBnClickedButton3()
{
	if (ChoosedID != -1) {
		Book_list.DeleteItem(ChoosedID);
		ChoosedID = -1;
		addnamestr = "";
		addmarkstr = "";
		UpdateData(false);
	}
}


void LibraryWin::OnClose()
{
	ShowWindow(SW_HIDE);
}


void LibraryWin::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (Mode != 1) {
		int nIndex = -1;
		nIndex = Book_list.GetNextItem(nIndex, LVNI_SELECTED);
		if (nIndex != -1) {
			addnamestr = Book_list.GetItemText(nIndex, 1);
			addmarkstr = Book_list.GetItemText(nIndex, 2);
			ChoosedID = nIndex;
			UpdateData(false);
		}
		*pResult = 0;
	}
}
