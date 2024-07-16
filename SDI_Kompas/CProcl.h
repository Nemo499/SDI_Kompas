#pragma once
#include "afxdialogex.h"


// Диалоговое окно CProcl
class CSDIKompasDoc;

class CProcl : public CDialog
{
	DECLARE_DYNAMIC(CProcl)

public:
	CProcl(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CProcl();
	CSDIKompasDoc* mpDoc;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGProcl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double d;
	double D;
	double s;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
