// CSalnik.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Kompas.h"
#include "afxdialogex.h"
#include "CSalnik.h"
#include "SDI_KompasDoc.h"


// Диалоговое окно CSalnik

IMPLEMENT_DYNAMIC(CSalnik, CDialog)

CSalnik::CSalnik(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOGSalnik, pParent)
	, d(8)
	, d1(4.5)
	, d2(8)
	, D(20)
	, D1(34)
	, D2(46)
	, M(16)
	, L(18)
	, hagrezb(1)
{

}

CSalnik::~CSalnik()
{
}

void CSalnik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, d);
	DDX_Text(pDX, IDC_EDIT1, d1);
	DDX_Text(pDX, IDC_EDIT2, d2);
	DDX_Text(pDX, IDC_EDIT3, D);
	DDX_Text(pDX, IDC_EDIT4, D1);
	DDX_Text(pDX, IDC_EDIT5, D2);
	DDX_Text(pDX, IDC_EDIT6, M);
	DDX_Text(pDX, IDC_EDIT7, L);
	DDX_Text(pDX, IDC_EDIT8, hagrezb);
}


BEGIN_MESSAGE_MAP(CSalnik, CDialog)
	ON_BN_CLICKED(IDOK, &CSalnik::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CSalnik




BOOL CSalnik::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	d = 8;
	d1 = 4.5;
	d2 = 8;
	D = 20;
	D1 = 34;
	D2 = 46;
	M = 16;
	L = 18;
	hagrezb = 1;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CSalnik::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	mpDoc->ddSalnik = d;
	mpDoc->dd1salnik = d1;
	mpDoc->dd2salnik = d2;
	mpDoc->dDsalnik = D;
	mpDoc->dD2salnik = D2;
	mpDoc->dMsalnik = M;
	mpDoc->dlsalnik = L;
	mpDoc->dD1salnik = D1;
	mpDoc->hag_rezb_saln = hagrezb;
	CDialog::OnOK();
;}
