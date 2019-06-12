// GlobalObjectsView.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "GlobalObjectsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsView

IMPLEMENT_DYNCREATE(CGlobalObjectsView, CScrollView)

CGlobalObjectsView::CGlobalObjectsView()
{
	pApp = (CColorVisionApp *)AfxGetApp();
	GlobalObjectsRepresentationType = pApp->GlobalObjectsRepresentationType;
	CurrentStrip = pApp->ColorImageProcess->CurStrip;
	if (GlobalObjectsRepresentationType == 1)
	{
		strTitle = "Global Color Sections";
		NumOfSect = pApp->ColorImageProcess->RealColorNumSect;
		SectInform = pApp->ColorImageProcess->ColorSection;
		Num_Levels = SectInform->MaximalNumberOfBunches;
		Section = pApp->ColorImageProcess->ColorDescrSect;
		Bunches = pApp->ColorImageProcess->ColorInt;
	}
	CurrentStrip = pApp->ColorImageProcess->CurStrip;



	NumberOfStrips = pApp->ColorImageProcess->NumStrips;

	HorizVert = pApp->ColorImageProcess->HorizontalVertical;
	ChosenSection = -1;

	xBase = SPACEATLEFT;
	yBase = 3 * SPACEATBOTTOM;

	xMarkTick = 1;
	yMarkTick = 1;

}

CGlobalObjectsView::~CGlobalObjectsView()
{
	pApp = (CColorVisionApp *)AfxGetApp();
	pApp->NumberOfDoc--;
	if (GlobalObjectsRepresentationType == 1)
	{
		pApp->m_ColorSectionsRepresentation = FALSE;
		pApp->pDocColSec1 = NULL;
	}
}


BEGIN_MESSAGE_MAP(CGlobalObjectsView, CScrollView)
	//{{AFX_MSG_MAP(CGlobalObjectsView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsView drawing

void CGlobalObjectsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	pDoc = GetDocument();

	pDoc->SetTitle((LPCTSTR)strTitle);
	if (GlobalObjectsRepresentationType == 1)
	{
		pApp->pDocColSec1 = pDoc;

	}
}

