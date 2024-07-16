
// SDI_KompasDoc.h: интерфейс класса CSDIKompasDoc 
//

#include <string>
using namespace std;
#pragma once
class CMyTreeView;
class CSDIKompasView;

class CSDIKompasDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIKompasDoc() noexcept;
	DECLARE_DYNCREATE(CSDIKompasDoc)

// Атрибуты
public:
	CSDIKompasView* pView;
	CMyTreeView* pTree;
	bool m_bSalnikFlan, m_bSalnik, m_bProcl, m_bGayka;
	double ddSalnik, dd1salnik, dd2salnik, dMsalnik, dDsalnik, dD1salnik, dD2salnik, dlsalnik;
	double ddgayka, dmgayka, dDgayka, dlgayka, hag_rezb_gayka, hag_rezb_saln;
	double ddprocl, dDprocl, dsprocl;
	string mat;
	double plot;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDIKompasDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
