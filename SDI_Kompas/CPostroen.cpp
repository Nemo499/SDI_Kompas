// CPostroen.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Kompas.h"
#include "afxdialogex.h"
#include "CPostroen.h"
#include "SDI_KompasDoc.h"
#include "D://Kompas 3D//SDK//Include//ksConstants.h"
#include "D://Kompas 3D//SDK//Include//ksConstants3D.h"
//#include "stdafx.h"
#include <atlsafe.h>
#include <comutil.h>
#include <cmath>

#import "D://Kompas 3D//SDK//lib//kAPI5.tlb"
using namespace Kompas6API5;
using namespace std;

KompasObjectPtr pKompasApp5;
ksPartPtr pPart;
ksDocument3DPtr pDoc;

struct kofpoint
{
	double xc;
	double yc;
};

kofpoint A_sul, B_sul, C_sul, D_sul, E_sul, F_sul;// коофиценты точек основания сальника
double Kshir_rezb_gayka = 17 / 12.8;
double Km_gayka = 16 / 3;
double Kd_pr_gayka = 16 / 0.5;
bool M_gayka_saln, D_gayka, d_gayka, M_gayka, l_gayka, M_saln, l_saln, D_saln, d_saln, d1_saln, d2_saln, D1_saln, D_procl, d_procl, s_procl, D_procl_saln, l_gayka_s_procl, hag_rezb_salnB, hag_rezb_gaykaB, hag_rezb_gayka_saln = false;
CString str;

// Диалоговое окно CPostroen


