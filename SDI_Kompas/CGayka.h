#pragma once
#include "afxdialogex.h"


// Диалоговое окно CGayka

class CSDIKompasDoc;
class CGayka : public CDialog
{
	DECLARE_DYNAMIC(CGayka)

public:
	CGayka(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CGayka();
	CSDIKompasDoc* mpDoc;
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGGayka };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double d;
	double D;
	double L;
	double M;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	double hagrezb;
};
