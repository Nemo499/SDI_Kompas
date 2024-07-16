#pragma once
#include "afxdialogex.h"


// Диалоговое окно CSalnik
class CSDIKompasDoc;
class CSalnik : public CDialog
{
	DECLARE_DYNAMIC(CSalnik)

public:
	CSalnik(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CSalnik();
	CSDIKompasDoc* mpDoc;
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSalnik };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double d;
	double d1;
	double d2;
	double D;
	double D1;
	double D2;
	double M;
	double L;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	double hagrezb;
};
