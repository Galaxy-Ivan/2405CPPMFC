// ShopWin.cpp: 实现文件
//

#include "pch.h"
#include "P5.h"
#include "afxdialogex.h"
#include "ShopWin.h"
#include "LibraryWin.h"


// ShopWin 对话框

IMPLEMENT_DYNAMIC(ShopWin, CDialogEx)

ShopWin::ShopWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ShopWin, pParent)
{

}

ShopWin::~ShopWin()
{
}

void ShopWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST11, Shop_list);
	DDX_Text(pDX, IDC_EDIT12, addnamestr);
	DDX_Text(pDX, IDC_EDIT13, addmarkstr);
	DDX_Text(pDX, IDC_EDIT1, addtimesstr);
	DDX_Control(pDX, IDC_BUTTON2, Del_Button);
	DDX_Control(pDX, IDC_LIST14, Choose_list);
	DDX_Control(pDX, IDC_BUTTON3, PayMeByWeChat);
}


BEGIN_MESSAGE_MAP(ShopWin, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST11, &ShopWin::OnNMClickList11)
	ON_BN_CLICKED(IDC_BUTTON1, &ShopWin::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST14, &ShopWin::OnNMClickList14)
	ON_BN_CLICKED(IDC_BUTTON2, &ShopWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ShopWin::OnBnClickedButton3)
END_MESSAGE_MAP()


// ShopWin 消息处理程序

void ShopWin::TotalSumTextUpdate() {
	CString Str = L"";
	int num = Choose_list.GetItemCount();
	if (num == 0) {
		Str = L"欢迎光临";
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	}
	else {
		Str = "已选 ";
		for (int i = num; i; i /= 10)
			Str += char(i % 10 + 48);
		CString S1 = L"";
		Str += " 种 共 ";
		int books = 0, moneys = 0;
		for (int i = 0; i < num; ++i) {
			int abook = 0;
			for (int j = 0; j < Choose_list.GetItemText(i, 3).GetLength(); ++j) {
				abook *= 10;
				abook += Choose_list.GetItemText(i, 3)[j] - 48;
			}
			books += abook;
			int amoney = 0;
			for (int j = 0; j < Choose_list.GetItemText(i, 2).GetLength(); ++j) {
				amoney *= 10;
				amoney += Choose_list.GetItemText(i, 2)[j] - 48;
			}
			moneys += amoney * abook;
		}
		for (int i = books; i; i /= 10)
			S1 += char(i % 10 + 48);
		for (int i = S1.GetLength() - 1; ~i; --i)
			Str += S1[i];
		Str += " 本书 合计 ";
		S1 = L"";
		for (int i = moneys; i; i /= 10)
			S1 += char(i % 10 + 48);
		for (int i = S1.GetLength() - 1; ~i; --i)
			Str += S1[i];
		Str += " 米";
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	}
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(Str);
}
BOOL ShopWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HWND hWnd = ::FindWindow(NULL, _T("书籍管理"));
	LibraryWin* pWnd = (LibraryWin*)LibraryWin::FromHandle(hWnd);
	CListCtrl* LibCtrl = (CListCtrl*)pWnd->GetDlgItem(IDC_LIST1);
	Shop_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	Shop_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Choose_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	Choose_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Shop_list.InsertColumn(1, _T("图书号"), LVCFMT_CENTER, 120);
	Shop_list.InsertColumn(2, _T("图书名"), LVCFMT_CENTER, 200);
	Shop_list.InsertColumn(3, _T("图书价格"), LVCFMT_CENTER, 120);
	Choose_list.InsertColumn(1, _T("图书号"), LVCFMT_CENTER, 60);
	Choose_list.InsertColumn(2, _T("图书名"), LVCFMT_CENTER, 200);
	Choose_list.InsertColumn(3, _T("图书价格"), LVCFMT_CENTER, 120);
	Choose_list.InsertColumn(4, _T("购买数目"), LVCFMT_CENTER, 120);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(TEXT("欢迎光临"));
	for (int i = 0; i < LibCtrl->GetItemCount(); ++i) {
		Shop_list.InsertItem(i, _T(""));
		Shop_list.SetItemText(i, 0, LibCtrl->GetItemText(i, 0));
		Shop_list.SetItemText(i, 1, LibCtrl->GetItemText(i, 1));
		Shop_list.SetItemText(i, 2, LibCtrl->GetItemText(i, 2));
	}
	return TRUE;
}