void CGlobalObjectsView::OnDraw(CDC* pDC)
{
	int first_fiber;
	int first_member;
	int old_col_num;
	int bunch_average_hue;
	int bunch_average_sat;
	int bunch_average_gray;
	int first_bunch_average_hue;
	/*int NumSideHues;
	int SideHue;
	int SideTriangle;*/

	int mean_hue;
	int mean_saturation;
	int mean_gray;

	int intens;
	int num_grain;
	int intensi;
	int history;
	int bunch_number_ini;
	int bunch_number;
	int num_fibre;
	int number_of_sections;
	int number_of_sections_left;
	int number_of_sections_right;
	int* sections_connections;
	int sect_f;
	int i_seclr;
	int i_secr;
	int i_secl;
	int i_secfind;

	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;

	int TextShift;
	int Shifty;
	long Symbol_width;
	int* OldNum;
	int sect_num;
	int sect_numr;
	int yIncr1;
	int MaxSectionNumber;
	int chosen_straight;
	int inclined_comp;
	int* SectionChoice;
	int* StraightSections;
	int* InclinedComp;

	COLORREF PeakColor1;
	COLORREF PeakColor2;

	CPoint PrPoint, PrPoint1;

	TEXTMETRIC TextMetr;
	LOGFONT LF;
	CFont* PtrOldFont;
	CString str, str1;
	CPen *HuePen, *POldPen;
	CPen* PenSect;
	CBrush *HueBrush;
	CBrush* PtrOldBrush;


	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pApp = (CColorVisionApp *)AfxGetApp();

	if (!Num_Levels)
	{
		return;
	}
	CFont Tempfont;
	CFont Font, Font1;

	Tempfont.CreateStockObject(SYSTEM_FONT);
	Tempfont.GetObject(sizeof(LOGFONT), &LF);

	Font.CreateFontIndirect(&LF);
	PtrOldFont = pDC->SelectObject(&Font);

	SIZE size;
	size.cx = xMax;
	size.cy = yMax;
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(size);
	size.cx = xMax;
	size.cy = -yMax;
	pDC->SetViewportExt(size);
	pDC->SetViewportOrg(0, yMax);

	PrPoint.x = SPACEATLEFT / 4;
	PrPoint.y = yMax - SPACEATBOTTOM + LF.lfHeight;
	strCaptions = "Bunch Number";

	pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);

	PrPoint.x = xMax - SPACEATLEFT / 2 - 10 * LF.lfWidth;
	PrPoint.y = SPACEATBOTTOM;
	strCaptions = "Strip Number";

	pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);
	PrPoint.x = xMax - SPACEATLEFT / 2 - 14 * LF.lfWidth;
	PrPoint.y = yMax - SPACEATBOTTOM + LF.lfHeight;
	strCaptions = "Sections Graph";
	pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);

	pDC->SelectObject(PtrOldFont);

	pDC->SelectStockObject(BLACK_PEN);



	pDC->MoveTo(xBase, yBase);  // draw axes
	pDC->LineTo(xBase, yBase + (Num_Levels + 1)*yIncr);
	pDC->MoveTo(xBase, yBase);
	pDC->LineTo(xMax - 10, yBase);

	memset(&LF, 0, sizeof(LOGFONT));
	LF.lfHeight = 10;

	//LF.lfWidth=4;
	//LF.lfWeight= FW_ULTRALIGHT;
	Font1.CreateFontIndirect(&LF);
	PtrOldFont = pDC->SelectObject(&Font1);
	pDC->GetTextMetrics(&TextMetr);

	for (int i = yMarkTick; i <= Num_Levels; i += yMarkTick)
	{                          // draw marks on Y axis
		pDC->MoveTo(xBase - SPACEATLEFT / 6, yBase + i*yIncr);
		pDC->LineTo(xBase, yBase + i*yIncr);
		PrPoint.x = 0;
		PrPoint.y = yBase + i*yIncr + TextMetr.tmHeight / 2;
		str1.Format("%d", (int)i);
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}

	for (int k = 0; k<NumberOfStrips; k += xMarkTick)
	{                           // draw marks on X axis
		pDC->MoveTo(xBase + (k + 1)*xIncr, yBase - SPACEATBOTTOM / 5);
		pDC->LineTo(xBase + (k + 1)*xIncr, yBase);
		PrPoint.x = xBase + (k + 1)*xIncr - TextMetr.tmAveCharWidth;
		PrPoint.y = yBase - SPACEATBOTTOM / 5;
		str1.Format("%d", (int)k);
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}
	for (int j = 0; j<NumberOfStrips; j++)  // draw lines corresponding to strips
	{
		PrPoint.x = xBase + (j + 1)*xIncr;
		PrPoint.y = yBase;
		pDC->MoveTo(PrPoint);
		PrPoint.y = yBase + (Num_Levels + 1)*yIncr;
		pDC->LineTo(PrPoint);
		PrPoint.x = xBase + (j + 1)*xIncr - min(3, xIncr / 4);
		PrPoint1.x = xBase + (j + 1)*xIncr + min(3, xIncr / 4);

		bunch_number_ini = Bunches[j].NumberOfColoredIntervals;
		if (!bunch_number_ini)
		{
			bunch_number = 0;
		}
		else
		{
			bunch_number = Bunches[j].RefinedNumberOfBunches;
		}
		for (int i_gr = 0; i_gr<bunch_number; i_gr++)//draw all  grains
		{
			old_col_num = Bunches[j].old_bunch_number[i_gr];
			bunch_average_hue =
				Bunches[j].ColoredIntervalsStructure->AverageHue[old_col_num];
			bunch_average_sat =
				Bunches[j].ColoredIntervalsStructure->AverageSat[old_col_num];
			bunch_average_gray =
				Bunches[j].ColoredIntervalsStructure->AverageGray[old_col_num];


			if (bunch_average_hue>47)
			{
				bunch_average_hue -= 48;
			}
			CalculateColor(bunch_average_hue, bunch_average_sat, bunch_average_gray, &Scoor1, &Scoor2,
				&Scoor3, &NScoor1, &NScoor2, &NScoor3);

			PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
			NScoor1 = (NScoor1 + Scoor1) / 2;
			NScoor2 = (NScoor2 + Scoor2) / 2;
			NScoor3 = (NScoor3 + Scoor3) / 2;
			PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);

			OldNum = Bunches[j].OldNumbers;
			//HuePen.CreatePen(PS_SOLID, 3, PeakColor2);
			HuePen = new CPen;
			HuePen->CreatePen(PS_SOLID, 3, PeakColor1);
			HueBrush = new CBrush;
			HueBrush->CreateSolidBrush(PeakColor1);
			POldPen = pDC->SelectObject(HuePen);
			PtrOldBrush = pDC->SelectObject(HueBrush);
			PrPoint.y = yBase + i_gr*yIncr + min(3, yIncr / 2);
			PrPoint1.y = yBase + i_gr*yIncr - min(3, yIncr / 2);

			pDC->Rectangle(PrPoint.x, PrPoint.y, PrPoint1.x, PrPoint1.y);
			pDC->SelectObject(POldPen);
			pDC->SelectObject(PtrOldBrush);
			delete HuePen;
			delete HueBrush;
		}
	}
	number_of_sections = SectInform->Number_of_sections;
	SectionChoice = new int[number_of_sections];
	memset(SectionChoice, (int) '\0', (sizeof(int))*number_of_sections);

	number_of_sections_left = SectInform->Number_of_sections_left;
	number_of_sections_right = SectInform->Number_of_sections_right;
	MaxSectionNumber = max(number_of_sections_left, number_of_sections_right);
	sections_connections = pApp->ColorImageProcess->SectionNeighborsLeftRight;
	ChosenSection = pApp->NumberOfColorSection;
	if (ChosenSection >= NumOfSect)
	{
		ChosenSection = 0;
		pApp->pm_ColorSectNumDialog->m_Spin.SetPos(0);
	}
	*(SectionChoice + ChosenSection) = 1;
	StraightSections = pApp->ColorImageProcess->StraightSections;
	InclinedComp = pApp->ColorImageProcess->InclinedComponent;
	chosen_straight = *(StraightSections + ChosenSection);
	inclined_comp = *(InclinedComp + ChosenSection);
	for (int i_sect = 0; i_sect<NumOfSect; i_sect++)
	{//sc
	 //if(((SectInform->SectionVisibility[i_sect]>=12) && (Section[i_sect].length_of_section>=3))||
	 // ((SectInform->SectionVisibility[i_sect]>=15) && (Section[i_sect].length_of_section==2)))
		if (*(SectionChoice + i_sect))
		{
			mean_hue = SectInform->section_mean_hue[i_sect];
			mean_saturation = SectInform->section_mean_saturation[i_sect];
			mean_gray = SectInform->section_mean_gray[i_sect];
			CalculateColor(mean_hue, mean_saturation, mean_gray, &Scoor1, &Scoor2,
				&Scoor3, &NScoor1, &NScoor2, &NScoor3);

			PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
			NScoor1 = (NScoor1 + Scoor1) / 2;
			NScoor2 = (NScoor2 + Scoor2) / 2;
			NScoor3 = (NScoor3 + Scoor3) / 2;
			PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
			PenSect = new CPen;
			PenSect->CreatePen(PS_SOLID, 2, PeakColor1);
			POldPen = pDC->SelectObject(PenSect);

			first_fiber = Section[i_sect].base_first;
			first_member = Section[i_sect].location_of_section[first_fiber] - 1;
			history = 0;
			for (int num_fibre = first_fiber; num_fibre <= Section[i_sect].base_last; num_fibre++)
			{//fb
				num_grain = Section[i_sect].location_of_section[num_fibre];
				if (num_grain)
				{//ng
					intensi = num_grain - 1;
					if (!history)
					{
						PrPoint.x = xBase + (num_fibre + 1)*xIncr;
						PrPoint.y = yBase + intensi*yIncr;
						history = 1;
					}
					else
					{
						PrPoint1.x = xBase + (num_fibre + 1)*xIncr;
						PrPoint1.y = yBase + intensi*yIncr;

						pDC->MoveTo(PrPoint);
						pDC->LineTo(PrPoint1);
						PrPoint.x = PrPoint1.x;
						PrPoint.y = PrPoint1.y;
					}
				}//ng
			}//fb


			pDC->SelectObject(POldPen);
			delete PenSect;
		}
	}//sc
	if (MaxSectionNumber)
	{
		yIncr1 = (14 * (yMax - 3 * SPACEATBOTTOM)) / (MaxSectionNumber * 16);
	}
	for (i_secl = 0; i_secl<number_of_sections_left; i_secl++)//draw all left sections-vertices
	{//sl
		mean_hue = SectInform->section_mean_hue[i_secl];
		mean_saturation = SectInform->section_mean_saturation[i_secl];
		mean_gray = SectInform->section_mean_gray[i_secl];
		CalculateColor(mean_hue, mean_saturation, mean_gray, &Scoor1, &Scoor2,
			&Scoor3, &NScoor1, &NScoor2, &NScoor3);
		PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
		NScoor1 = (NScoor1 + Scoor1) / 2;
		NScoor2 = (NScoor2 + Scoor2) / 2;
		NScoor3 = (NScoor3 + Scoor3) / 2;
		PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
		HuePen = new CPen;
		HuePen->CreatePen(PS_SOLID, 3, PeakColor1);
		HueBrush = new CBrush;
		HueBrush->CreateSolidBrush(PeakColor1);
		POldPen = pDC->SelectObject(HuePen);
		PtrOldBrush = pDC->SelectObject(HueBrush);
		PrPoint.x = xMax - 5 * SPACEATLEFT - min(2, xIncr / 4);
		PrPoint1.x = xMax - 5 * SPACEATLEFT + min(2, xIncr / 4);
		PrPoint.y = yBase + i_secl*yIncr1 + min(2, yIncr1 / 2);
		PrPoint1.y = yBase + i_secl*yIncr1 - min(2, yIncr1 / 2);
		pDC->Rectangle(PrPoint.x, PrPoint.y, PrPoint1.x, PrPoint1.y);
		pDC->SelectObject(POldPen);
		pDC->SelectObject(PtrOldBrush);
		delete HuePen;
		delete HueBrush;
	}//sl
	for (i_secr = 0; i_secr<number_of_sections_right; i_secr++)//draw all right sections-vertices
	{//sr
		mean_hue = SectInform->section_mean_hue[number_of_sections_left + i_secr];
		mean_saturation = SectInform->section_mean_saturation[number_of_sections_left + i_secr];
		mean_gray = SectInform->section_mean_gray[number_of_sections_left + i_secr];
		CalculateColor(mean_hue, mean_saturation, mean_gray, &Scoor1, &Scoor2,
			&Scoor3, &NScoor1, &NScoor2, &NScoor3);
		PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
		NScoor1 = (NScoor1 + Scoor1) / 2;
		NScoor2 = (NScoor2 + Scoor2) / 2;
		NScoor3 = (NScoor3 + Scoor3) / 2;
		PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
		HuePen = new CPen;
		HuePen->CreatePen(PS_SOLID, 3, PeakColor1);
		HueBrush = new CBrush;
		HueBrush->CreateSolidBrush(PeakColor1);
		POldPen = pDC->SelectObject(HuePen);
		PtrOldBrush = pDC->SelectObject(HueBrush);
		PrPoint.x = xMax - 2 * SPACEATLEFT - min(2, xIncr / 4);
		PrPoint1.x = xMax - 2 * SPACEATLEFT + min(2, xIncr / 4);
		PrPoint.y = yBase + i_secr*yIncr1 + min(2, yIncr1 / 2);
		PrPoint1.y = yBase + i_secr*yIncr1 - min(2, yIncr1 / 2);
		pDC->Rectangle(PrPoint.x, PrPoint.y, PrPoint1.x, PrPoint1.y);
		pDC->SelectObject(POldPen);
		pDC->SelectObject(PtrOldBrush);
		delete HuePen;
		delete HueBrush;
	}//sr

	for (i_seclr = 0; i_seclr<number_of_sections_left; i_seclr++)//draw all left sections-vertices
	{//slr
		mean_hue = SectInform->section_mean_hue[i_seclr];
		mean_saturation = SectInform->section_mean_saturation[i_seclr];
		mean_gray = SectInform->section_mean_gray[i_seclr];
		CalculateColor(mean_hue, mean_saturation, mean_gray, &Scoor1, &Scoor2,
			&Scoor3, &NScoor1, &NScoor2, &NScoor3);
		PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
		NScoor1 = (NScoor1 + Scoor1) / 2;
		NScoor2 = (NScoor2 + Scoor2) / 2;
		NScoor3 = (NScoor3 + Scoor3) / 2;
		PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
		PenSect = new CPen;
		PenSect->CreatePen(PS_SOLID, 2, PeakColor1);
		POldPen = pDC->SelectObject(PenSect);


		PrPoint.x = xMax - 5 * SPACEATLEFT;
		PrPoint1.x = xMax - 2 * SPACEATLEFT;
		PrPoint.y = yBase + i_seclr*yIncr1;



		for (i_secfind = 0; i_secfind<number_of_sections_right; i_secfind++)
		{

			sect_f = *(sections_connections + i_seclr*(NUM_SECT1 / 2) + i_secfind);
			if (sect_f>0)
			{
				PrPoint1.y = yBase + i_secfind*yIncr1;
				pDC->MoveTo(PrPoint);
				pDC->LineTo(PrPoint1);
			}
		}
		pDC->SelectObject(POldPen);
		delete PenSect;
	}//slr	
	PrPoint.x = xMax - 6 * SPACEATLEFT - SPACEATLEFT / 2;
	/*PrPoint.y = yBase + yIncr1;
	sect_num=0;
	str1.Format("%d",(int)sect_num);
	pDC->TextOut((int)PrPoint.x,(int)PrPoint.y,str1);*/
	//for (sect_num=yMarkTick; sect_num<number_of_sections_left; sect_num+=yMarkTick)
	for (sect_num = 0; sect_num<number_of_sections_left; sect_num++)
	{                          // draw marks on Y axis
							   // pDC->MoveTo(xBase-SPACEATLEFT/6, yBase+i*yIncr);
							   //pDC->LineTo(xBase, yBase+i*yIncr);
							   //PrPoint.x = xMax - 6*SPACEATLEFT-SPACEATLEFT/2;
							   //PrPoint.y = yBase + sect_num*yIncr + TextMetr.tmHeight/2;
							   //PrPoint.y = yBase + sect_num*yIncr1+yIncr1;
		PrPoint.y = yBase + sect_num*yIncr1 + TextMetr.tmHeight / 2;
		str1.Format("%d", (int)sect_num);
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}
	PrPoint.x = xMax - SPACEATLEFT;
	/*PrPoint.y = yBase + yIncr1;
	sect_num=number_of_sections_left;
	str1.Format("%d",(int)sect_num);*/
	//pDC->TextOut((int)PrPoint.x,(int)PrPoint.y,str1);
	//for (sect_numr=yMarkTick; sect_numr<number_of_sections_right; sect_numr+=yMarkTick)
	for (sect_numr = 0; sect_numr<number_of_sections_right; sect_numr++)
	{                          // draw marks on Y axis
							   // pDC->MoveTo(xBase-SPACEATLEFT/6, yBase+i*yIncr);
							   //pDC->LineTo(xBase, yBase+i*yIncr);
							   //PrPoint.x = xMax - SPACEATLEFT;
							   //PrPoint.y = yBase + sect_num*yIncr + TextMetr.tmHeight/2;
		PrPoint.y = yBase + sect_numr*yIncr1 + TextMetr.tmHeight / 2;
		str1.Format("%d", (int)(number_of_sections_left + sect_numr));
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}
	for (int j_sect = 0; j_sect<NumOfSect; j_sect++)
	{                                  // inscribe numbers of sections
		if (*(SectionChoice + j_sect))
		{
			num_fibre = Section[j_sect].base_first;
			num_grain = Section[j_sect].location_of_section[num_fibre];
			intens = num_grain - 1;
			PrPoint.x = xBase + (num_fibre + 1)*xIncr - 4 * TextMetr.tmAveCharWidth;;
			PrPoint.y = yBase + intens*yIncr + TextMetr.tmHeight / 2;
			str1.Format("%d", (int)j_sect);
			pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
		}

	}
	pDC->SelectObject(PtrOldFont);

	//pApp= (CColorVisionApp *)AfxGetApp ();

	/*ChosenSection=pApp->NumberOfColorSection;

	if(ChosenSection >= NumOfSect)
	{
	ChosenSection=0;
	pApp->pm_ColorSectNumDialog->m_Spin.SetPos(0);
	}*/

	if (ChosenSection >= 0)

	{
		int num_strip;

		num_strip = Section[ChosenSection].base_first;
		num_grain = Section[ChosenSection].location_of_section[num_strip];
		mean_hue = SectInform->section_mean_hue[ChosenSection];
		mean_saturation = SectInform->section_mean_saturation[ChosenSection];
		mean_gray = SectInform->section_mean_gray[ChosenSection];
		if (mean_hue>47)
		{
			mean_hue -= 48;
		}

		intens = num_grain - 1;

		PrPoint.x = xBase + (num_strip + 1)*xIncr - min(5, xIncr / 3);
		PrPoint1.x = xBase + (num_strip + 1)*xIncr + min(5, xIncr / 3);

		PrPoint.y = yBase + intens*yIncr + min(5, yIncr);
		PrPoint1.y = yBase + intens*yIncr - min(5, yIncr);
		pDC->Rectangle(PrPoint.x, PrPoint.y, PrPoint1.x, PrPoint1.y);

		CFont Tempfont1;
		CFont Font2;

		Tempfont1.CreateStockObject(SYSTEM_FONT);
		Tempfont1.GetObject(sizeof(LOGFONT), &LF);
		TextShift = 20 * LF.lfWidth;
		Shifty = (3 * LF.lfHeight) / 2;


		memset(&LF, 0, sizeof(LOGFONT));
		LF.lfHeight = 11;

		Font2.CreateFontIndirect(&LF);
		PtrOldFont = pDC->SelectObject(&Font2);
		pDC->SelectStockObject(BLACK_PEN);

		pDC->GetTextMetrics(&TextMetr);

		POINT Text_Origin;


		Text_Origin.y = SPACEATBOTTOM + TextMetr.tmHeight;
		Text_Origin.x = 2;
		Symbol_width = TextMetr.tmAveCharWidth;
		str = "Hue";
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
		Text_Origin.x += 4 * Symbol_width;
		str1.Format("=%d", mean_hue);
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
		Text_Origin.x += 4 * Symbol_width;

		str = "Sat";
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
		Text_Origin.x += 4 * Symbol_width;
		str1.Format("=%d", mean_saturation);
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
		Text_Origin.x += 4 * Symbol_width;

		str = "Gray";
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
		Text_Origin.x += 5 * Symbol_width;
		str1.Format("=%d", mean_gray);
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
		Text_Origin.x += 4 * Symbol_width;
		str = "StraightTest";
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
		Text_Origin.x += 12 * Symbol_width;
		str1.Format("=%d", chosen_straight);
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
		Text_Origin.x += 6 * Symbol_width;
		str = "InclinedComp";
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
		Text_Origin.x += 12 * Symbol_width;
		str1.Format("=%d", inclined_comp);
		pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);



		pDC->SelectObject(PtrOldFont);
	}
	delete[] SectionChoice;
}

