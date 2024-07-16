
// SDI_KompasView.h: интерфейс класса CSDIKompasView
//

#pragma once
#include "SDI_KompasDoc.h"

class CSDIKompasView : public CView
{
protected: // создать только из сериализации
	CSDIKompasView() noexcept;
	DECLARE_DYNCREATE(CSDIKompasView)

// Атрибуты
public:
	CSDIKompasDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CSDIKompasView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в SDI_KompasView.cpp
inline CSDIKompasDoc* CSDIKompasView::GetDocument() const
   { return reinterpret_cast<CSDIKompasDoc*>(m_pDocument); }
#endif