void ShopWin::OnNMClickList11(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = -1;
	nIndex = Shop_list.GetNextItem(nIndex, LVNI_SELECTED);
	if (nIndex != -1) {
		addnamestr = Shop_list.GetItemText(nIndex, 1);
		addmarkstr = Shop_list.GetItemText(nIndex, 2);
		addtimesstr = "1";
		ChoosedID = nIndex;
		ChoosePlace = 1;
		Del_Button.EnableWindow(0);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加");
		UpdateData(false);
	}
	*pResult = 0;
}


void ShopWin::OnBnClickedButton1()
{
	if (ChoosePlace == 1) {
		UpdateData(true);
		int times = 0;
		if (addtimesstr.GetLength() == 0) {
			times = 0;
		}
		else {
			for (int i = 0; i < addtimesstr.GetLength(); ++i) {
				times *= 10;
				times += addtimesstr[i] - 48;
			}
		}
		if (times == 0) {
			addtimesstr = "";
			addnamestr = "请填写购买数目";
			addmarkstr = "";
		}
		else {
			int L = Choose_list.GetItemCount();
			Choose_list.InsertItem(L, _T(""));
			Choose_list.SetItemText(L, 0, Shop_list.GetItemText(ChoosedID, 0));
			Choose_list.SetItemText(L, 1, addnamestr); addnamestr = "";
			Choose_list.SetItemText(L, 2, addmarkstr); addmarkstr = "";
			Choose_list.SetItemText(L, 3, addtimesstr); addtimesstr = "";
			Shop_list.DeleteItem(ChoosedID);
		}
		UpdateData(false);
	}
	else if (ChoosePlace == 2) {
		UpdateData(true);
		int times = 0;
		if (addtimesstr.GetLength() == 0) {
			times = 0;
		}
		else {
			for (int i = 0; i < addtimesstr.GetLength(); ++i) {
				times *= 10;
				times += addtimesstr[i] - 48;
			}
		}
		if (times == 0) {
			addtimesstr = "";
			addnamestr = "请保留购买数目";
			addmarkstr = "";
		}
		else {
			Choose_list.SetItemText(ChoosedID, 1, addnamestr); addnamestr = "";
			Choose_list.SetItemText(ChoosedID, 2, addmarkstr); addmarkstr = "";
			Choose_list.SetItemText(ChoosedID, 3, addtimesstr); addtimesstr = "";
		}
		UpdateData(false);
		Del_Button.EnableWindow(0);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加");
	}
	TotalSumTextUpdate();
}

void ShopWin::OnNMClickList14(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = -1;
	nIndex = Choose_list.GetNextItem(nIndex, LVNI_SELECTED);
	if (nIndex != -1) {
		addnamestr = Choose_list.GetItemText(nIndex, 1);
		addmarkstr = Choose_list.GetItemText(nIndex, 2);
		addtimesstr = Choose_list.GetItemText(nIndex, 3);
		ChoosedID = nIndex;
		ChoosePlace = 2;
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"修改");
		Del_Button.EnableWindow(1);
		UpdateData(false);
	}
}
void ShopWin::OnBnClickedButton2()
{
	if (ChoosePlace == 2) {
		int Insbooktitle = 0;
		CString strs = Choose_list.GetItemText(ChoosedID, 0);
		for (int i = 0; i < strs.GetLength(); ++i) {
			Insbooktitle *= 10;
			Insbooktitle += strs[i] - 48;
		}
		int L = Shop_list.GetItemCount();
		for (; ~L; --L) {
			int Tempbooktitle = 0;
			strs = Shop_list.GetItemText(L - 1, 0);
			for (int i = 0; i < strs.GetLength(); ++i) {
				Tempbooktitle *= 10;
				Tempbooktitle += strs[i] - 48;
			}
			if (Tempbooktitle < Insbooktitle)
				break;
		}
		Shop_list.InsertItem(L, _T(""));
		Shop_list.SetItemText(L, 0, Choose_list.GetItemText(ChoosedID, 0));
		Shop_list.SetItemText(L, 1, addnamestr); addnamestr = "";
		Shop_list.SetItemText(L, 2, addmarkstr); addmarkstr = "";
		addtimesstr = "";
		Choose_list.DeleteItem(ChoosedID);
		UpdateData(false);
		Del_Button.EnableWindow(0);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"添加");
	}
	TotalSumTextUpdate();
}

void ShopWin::OnBnClickedButton3()
{
	system("start https://www.luogu.com.cn/paste/bwvmlbs5");
}
