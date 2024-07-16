#pragma once
#include "afxdialogex.h"


// Диалоговое окно CPostroen
class CSDIKompasDoc;

class CPostroen : public CDialog
{
	DECLARE_DYNAMIC(CPostroen)

public:
	CPostroen(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CPostroen();
	CSDIKompasDoc* mpDoc;
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	bool CheckData();
	double dSalnik, d1salnik, d2salnik, Msalnik, Dsalnik, D1salnik, D2salnik, B1salnik, lsalnik, hag_rezb_saln;
	double dgayka, Mgayka, Dgayka, sgayka, lgayka, hag_rezb_gayka;
	double dprocl, Dprocl, sprocl;
//	virtual BOOL OnInitDialog();
};
