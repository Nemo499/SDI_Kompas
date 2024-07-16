// CProcl.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Kompas.h"
#include "afxdialogex.h"
#include "CProcl.h"
#include "SDI_KompasDoc.h"
#include "CPostroen.h"


// Диалоговое окно CProcl

IMPLEMENT_DYNAMIC(CProcl, CDialog)

CProcl::CProcl(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOGProcl, pParent)
	, d(5)
	, D(14)
	, s(1.5)
{

}

CProcl::~CProcl()
{
}

void CProcl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT14, d);
	DDX_Text(pDX, IDC_EDIT15, D);
	DDX_Text(pDX, IDC_EDIT16, s);
}


BEGIN_MESSAGE_MAP(CProcl, CDialog)
	ON_BN_CLICKED(IDOK, &CProcl::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CProcl





void CProcl::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	mpDoc->dDprocl = D;
	mpDoc->ddprocl = d;
	mpDoc->dsprocl = s;
	CDialog::OnOK();
}

BOOL CProcl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	d = 5;
	D = 14;
	s = 1.5;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