/////////////////////////////////////////////////////////////////////////////

void
CGlobalObjectsView::SetMaxCoordinates()
{
	CRect rect;

	GetClientRect(rect);


	xMax = rect.right;
	yMax = rect.bottom;

	xIncr = (14 * (xMax - 6 * SPACEATLEFT)) / (NumberOfStrips * 16);
	if (SectInform->MaximalNumberOfBunches)
	{
		yIncr = (14 * (yMax - 3 * SPACEATBOTTOM)) / (Num_Levels * 16);
	}
	else
	{
		yIncr = 0;
	}
}
/////////////////////////////////////////////////////////////////////////////

void

CGlobalObjectsView::CalculateColor(int Hue, int Satur, int Gray, int* STCoor1, int* STCoor2,
	int* STCoor3, int* NTCoor1, int* NTCoor2, int* NTCoor3)
{
	int NumSideHues;
	int SideHue;
	int SideTriangle;
	int Imax;
	int GrayLev;
	int NewGrayLev;
	int Coor1;
	int Coor2;
	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;

	NumSideHues = (NUM_HUES / 3);
	SideTriangle = Hue / NumSideHues;
	SideHue = Hue - NumSideHues*SideTriangle;

	if (SideTriangle == 0)
	{
		Coor1 = 255 - CoorHuePoints1[SideHue];
		Coor2 = CoorHuePoints1[SideHue];
		Scoor1 = 84 + (Satur*(Coor1 - 84)) / 15;
		Scoor2 = 84 + (Satur*(Coor2 - 84)) / 15;
		Scoor3 = (84 * (15 - Satur)) / 15;

		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;

		//PeakColor2=RGB(Scoor1,Scoor2, Scoor3);
		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>Gray)
		{
			/*Scoor1=(Scoor1*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
			Scoor2=(Scoor2*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
			Scoor3=(Scoor3*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;*/
			NScoor1 = (Scoor1*Gray) / GrayLev;
			NScoor2 = (Scoor2*Gray) / GrayLev;
			NScoor3 = (Scoor3*Gray) / GrayLev;
			NewGrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}

	}
	if (SideTriangle == 1)
	{
		Coor1 = 255 - CoorHuePoints1[SideHue];
		Coor2 = CoorHuePoints1[SideHue];
		Scoor1 = (84 * (15 - Satur)) / 15;
		Scoor2 = 84 + (Satur*(Coor1 - 84)) / 15;
		Scoor3 = 84 + (Satur*(Coor2 - 84)) / 15;
		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;

		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>Gray)
		{
			NScoor1 = (Scoor1*Gray) / GrayLev;
			NScoor2 = (Scoor2*Gray) / GrayLev;
			NScoor3 = (Scoor3*Gray) / GrayLev;
			NewGrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}

	}

	if (SideTriangle == 2)
	{
		Coor1 = CoorHuePoints1[SideHue];
		Coor2 = 255 - CoorHuePoints1[SideHue];
		Scoor1 = 84 + (Satur*(Coor1 - 84)) / 15;
		Scoor2 = (84 * (15 - Satur)) / 15;
		Scoor3 = 84 + (Satur*(Coor2 - 84)) / 15;
		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;

		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>Gray)
		{
			NScoor1 = (Scoor1*Gray) / GrayLev;
			NScoor2 = (Scoor2*Gray) / GrayLev;
			NScoor3 = (Scoor3*Gray) / GrayLev;
			NewGrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}

	}
	*STCoor1 = Scoor1;
	*STCoor2 = Scoor2;
	*STCoor3 = Scoor3;
	*NTCoor1 = NScoor1;
	*NTCoor2 = NScoor2;
	*NTCoor3 = NScoor3;
}

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsView diagnostics

#ifdef _DEBUG
void CGlobalObjectsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGlobalObjectsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsView message handlers

void CGlobalObjectsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class

	SetMaxCoordinates();

	pDoc = GetDocument();

	Invalidate();
	pDoc->UpdateAllViews(this);
	CScrollView::OnUpdate(pSender, lHint, pHint);

}

void CGlobalObjectsView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	SetMaxCoordinates();

	pDoc = GetDocument();

	Invalidate();
	pDoc->UpdateAllViews(this);

}
