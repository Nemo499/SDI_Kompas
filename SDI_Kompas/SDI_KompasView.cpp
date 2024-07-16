
// SDI_KompasView.cpp: реализация класса CSDIKompasView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI_Kompas.h"
#endif

#include "SDI_KompasDoc.h"
#include "SDI_KompasView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIKompasView

IMPLEMENT_DYNCREATE(CSDIKompasView, CView)

BEGIN_MESSAGE_MAP(CSDIKompasView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Создание или уничтожение CSDIKompasView

CSDIKompasView::CSDIKompasView() noexcept
{
	// TODO: добавьте код создания

}

CSDIKompasView::~CSDIKompasView()
{
}

BOOL CSDIKompasView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSDIKompasView

void CSDIKompasView::OnDraw(CDC* pDC)
{
	CSDIKompasDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	int w = rc.right;
	int h = rc.bottom;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CDC dcTemp;
	CBitmap cb;
	CBitmap *oldbit;
	if (pDoc->m_bGayka)
	{
		cb.LoadBitmap(IDB_BITMAP1);
		dcTemp.CreateCompatibleDC(pDC);
		dcTemp.SelectObject(cb);

		pDC->BitBlt(0, 0, w, h, &dcTemp, 0, 0, SRCCOPY);
	}
	if (pDoc->m_bProcl)
	{
		cb.LoadBitmap(IDB_BITMAP3);
		dcTemp.CreateCompatibleDC(pDC);
		dcTemp.SelectObject(cb);

		pDC->BitBlt(0, 0, w, h, &dcTemp, 0, 0, SRCCOPY);
	}
	if (pDoc->m_bSalnik)
	{
		cb.LoadBitmap(IDB_BITMAP4);
		dcTemp.CreateCompatibleDC(pDC);
		dcTemp.SelectObject(cb);

		pDC->BitBlt(0, 0, w, h, &dcTemp, 0, 0, SRCCOPY);
	}
	if (pDoc->m_bSalnikFlan)
	{
		cb.LoadBitmap(IDB_BITMAP2);
		dcTemp.CreateCompatibleDC(pDC);
		dcTemp.SelectObject(cb);

		pDC->BitBlt(0, 0, w, h, &dcTemp, 0, 0, SRCCOPY);
	}
}


// Печать CSDIKompasView

BOOL CSDIKompasView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSDIKompasView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDIKompasView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CSDIKompasView

#ifdef _DEBUG
void CSDIKompasView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIKompasView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIKompasDoc* CSDIKompasView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIKompasDoc)));
	return (CSDIKompasDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSDIKompasView
