// CGayka.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Kompas.h"
#include "afxdialogex.h"
#include "SDI_KompasDoc.h"
#include "CGayka.h"
#include <string>
using namespace std;


// Диалоговое окно CGayka

IMPLEMENT_DYNAMIC(CGayka, CDialog)

CGayka::CGayka(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOGGayka, pParent)
	, d(10)
	, D(21.9)
	, L(17)
	, M(16)
	, hagrezb(1)
{

}

CGayka::~CGayka()
{
}

void CGayka::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT10, d);
	DDX_Text(pDX, IDC_EDIT11, D);
	DDX_Text(pDX, IDC_EDIT13, L);
	DDX_Text(pDX, IDC_EDIT17, M);
	DDX_Text(pDX, IDC_EDIT1, hagrezb);
}


BEGIN_MESSAGE_MAP(CGayka, CDialog)
	
	ON_BN_CLICKED(IDOK, &CGayka::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CGayka





BOOL CGayka::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	d = 10;
	D = 21.9;
	L = 17;
	M = 16;
	hagrezb = 1;
	UpdateData(false);

	CWnd* pWnd = GetDlgItem(IDC_COMBO_VALUE);

	int num = ((CComboBox*)pWnd)->AddString(L"Сталь");
	((CComboBox*)pWnd)->SetItemData(num, 1);

	num = ((CComboBox*)pWnd)->AddString(L"Резина");
	((CComboBox*)pWnd)->SetItemData(num, 2);


	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CGayka::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	CWnd* pWnd = GetDlgItem(IDC_COMBO_VALUE);
	int selection = ((CComboBox*)pWnd)->GetCurSel();
	int res = ((CComboBox*)pWnd)->GetItemData(selection);
	string mt;
	double plot = 7.85;
	if(res==2) 
	{
		mt = "Резина";
		plot = 1.05;
	}
	else if(res==1)
	{
		mt = "Сталь";
		plot = 7.85;
	}
	if(mt==""&&(res!=1||res!=2))
	{
		MessageBox(L"Не выбран материал!");
	}
	else
	{
		mpDoc->ddgayka = d;
		mpDoc->dDgayka = D;
		mpDoc->dlgayka = L;
		mpDoc->dmgayka = M;
		mpDoc->mat = mt;
		mpDoc->plot = plot;
		mpDoc->hag_rezb_gayka = hagrezb;
		CDialog::OnOK();
	}
}