IMPLEMENT_DYNAMIC(CPostroen, CDialog)
CPostroen::CPostroen(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CPostroen::~CPostroen()
{
}

void CPostroen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPostroen, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPostroen::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CPostroen

bool CPostroen::CheckData()
{
	if (!UpdateData())
		return false;

	/*m_Dverh /=10;
	m_Dcentrotv /= 10;
	m_Dcentr /= 10;
	m_Dotv /= 10;
	m_Dosn /= 10;
	m_GlubinaPaza /= 10;
	m_ShirinaPaza /= 10;
	m_Lpaza /= 10;
	m_OtstupPaza /= 10;
	m_DVireza /= 10;
	m_GlubinaVireza /= 10;
	m_Lobsh /= 10;
	m_Losn /= 10;*/

	return true;
}

void CPostroen::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	BeginWaitCursor();
	sprocl = mpDoc->dsprocl;
	dprocl = mpDoc->ddprocl;
	Dprocl = mpDoc->dDprocl;
	dgayka = mpDoc->ddgayka;
	Mgayka = mpDoc->dmgayka;
	Dgayka = mpDoc->dDgayka;
	lgayka = mpDoc->dlgayka;
	dSalnik = mpDoc->ddSalnik;
	d1salnik = mpDoc->dd1salnik;
	d2salnik = mpDoc->dd2salnik;
	Msalnik = mpDoc->dMsalnik;
	Dsalnik = mpDoc->dDsalnik;
	D1salnik = mpDoc->dD1salnik;
	D2salnik = mpDoc->dD2salnik;
	lsalnik = mpDoc->dlsalnik;
	hag_rezb_gayka = mpDoc->hag_rezb_gayka;
	hag_rezb_saln = mpDoc->hag_rezb_saln;
	A_sul.xc = 46 / 2.38;
	A_sul.yc = 46 / 22.88;
	B_sul.xc = -46 / 2.38;
	B_sul.yc = 46 / 22.88;
	C_sul.xc = -46.f / 21;
	C_sul.yc = -46 / 9.38;
	D_sul.xc = -46 / 18.62;
	D_sul.yc = -46 / 13.5;
	E_sul.xc = 46 / 18.62;
	E_sul.yc = -46 / 13.5;
	F_sul.xc = 46.f / 21;
	F_sul.yc = -46 / 9.38;
	double Kfas = 16.f;
	double storfas;
	string mat = (mpDoc->mat);
	double plot = mpDoc->plot;
	if (abs(Msalnik - Mgayka) < 0.001)
	{
		M_gayka_saln = true;
	}
	if (Dgayka > dgayka && Dgayka > Mgayka && Dgayka > 0)
	{
		D_gayka = true;
	}
	if (dgayka > 0)
	{
		d_gayka = true;
	}
	if (lgayka > 3)
	{
		l_gayka = true;
	}
	if (Mgayka > 0)
	{
		M_gayka = true;
	}
	if (dprocl > 0 && dprocl < dSalnik)
	{
		d_procl = true;
	}
	if (Dprocl > dprocl && Dprocl > 0)
	{
		D_procl = true;
	}
	if (sprocl > 0)
	{
		s_procl = true;
	}
	if ((lgayka / Kshir_rezb_gayka + sprocl * 2 + 3) > lsalnik)
	{
		l_gayka_s_procl = true;
	}
	if (Msalnik > 0)
	{
		M_saln = true;
	}
	if (lsalnik > 3)
	{
		l_saln = true;
	}
	if (Dsalnik > Msalnik && Dsalnik > 0)
	{
		D_saln = true;
	}
	if (dSalnik > 0 && dSalnik < Msalnik)
	{
		d_saln = true;
	}
	if (d1salnik > 0)
	{
		d1_saln = true;
	}
	if (d2salnik > d1salnik && d2salnik > 0)
	{
		d2_saln = true;
	}
	if (D1salnik / 2 > Dsalnik / 2 + d2salnik / 2 && D1salnik > 0) 
	{
		D1_saln = true;
	}
	if (Dprocl < Msalnik && Dprocl>dSalnik)
	{
		D_procl_saln = true;
	}
	if (hag_rezb_saln > 0)
	{
		hag_rezb_salnB = true;
	}
	if (hag_rezb_gayka > 0)
	{
		hag_rezb_gaykaB = true;
	}
	if (abs(hag_rezb_gayka - hag_rezb_saln) < 0.001)
	{
		hag_rezb_gayka_saln = true;
	}

	if (hag_rezb_gayka_saln && hag_rezb_gaykaB && M_gayka_saln && D_gayka && d_gayka && M_gayka && l_gayka && M_saln && l_saln && D_saln && d_saln && d1_saln && d2_saln && D1_saln && D_procl && d_procl && s_procl && D_procl_saln && l_gayka_s_procl && hag_rezb_salnB)
	{
		if (!CheckData())
			return;

		CComPtr<IUnknown> pKompasAppUnk = nullptr;
		if (!pKompasApp5)
		{
			// Получаем CLSID для Компас
			CLSID InvAppClsid;
			HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}

			// Проверяем есть ли запущенный экземпляр Компас
			//если есть получаем IUnknown
			hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
			if (FAILED(hRes)) {
				// Приходится запускать Компас самим так как работающего нет
				// Также получаем IUnknown для только что запущенного приложения Компас
				TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
				hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
				if (FAILED(hRes)) {
					pKompasApp5 = nullptr;
					return;
				}
			}

			// Получаем интерфейс приложения Компас
			hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
			if (FAILED(hRes)) {
				return;
			}
		}
		storfas = Msalnik / Kfas;
		// делаем Компас видимым
		pKompasApp5->Visible = true;
		pDoc = pKompasApp5->Document3D(); //Получаем интерфейс документа-модели
		pDoc->Create(false, true); //Создаем документ-модель
		pPart = pDoc->GetPart(pTop_Part); //Получаем интерфейс 3D-модели
		// Создаём эскиз прокладка
		ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch->Create();
		ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit(); //Входим в режим редактирования эскиза
		p2DDoc->ksCircle(0, 0, Dprocl / 2, 1);
		pSketchDef->EndEdit();

		// Выдавливание
		ksEntityPtr pAlignment = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef = pAlignment->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef->SetSideParam(true, etBlind, sprocl, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef->SetSketch(pSketch);
		pAlignment->Create();

		//Эскиз отверстия
		ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef2 = pSketch2->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef2->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch2->Create();
		ksDocument2DPtr p2DDoc2 = pSketchDef2->BeginEdit();
		p2DDoc2->ksCircle(0, 0, dprocl / 2, 1);
		pSketchDef2->EndEdit();

		// Вырезание
		ksEntityPtr pCut_out = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef = pCut_out->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef->cut = true;
		pCut_outDef->directionType = dtReverse;
		pCut_outDef->SetSideParam(true, etBlind, sprocl, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef->SetSketch(pSketch2);
		pCut_out->Create();

		// Создание плоскости для соосности
		ksEntityCollectionPtr flFaces = pPart->EntityCollection(o3d_face);
		for (int i = 0; i < flFaces->GetCount(); i++)
		{
			ksEntityPtr face = flFaces->GetByIndex(i);
			ksFaceDefinitionPtr def = face->GetDefinition();
			if (def->GetOwnerEntity() == pCut_out)
			{
				if (def->IsCylinder()) {
					double h, r;
					def->GetCylinderParam(&h, &r);
					if (r == dprocl / 2.f)
					{
						face->Putname("Cylinder4Assembly");
						face->Update();
					}
				}

			}

		}
		//создание плоскостей граней
		ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);

		for (int i = 0; i < fledges->GetCount(); i++)
		{
			ksEntityPtr ed = fledges->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();

			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if (z1 == 0 && x1 < Dprocl / 2) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("NignPloskProcl");
					face->Update();
				}
				else  if (z1 == sprocl)
				{
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("WerhPloskProcl");
					face->Update();
				}
			}

		}


		pDoc->SaveAs("D:\\Проекты Visual Studio\\Курсавая работа\\Прокладка.m3d");

		// делаем Компас видимым
		pKompasApp5->Visible = true;
		pDoc = pKompasApp5->Document3D(); //Получаем интерфейс документа-модели
		pDoc->Create(false, true); //Создаем документ-модель
		pPart = pDoc->GetPart(pTop_Part); //Получаем интерфейс 3D-модели
		pPart->SetMaterial(mat.c_str(), plot);//задаём материал
		pPart->Update();

		//Создаём основание гайки
		ksEntityPtr pSketch3 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef3 = pSketch3->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef3->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch3->Create();
		ksDocument2DPtr p2DDoc3 = pSketchDef3->BeginEdit();
		p2DDoc3->ksCircle(0, 0, Mgayka / 2, 1);
		pSketchDef3->EndEdit();

		// Выдавливаем основание
		ksEntityPtr pAlignment2 = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef2 = pAlignment2->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef2->SetSideParam(true, etBlind, lgayka / Kshir_rezb_gayka, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef2->SetSketch(pSketch3);
		pAlignment2->Create();

		//создаём экскиз проточки
		ksEntityPtr pSketch4 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef4 = pSketch4->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef4->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch4->Create();
		ksDocument2DPtr p2DDoc4 = pSketchDef4->BeginEdit();
		p2DDoc4->ksCircle(0, 0, (Mgayka - Mgayka / Kd_pr_gayka) / 2, 1);
		pSketchDef4->EndEdit();

		//выдавливание проточки гайки
		ksEntityPtr pAlignment3 = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef3 = pAlignment3->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef3->SetSideParam(true, etBlind, lgayka - lgayka / Km_gayka, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef3->SetSketch(pSketch4);
		pAlignment3->Create();

		// Создание смещённой плоскости
		ksEntityPtr Plane = pPart->GetDefaultEntity(o3d_planeXOY); //Получаем интерфейс объекта "плоскость XOY"
		ksEntityPtr Planeset = pPart->NewEntity(o3d_planeOffset); //Получаем интерфейс объекта "смещенная плоскость"
		ksPlaneOffsetDefinitionPtr PlaneOffsetDefinition = Planeset->GetDefinition(); //Получаем интерфейс параметров смещенной плоскости
		PlaneOffsetDefinition->direction = true;
		PlaneOffsetDefinition->offset = lgayka - lgayka / Km_gayka;
		PlaneOffsetDefinition->SetPlane(Plane); //Устанавливаем базовую плоскость
		Planeset->Create();

		// Создаём эскиз гайки
		ksEntityPtr pSketch5 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef5 = pSketch5->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef5->SetPlane(Planeset); //Получаем интерфейс объекта пренесённой плоскости и устанавливаем её
		pSketch5->Create();
		ksDocument2DPtr p2DDoc5 = pSketchDef5->BeginEdit(); //Входим в режим редактирования эскиза
		ksRegularPolygonParamPtr Regular = pKompasApp5->GetParamStruct(ko_RegularPolygonParam); //Получаем указатель на параметры многоугольника
		Regular->ang = 0;// Угол наклона многоугольника к оси Х
		Regular->count = 6;// Устанавливаем количесвто углов
		Regular->describe = false;// Устанавливем описанную окружность
		Regular->radius = Dgayka / 2;// радиус окружности
		Regular->style = 1;//стиль линии
		Regular->xc = 0;//координата х окружности
		Regular->yc = 0;//координата у окружности
		p2DDoc5->ksRegularPolygon(Regular, 0);// передача параметров прямоугольника эскизу
		pSketchDef5->EndEdit();// заканчиваем создавать эскиз

		//выдавливание Головки гайки
		ksEntityPtr pAlignment4 = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef4 = pAlignment4->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef4->SetSideParam(true, etBlind, lgayka / Km_gayka, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef4->SetSketch(pSketch5);
		pAlignment4->Create();

		//создаём экскиз проточки
		ksEntityPtr pSketch6 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef6 = pSketch6->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef6->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch6->Create();
		ksDocument2DPtr p2DDoc6 = pSketchDef6->BeginEdit();
		p2DDoc6->ksCircle(0, 0, dgayka / 2, 1);
		pSketchDef6->EndEdit();

		// Вырезание
		ksEntityPtr pCut_out2 = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef2 = pCut_out2->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef2->cut = true;
		pCut_outDef2->directionType = dtReverse;
		pCut_outDef2->SetSideParam(false, etBlind, lgayka, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef2->SetSketch(pSketch6);
		pCut_out2->Create();

		//создание фаски
		ksEntityCollectionPtr fledges2 = pPart->EntityCollection(o3d_edge);
		ksEntityPtr pChamfer = pPart->NewEntity(o3d_chamfer);
		ksEntityPtr pFillet2 = pPart->NewEntity(o3d_fillet);
		ksFilletDefinitionPtr pFilletDef2 = pFillet2->GetDefinition();

		ksChamferDefinitionPtr pChamferDef = pChamfer->GetDefinition();
		pChamferDef->SetChamferParam(true, storfas, storfas);
		ksEntityCollectionPtr fl = pFilletDef2->array();
		fl = pChamferDef->array();
		fl->Clear();

		for (int i = 0; i < fledges2->GetCount(); i++)
		{
			ksEntityPtr ed = fledges2->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();
			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if (z1 == lgayka)
				{
					fl->Add(ed);

				}
				else if (abs(Mgayka / 2 - x1) < 0.001 && z1 == 0)
				{
					fl->Add(ed);
				}
			}

		}

		pChamfer->Create();

		ksEntityCollectionPtr flFaces2 = pPart->EntityCollection(o3d_face);
		for (int i = 0; i < flFaces2->GetCount(); i++)
		{
			ksEntityPtr face = flFaces2->GetByIndex(i);
			ksFaceDefinitionPtr def = face->GetDefinition();
			if (def->IsCylinder()) {
				double h, r;
				def->GetCylinderParam(&h, &r);
				if (r == dgayka / 2.f)
				{
					face->Putname("Cylinder5Assembly");
					face->Update();
				}
				if (r == Mgayka / 2.f)
				{
					//создание резьбы
					ksEntityPtr pThread = pPart->NewEntity(o3d_thread);

					ksThreadDefinitionPtr pThDef = pThread->GetDefinition();
					pThDef->PutallLength(true);
					pThDef->PutautoDefinDr(true);
					pThDef->SetBaseObject(face);
					pThDef->Putp(hag_rezb_gayka);
					pThread->Create();
				}
			}
		}
		ksEntityCollectionPtr fledges5 = pPart->EntityCollection(o3d_edge);

		for (int i = 0; i < fledges5->GetCount(); i++)
		{
			ksEntityPtr ed = fledges5->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();

			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if (z1 == 0) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("NignPloskGayka");
					face->Update();
				}
			}

		}
		pDoc->SaveAs("D:\\Проекты Visual Studio\\Курсавая работа\\Гайка.m3d");

		//Делаем компас видимым
		pKompasApp5->Visible = true;
		pDoc = pKompasApp5->Document3D(); //Получаем интерфейс документа-модели
		pDoc->Create(false, true); //Создаем документ-модель
		pPart = pDoc->GetPart(pTop_Part); //Получаем интерфейс 3D-модели
		double mas[12][2];
		mas[0][0] = D2salnik / A_sul.xc;
		mas[0][1] = D2salnik / A_sul.yc;
		mas[1][0] = D2salnik / B_sul.xc;
		mas[1][1] = D2salnik / B_sul.yc;
		mas[2][0] = D2salnik / C_sul.xc;
		mas[2][1] = D2salnik / C_sul.yc;
		mas[3][0] = D2salnik / D_sul.xc;
		mas[3][1] = D2salnik / D_sul.yc;
		mas[4][0] = D2salnik / E_sul.xc;
		mas[4][1] = D2salnik / E_sul.yc;
		mas[5][0] = D2salnik / F_sul.xc;
		mas[5][1] = D2salnik / F_sul.yc;

		//Создаём основу сальника
		ksEntityPtr pSketch7 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef7 = pSketch7->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef7->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch7->Create();
		ksDocument2DPtr p2DDoc7 = pSketchDef7->BeginEdit();
		p2DDoc7->ksLineSeg(mas[0][0], mas[0][1], mas[1][0], mas[1][1], 1);
		p2DDoc7->ksLineSeg(mas[1][0], mas[1][1], mas[2][0], mas[2][1], 1);
		p2DDoc7->ksLineSeg(mas[2][0], mas[2][1], mas[3][0], mas[3][1], 1);
		p2DDoc7->ksLineSeg(mas[3][0], mas[3][1], mas[4][0], mas[4][1], 1);
		p2DDoc7->ksLineSeg(mas[4][0], mas[4][1], mas[5][0], mas[5][1], 1);
		p2DDoc7->ksLineSeg(mas[5][0], mas[5][1], mas[0][0], mas[0][1], 1);
		pSketchDef7->EndEdit();

		//выдавливание основания сальника
		ksEntityPtr pAlignment5 = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef5 = pAlignment5->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef5->SetSideParam(true, etBlind, 3, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef5->SetSketch(pSketch7);
		pAlignment5->Create();

		//Создание эскиза цилиндра сальника
		ksEntityPtr pSketch8 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef8 = pSketch8->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef8->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch8->Create();
		ksDocument2DPtr p2DDoc8 = pSketchDef8->BeginEdit();
		p2DDoc8->ksCircle(0, 0, Dsalnik / 2, 1);
		pSketchDef8->EndEdit();

		//выдавливание основания сальника
		ksEntityPtr pAlignment6 = pPart->NewEntity(o3d_bossExtrusion); //Получаем интерфейс объекта "операция выдавливание"
		ksBossExtrusionDefinitionPtr pAlignmentDef6 = pAlignment6->GetDefinition(); //Получаем интерфейс параметров операции "выдавливание"
		pAlignmentDef6->SetSideParam(true, etBlind, lsalnik, 0, true); //Устанавливаем параметры операции выдавливания
		pAlignmentDef6->SetSketch(pSketch8);
		pAlignment6->Create();

		// Создание смещённой плоскости
		ksEntityPtr Plan2 = pPart->GetDefaultEntity(o3d_planeXOY); //Получаем интерфейс объекта "плоскость XOY"
		ksEntityPtr Planeset2 = pPart->NewEntity(o3d_planeOffset); //Получаем интерфейс объекта "смещенная плоскость"
		ksPlaneOffsetDefinitionPtr PlaneOffsetDefinition2 = Planeset2->GetDefinition(); //Получаем интерфейс параметров смещенной плоскости
		PlaneOffsetDefinition2->direction = true;
		PlaneOffsetDefinition2->offset = 1.5;
		PlaneOffsetDefinition2->SetPlane(Plan2); //Устанавливаем базовую плоскость
		Planeset2->Create();

		// Создание смещённой плоскости
		ksEntityPtr Plan3 = pPart->GetDefaultEntity(o3d_planeXOY); //Получаем интерфейс объекта "плоскость XOY"
		ksEntityPtr Planeset3 = pPart->NewEntity(o3d_planeOffset); //Получаем интерфейс объекта "смещенная плоскость"
		ksPlaneOffsetDefinitionPtr PlaneOffsetDefinition3 = Planeset3->GetDefinition(); //Получаем интерфейс параметров смещенной плоскости
		PlaneOffsetDefinition3->direction = true;
		PlaneOffsetDefinition3->offset = 3;
		PlaneOffsetDefinition3->SetPlane(Plan3); //Устанавливаем базовую плоскость
		Planeset3->Create();

		//Создание эскиза отверстия в цилиндре сальника
		ksEntityPtr pSketch9 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef9 = pSketch9->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef9->SetPlane(Planeset3); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch9->Create();
		ksDocument2DPtr p2DDoc9 = pSketchDef9->BeginEdit();
		p2DDoc9->ksCircle(0, 0, Msalnik / 2, 1);
		pSketchDef9->EndEdit();

		//Создание эскиза меньшего отверстия на основании
		ksEntityPtr pSketch10 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef10 = pSketch10->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef10->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch10->Create();
		ksDocument2DPtr p2DDoc10 = pSketchDef10->BeginEdit();
		p2DDoc10->ksCircle(0, D1salnik / 2, d1salnik / 2, 1);
		pSketchDef10->EndEdit();

		//вырезание отверстия на основании для болтов

		//вырезание отверстия в целиндре
		ksEntityPtr pCut_out4 = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef4 = pCut_out4->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef4->cut = true;
		pCut_outDef4->directionType = dtReverse;
		pCut_outDef4->SetSideParam(false, etBlind, lsalnik - 3, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef4->SetSketch(pSketch9);
		pCut_out4->Create();

		//Создание эскиза центрального отверстия 
		ksEntityPtr pSketch11 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef11 = pSketch11->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef11->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY)); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch11->Create();
		ksDocument2DPtr p2DDoc11 = pSketchDef11->BeginEdit();
		p2DDoc11->ksCircle(0, 0, dSalnik / 2, 1);
		pSketchDef11->EndEdit();

		//вырезание центрального отверстия
		ksEntityPtr pCut_out3 = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef3 = pCut_out3->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef3->cut = true;
		pCut_outDef3->directionType = dtReverse;
		pCut_outDef3->SetSideParam(true, etBlind, 3, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef3->SetSketch(pSketch11);
		pCut_out3->Create();

		//вырезание меньшего отверстия на основании
		ksEntityPtr pCut_out5 = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef5 = pCut_out5->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef5->cut = true;
		pCut_outDef5->directionType = dtReverse;
		pCut_outDef5->SetSideParam(true, etBlind, 3, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef5->SetSketch(pSketch10);
		pCut_out5->Create();

		//Создание эскиза отверстия в цилиндре сальника
		ksEntityPtr pSketch12 = pPart->NewEntity(o3d_sketch); //Получаем интерфейс объекта "Эскиз"
		ksSketchDefinitionPtr pSketchDef12 = pSketch12->GetDefinition(); //Получаем интерфейс параметров эскиза
		pSketchDef12->SetPlane(Planeset2); //Получаем интерфейс объекта "плоскость XOY" и устанавливаем её
		pSketch12->Create();
		ksDocument2DPtr p2DDoc12 = pSketchDef12->BeginEdit();
		p2DDoc12->ksCircle(0, D1salnik / 2, d2salnik / 2, 1);
		pSketchDef12->EndEdit();

		//вырезание большего отверстия на основании сальника для болта
		ksEntityPtr pCut_out6 = pPart->NewEntity(o3d_cutExtrusion); //Получаем интерфейс объекта "операция вырезания"
		ksCutExtrusionDefinitionPtr pCut_outDef6 = pCut_out6->GetDefinition(); //Получаем интерфейс параметров операции "вырезания"
		pCut_outDef6->cut = true;
		pCut_outDef6->directionType = dtReverse;
		pCut_outDef6->SetSideParam(true, etBlind, 1.5, 0, true); //Устанавливаем параметры операции вырезания
		pCut_outDef6->SetSketch(pSketch12);
		pCut_out6->Create();

		//Массив окружности
		ksEntityPtr CircularCopy = pPart->NewEntity(o3d_circularCopy); //Получаем интерфейс объекта операции
		ksCircularCopyDefinitionPtr CircularCopyset = CircularCopy->GetDefinition(); //Получаем интерфейс параметрова операции
		CircularCopyset->count1 = 1;
		CircularCopyset->SetAxis(pPart->GetDefaultEntity(o3d_axisOZ)); //Устанавливаем ось операции
		CircularCopyset->SetCopyParamAlongDir(3, 360, true, false); //Устанавливаем параметры копирования
		ksEntityCollectionPtr Circlularcol = CircularCopyset->GetOperationArray();//Получаем массив копируемых элементов
		Circlularcol->Clear();
		Circlularcol->Add(pCut_out6);
		Circlularcol->Add(pCut_out5);
		CircularCopy->Create();

		// фаска
		ksEntityCollectionPtr fledges3 = pPart->EntityCollection(o3d_edge);
		ksEntityPtr pChamfer2 = pPart->NewEntity(o3d_chamfer);
		ksEntityPtr pFillet3 = pPart->NewEntity(o3d_fillet);
		ksFilletDefinitionPtr pFilletDef3 = pFillet3->GetDefinition();

		ksChamferDefinitionPtr pChamferDef2 = pChamfer2->GetDefinition();
		pChamferDef2->SetChamferParam(true, storfas, storfas);
		fl = pFilletDef2->array();
		fl = pChamferDef2->array();
		fl->Clear();


		for (int i = 0; i < fledges3->GetCount(); i++)
		{
			ksEntityPtr ed = fledges3->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();
			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if ((abs(Msalnik / 2 - y1) <= 0.001 || abs(Msalnik / 2 - x1) <= 0.001) && z1 == lsalnik)
				{
					fl->Add(ed);

				}
			}

		}

		pChamfer2->Create();

		// фаска
		storfas = dSalnik / Kfas;
		ksEntityCollectionPtr fledges6 = pPart->EntityCollection(o3d_edge);
		ksEntityPtr pChamfer3 = pPart->NewEntity(o3d_chamfer);
		ksEntityPtr pFillet4 = pPart->NewEntity(o3d_fillet);
		ksFilletDefinitionPtr pFilletDef4 = pFillet4->GetDefinition();

		ksChamferDefinitionPtr pChamferDef3 = pChamfer3->GetDefinition();
		pChamferDef3->SetChamferParam(true, storfas, storfas);
		fl = pFilletDef3->array();
		fl = pChamferDef3->array();
		fl->Clear();


		for (int i = 0; i < fledges6->GetCount(); i++)
		{
			ksEntityPtr ed = fledges6->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();
			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if ((abs(dSalnik / 2 - y1) <= 0.001 || abs(dSalnik / 2 - x1) <= 0.001) && z1 == 0)
				{
					fl->Add(ed);
				}
			}

		}

		pChamfer3->Create();
		//создание имён плоскостей сальника
		ksEntityCollectionPtr fledges4 = pPart->EntityCollection(o3d_edge);

		for (int i = 0; i < fledges4->GetCount(); i++)
		{
			ksEntityPtr ed = fledges4->GetByIndex(i);
			ksEdgeDefinitionPtr def = ed->GetDefinition();

			if (def->IsCircle())
			{
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				if ((!p1) || (!p2))
				{
					continue;
				}
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if (z1 == 3) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("WerhOsnSalnik");
					face->Update();
				}
				else  if (z1 == lsalnik)
				{
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("WerhSalnik");
					face->Update();
				}
			}

		}
		ksEntityCollectionPtr flFaces3 = pPart->EntityCollection(o3d_face);
		for (int i = 0; i < flFaces3->GetCount(); i++)
		{
			ksEntityPtr face = flFaces3->GetByIndex(i);
			ksFaceDefinitionPtr def = face->GetDefinition();
				if (def->IsCylinder()) {
					double h, r;
					def->GetCylinderParam(&h, &r);
					if (r == dSalnik / 2.f)
					{
						face->Putname("Cylinder6Assembly");
						face->Update();
					}
					if (abs(Msalnik / 2.f - r) <= 0.001)
					{
						//создание резьбы
						ksEntityPtr pThread = pPart->NewEntity(o3d_thread);

						ksThreadDefinitionPtr pThDef = pThread->GetDefinition();
						pThDef->PutallLength(true);
						pThDef->PutautoDefinDr(true);
						pThDef->SetBaseObject(face);
						pThDef->Putp(hag_rezb_saln);
						pThread->Create();
					}

				}

		}
		pDoc->SaveAs("D:\\Проекты Visual Studio\\Курсавая работа\\Сальник.m3d");

		//Создание сборки
		pDoc = pKompasApp5->Document3D();

		pDoc->Create(false, false);

		pPart = pDoc->GetPart(pTop_Part);

		ksPartPtr pSalnik, pProcl1, pProcl2, pGayka;
		pDoc->SetPartFromFile("D:\\Проекты Visual Studio\\Курсавая работа\\Сальник.m3d", pPart, true);
		pDoc->SetPartFromFile("D:\\Проекты Visual Studio\\Курсавая работа\\Прокладка.m3d", pPart, true);
		pDoc->SetPartFromFile("D:\\Проекты Visual Studio\\Курсавая работа\\Прокладка.m3d", pPart, true);
		pDoc->SetPartFromFile("D:\\Проекты Visual Studio\\Курсавая работа\\Гайка.m3d", pPart, true);

		pSalnik = pDoc->GetPart(0);
		pProcl1 = pDoc->GetPart(1);
		pProcl2 = pDoc->GetPart(2);
		pGayka = pDoc->GetPart(3);

		//ищем имена плоскостей
		ksEntityCollectionPtr col = pSalnik->EntityCollection(o3d_face);

		ksEntityPtr WerhOsnSalnik = col->GetByName("WerhOsnSalnik", true, true);
		ksEntityPtr WerhSalnik = col->GetByName("WerhSalnik", true, true);

		ksEntityPtr BossCylinder6Assembly = col->GetByName("Cylinder6Assembly", true, true);

		col = pProcl1->EntityCollection(o3d_face);
		ksEntityPtr NignPloskProcl = col->GetByName("NignPloskProcl", true, true);
		ksEntityPtr WerhPloskProcl = col->GetByName("WerhPloskProcl", true, true);
		ksEntityPtr BossCylinder4Assembly = col->GetByName("Cylinder4Assembly", true, true);

		col = pProcl2->EntityCollection(o3d_face);
		ksEntityPtr NignPloskProcl2 = col->GetByName("NignPloskProcl", true, true);
		ksEntityPtr WerhPloskProcl2 = col->GetByName("WerhPloskProcl", true, true);
		ksEntityPtr BossCylinder8Assembly = col->GetByName("Cylinder4Assembly", true, true);

		col = pGayka->EntityCollection(o3d_face);
		ksEntityPtr BossCylinder5Assembly = col->GetByName("Cylinder5Assembly", true, true);
		ksEntityPtr NignPloskGayka = col->GetByName("NignPloskGayka", true, true);

		//добавим в документ соответствующие зависимости
		pDoc->AddMateConstraint(mc_Concentric, BossCylinder6Assembly, BossCylinder4Assembly, 1, 1, 0);
		pDoc->AddMateConstraint(mc_Concentric, BossCylinder6Assembly, BossCylinder8Assembly, 1, 1, 0);
		pDoc->AddMateConstraint(mc_Concentric, BossCylinder6Assembly, BossCylinder5Assembly, 1, 1, 0);

		pDoc->AddMateConstraint(0, WerhOsnSalnik, NignPloskProcl, 0, 0, 0);
		pDoc->AddMateConstraint(0, WerhPloskProcl, NignPloskProcl2, 0, 0, 0);
		pDoc->AddMateConstraint(0, WerhPloskProcl2, NignPloskGayka, 0, 0, 0);

		pDoc->RebuildDocument();

		pDoc->SaveAs("D:\\Проекты Visual Studio\\Курсавая работа\\Сальник фланцевый.a3d");
	}
	else
	{
		if (!M_gayka_saln)
		{
			str += L"Диаметр резьбы на гайке и сальнике должны совпадать!\n";
		}
		if (!D_gayka)
		{
			str += L"D гайки должна быть больше d и М гайки и 0!\n";
		}
		if (!d_gayka)
		{
			str += L"d гайки должна быть больше 0!\n";
		}
		if (!M_gayka)
		{
			str += L"М гайки должна быть больше 0!\n";
		}
		if (!l_gayka)
		{
			str += L"l гайки должна быть больше 0!\n";
		}
		if (!M_saln)
		{
			str += L"М сальника должна быть больше 0!\n";
		}
		if (!l_saln)
		{
			str += L"l сальника должна быть больше 3!\n";
		}
		if (!D_saln)
		{
			str += L"D сальника должна быть больше M сальника и 0!\n";
		}
		if (!d_saln)
		{
			str += L"d сальника должна быть больше 0 и меньше M сальника!\n";
		}
		if (!d1_saln)
		{
			str += L"d1 сальника должна быть больше 0!\n";
		}
		if (!d2_saln)
		{
			str += L"d2 сальника должно быть больше d1 сальника и 0!\n";
		}
		if (!D1_saln)
		{
			str += L"Радиус окружности D1 сальника должен быть больше суммы радиусов d2 и D сальника и 0!\n";
		}
		if (!D_procl)
		{
			str += L"D прокладки должен быть больше d прокладки и 0!\n";
		}
		if (!d_procl)
		{
			str += L"d прокладки должно быть больше 0 и меньше d сальника!\n";
		}
		if (!s_procl)
		{
			str += L"s прокладки должно быть больше 0!\n";
		}
		if (!D_procl_saln)
		{
			str += L"D прокладка должно быть меньше М сальника, но больше d сальника!\n";
		}
		if (!l_gayka_s_procl)
		{
			str += L"Сумма l гайки и двух s прокладки в сборочном положении должны быть больше l сальника!\n";
		}
		if (!hag_rezb_salnB)
		{
			str += L"Шаг резьбы сальника должен быть больше 0!\n";
		}
		if (!hag_rezb_gaykaB)
		{
			str += L"Шаг резьбы гайки должен быть больше 0!\n";
		}
		if (!hag_rezb_gayka_saln)
		{
			str += L"\n";
		}
		MessageBox(str);
	}
}

