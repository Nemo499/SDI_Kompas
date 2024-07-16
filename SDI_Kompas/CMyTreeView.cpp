// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Kompas.h"
#include "CMyTreeView.h"
#include "SDI_KompasDoc.h"
#include "SDI_KompasView.h"
#include "CGayka.h"
#include "CPostroen.h"
#include "CSalnik.h"
#include "CProcl.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hSalnikFlan = tree.InsertItem(L"Сальник фланцевый", -1, -1, NULL, TVI_FIRST);
	m_hSalnik = tree.InsertItem(L"Сальник", -1, -1, m_hSalnikFlan, TVI_FIRST);
	m_hGayka = tree.InsertItem(L"Гайка", -1, -1, m_hSalnikFlan, TVI_FIRST);
	m_hProcl = tree.InsertItem(L"Прокладка", -1, -1, m_hSalnikFlan, TVI_FIRST);
	tree.Expand(m_hSalnikFlan, TVE_EXPAND);
}

void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;
	CProcl pr;
	CGayka ga;
	CSalnik sal;
	CPostroen cr;
	tree.GetItemRect(m_hSalnikFlan, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hSalnikFlan);
	}

	tree.GetItemRect(m_hSalnik, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hSalnik);
	}

	tree.GetItemRect(m_hProcl, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hProcl);
	}

	tree.GetItemRect(m_hGayka, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hGayka);
	}
	if (tree.GetSelectedItem() == m_hSalnikFlan)
	{
		m_pDoc->m_bSalnikFlan = true;
		m_pDoc->m_bSalnik = false;
		m_pDoc->m_bProcl = false;
		m_pDoc->m_bGayka = false;
		m_pDoc->pView->Invalidate(1);
		cr.mpDoc = m_pDoc;
		cr.DoModal();
	}
	if(tree.GetSelectedItem() == m_hSalnik)
	{
		m_pDoc->m_bSalnikFlan = false;
		m_pDoc->m_bSalnik = true;
		m_pDoc->m_bProcl = false;
		m_pDoc->m_bGayka = false;
		m_pDoc->pView->Invalidate(1);
		sal.mpDoc = m_pDoc;
		sal.DoModal();
	}
	if(tree.GetSelectedItem() == m_hProcl)
	{
		m_pDoc->m_bSalnikFlan = false;
		m_pDoc->m_bSalnik = false;
		m_pDoc->m_bProcl = true;
		m_pDoc->m_bGayka = false;
		m_pDoc->pView->Invalidate(1);
		pr.mpDoc = m_pDoc;
		pr.DoModal();
	}
	if (tree.GetSelectedItem() == m_hGayka)
	{
		m_pDoc->m_bSalnikFlan = false;
		m_pDoc->m_bSalnik = false;
		m_pDoc->m_bProcl = false;
		m_pDoc->m_bGayka = true;
		m_pDoc->pView->Invalidate(1);
		ga.mpDoc = m_pDoc;
		ga.DoModal();
	}
}
