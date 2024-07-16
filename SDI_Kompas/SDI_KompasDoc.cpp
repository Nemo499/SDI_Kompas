
// SDI_KompasDoc.cpp: реализация класса CSDIKompasDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI_Kompas.h"
#endif

#include "SDI_KompasDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CMyTreeView.h"
#include <string>

// CSDIKompasDoc

IMPLEMENT_DYNCREATE(CSDIKompasDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIKompasDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CSDIKompasDoc

CSDIKompasDoc::CSDIKompasDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSDIKompasDoc::~CSDIKompasDoc()
{
}

BOOL CSDIKompasDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	m_bSalnikFlan = m_bSalnik = m_bProcl = m_bGayka = false;
	ddSalnik = dd1salnik = dd2salnik = dMsalnik = dDsalnik = dD1salnik = dD2salnik = dlsalnik = hag_rezb_gayka = hag_rezb_saln = 0;
	ddprocl = dDprocl = dsprocl = 0;
	pTree->FillTree();
	return TRUE;
}




// Сериализация CSDIKompasDoc

void CSDIKompasDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDIKompasDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSDIKompasDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDIKompasDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSDIKompasDoc

#ifdef _DEBUG
void CSDIKompasDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIKompasDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSDIKompasDoc
