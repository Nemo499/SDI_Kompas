
// SDI_Kompas.h: основной файл заголовка для приложения SDI_Kompas
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSDIKompasApp:
// Сведения о реализации этого класса: SDI_Kompas.cpp
//

class CSDIKompasApp : public CWinApp
{
public:
	CSDIKompasApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDIKompasApp theApp;
