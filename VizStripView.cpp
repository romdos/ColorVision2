// VizStripView.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "VizStripView.h"

/*CMemoryState oldMemState, newMemState;
CMemoryState diffMemState;*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVizStripView

IMPLEMENT_DYNCREATE(CVizStripView, CScrollView)

CVizStripView::CVizStripView()
{

	pApp = (CColorVisionApp *)AfxGetApp();
	CurrentStrip = pApp->ColorImageProcess->CurStrip;
	ProcTime = pApp->ColorImageProcess->execution_time;
	//MySpinner=NULL;
	if (pApp->StripRepresentationType == 1)
	{
		strTitle = "Strip Color Representation";
		NumLevels = NUM_INTEN;
	}
	if (pApp->StripRepresentationType == 2)
	{
		strTitle = "Strip Greyscale Representation";
		NumLevels = NUM_INTEN1;
	}
	if (pApp->StripRepresentationType == 3)
	{
		strTitle = "Bunch Representation";
		NumLevels = NUM_INTEN;
		//MySpinner = new CSpinButtonCtrl;

	}
	StripRepresentationType = pApp->StripRepresentationType;
	xBase = SPACEATLEFT;
	yBase = 2 * SPACEATBOTTOM;
	NumRatio = 0;
	NumInterval = 0;
}

CVizStripView::~CVizStripView()
{ 
	pApp = (CColorVisionApp *)AfxGetApp(); 
	if (StripRepresentationType == 1)
	{
		pApp->m_StripColorRepresentation = FALSE;
		pApp->pDocs1 = NULL;
	}
	if (StripRepresentationType == 2)
	{
		pApp->m_StripGrayRepresentation = FALSE;
		pApp->pDocs2 = NULL;
	}
	if (StripRepresentationType == 3)
	{
		pApp->m_ColorBunchRepresentation = FALSE;
		pApp->pDocs3 = NULL;
	}
	pApp->StripRepresentationType = 0;
	/*	if(MySpinner!=NULL)
	{
	delete MySpinner;
	MySpinner=NULL;
	}*/
}


BEGIN_MESSAGE_MAP(CVizStripView, CScrollView)
	//{{AFX_MSG_MAP(CVizStripView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVizStripView drawing

void CVizStripView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	pDoc = GetDocument();

	pDoc->SetTitle((LPCTSTR)strTitle);
	if (StripRepresentationType == 1)
	{
		pApp->pDocs1 = pDoc;

	}
	if (StripRepresentationType == 2)
	{
		pApp->pDocs2 = pDoc;
	}
	if (StripRepresentationType == 3)
	{
		pApp->pDocs3 = pDoc;
	}
	/*#ifdef _DEBUG
	oldMemState.Checkpoint();
	#endif*/
}

void CVizStripView::OnDraw(CDC* pDC)
{
	int num_intensity;
	int num_interval;
	int k;
	int Dimension;
	int BunchRange;
	int* OldNum;
	int old_num;
	int bunch_number;
	int upper_hue;
	int lower_hue;
	int bunch_average_hue;
	int bunch_average_sat;
	int bunch_average_gray;
	int left_contrast;
	int right_contrast;
	int left_adjacent;
	int right_adjacent;
	int upper_sat;
	int lower_sat;
	int number_ext;
	int grain_intensity;
	int bunch_significance;
	int lower_gray;
	int upper_gray;
	int low_intense;
	int upper_intense;
	int NumSideHues;
	int SideTriangle;
	int SideHue;
	int Beg_bunch;
	int End_bunch;
	int old_col_num;
	int new_adjacent_bunch_num;
	int old_col_number;
	int belong_bunch;
	int covering_belong_bunch;
	int Coor1;
	int Coor2;
	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;
	int GrayLev;
	int NewGrayLev;
	int Imax;
	int* blocking_bunch;
	int TextShift;
	int Shifty;
	int short_dimension;
	//BOOL GGBorGGR;

	TEXTMETRIC TextMetr;
	LOGFONT LF;
	CFont* PtrOldFont;
	CPoint PrPoint;
	RECT Rect;
	CString str1;
	CPen Pen, *POldPen;
	CPen HuePen;
	long Symbol_width;


	COLORREF PeakColor1;
	COLORREF PeakColor2;




	pDoc = GetDocument();


	pApp = (CColorVisionApp *)AfxGetApp();
	StripNumber = pApp->NumberStripClicked;
	GGBorGGR = pApp->PermuteRatios;

	HorizVert = CurrentStrip[StripNumber].HorizontalVertical;
	xMarkTick = NumLevels / X_TICKS;
	yMarkTick = CurrentStrip[StripNumber].DimY / Y_TICKS;

	num_intensity = -1;
	num_interval = -1;


	CFont Tempfont;
	CFont Font, Font1;

	Tempfont.CreateStockObject(SYSTEM_FONT);
	Tempfont.GetObject(sizeof(LOGFONT), &LF);
	//memset(&LF,0, sizeof(LOGFONT));
	LF.lfHeight = 10;

	//LF.lfWidth=4;
	//LF.lfWeight= FW_ULTRALIGHT;
	//Font1.CreateFontIndirect(&LF);
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
	xIncr = (xMax - xBase) / NumLevels;

	if (HorizVert == 1)
	{
		strCaptions = "Image Height";
		pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);
		Dimension = CurrentStrip[StripNumber].DimY;

	}
	else
	{
		strCaptions = "Image Width";
		pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);
		Dimension = CurrentStrip[StripNumber].DimX;
	}

	if (Dimension <= 320)
	{
		short_dimension = Dimension;
	}
	else
	{
		short_dimension = Dimension / 2;
	}

	yIncr = (yMax - yBase - LF.lfHeight) / short_dimension;

	yMarkTick = short_dimension / Y_TICKS;
	ImageRect.left = xBase;
	ImageRect.top = yMax - yBase - short_dimension*yIncr;
	ImageRect.bottom = yMax - yBase;
	ImageRect.right = xBase + xIncr*NumLevels;
	PrPoint.x += LF.lfWidth * 13;
	strCaptions = "Strip";
	pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);
	PrPoint.x += LF.lfWidth * 5;
	str1.Format("%d", (int)pApp->NumberStripClicked);
	pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	PrPoint.x = xMax - 4 * SPACEATLEFT / 2 - LF.lfWidth * 10;
	PrPoint.y = 3 * SPACEATBOTTOM / 2;
	if ((StripRepresentationType == 1) || (StripRepresentationType == 3))
	{
		if (GGBorGGR)
		{
			strCaptions = "G/(G+B) Intensity";
		}
		else
		{
			strCaptions = "G/(G+R) Intensity";
		}
	}
	if (StripRepresentationType == 2)
	{
		strCaptions = "Grayscale Intensity";
	}

	pDC->TextOut(PrPoint.x, PrPoint.y, strCaptions);


	//Invalidate();
	// pDoc->UpdateAllViews(this,0,NULL);

	pDC->SelectObject(PtrOldFont);

	pDC->SelectStockObject(BLACK_PEN);



	pDC->MoveTo(xBase, yBase);  // draw axes
	pDC->LineTo(xBase, yMax - SPACEATBOTTOM - LF.lfHeight - 1);
	pDC->MoveTo(xBase, yBase);
	pDC->LineTo(xMax, yBase);

	memset(&LF, 0, sizeof(LOGFONT));
	LF.lfHeight = 10;

	//LF.lfWidth=4;
	//LF.lfWeight= FW_ULTRALIGHT;
	Font1.CreateFontIndirect(&LF);
	PtrOldFont = pDC->SelectObject(&Font1);
	pDC->GetTextMetrics(&TextMetr);

	for (int i = yMarkTick; i <= short_dimension; i += yMarkTick)
	{                          // draw marks on Y axis
		pDC->MoveTo(xBase - SPACEATLEFT / 6, yBase + i*yIncr);
		pDC->LineTo(xBase, yBase + i*yIncr);
		PrPoint.x = 0;
		PrPoint.y = yBase + i*yIncr + TextMetr.tmHeight / 2;
		if (Dimension <= 320)
		{
			str1.Format("%d", (int)i);
		}
		else
		{
			str1.Format("%d", (int)2 * i);
		}
		//str1.Format("%d",(int)2*i);
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}
	PrPoint.y = yBase + yIncr*short_dimension + TextMetr.tmHeight / 2;
	PlotHeight = PrPoint.y;
	pDC->MoveTo(xBase - SPACEATLEFT / 6, yBase + short_dimension);
	pDC->LineTo(xBase, yBase + short_dimension);
	str1.Format("%d", (int)Dimension);
	pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	for (int i = xMarkTick; i <= NumLevels; i += xMarkTick)
	{                           // draw marks on X axis
		pDC->MoveTo(xBase + i*xIncr, yBase - SPACEATBOTTOM / 5);
		pDC->LineTo(xBase + i*xIncr, yBase);
		PrPoint.x = xBase + i*xIncr - TextMetr.tmAveCharWidth;
		PrPoint.y = yBase - SPACEATBOTTOM / 5;
		str1.Format("%d", (int)i);
		pDC->TextOut((int)PrPoint.x, (int)PrPoint.y, str1);
	}

	pDC->SelectObject(PtrOldFont);

	if ((StripRepresentationType == 1) || (StripRepresentationType == 2))
	{
		Pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
		POldPen = pDC->SelectObject(&Pen);

		for (int i = 0; i<NumLevels; i++)  // draw all subsegments for each intensity
		{

			if (StripRepresentationType == 1)
			{
				for (k = 0; k<CurrentStrip[StripNumber].IntAllInform[i].num_of_int; k++)
				{
					if (CurrentStrip[StripNumber].IntAllInform[i].num_of_int)
					{
						if (Dimension <= 320)
						{
							pDC->MoveTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[i].BegInt[k])*yIncr);
							pDC->LineTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[i].EndInt[k])*yIncr);
						}
						else
						{
							pDC->MoveTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[i].BegInt[k] / 2)*yIncr);
							pDC->LineTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[i].EndInt[k] / 2)*yIncr);
						}
					}
				}

			}

			if (StripRepresentationType == 2)
			{
				for (k = 0; k<CurrentStrip[StripNumber].IntAllInformGray[i].num_of_int; k++)
				{
					if (CurrentStrip[StripNumber].IntAllInformGray[i].num_of_int)
					{
						if (Dimension <= 320)
						{
							pDC->MoveTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInformGray[i].BegInt[k])*yIncr);
							pDC->LineTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInformGray[i].EndInt[k])*yIncr);
						}
						else
						{
							pDC->MoveTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInformGray[i].BegInt[k] / 2)*yIncr);
							pDC->LineTo(xBase + i*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInformGray[i].EndInt[k] / 2)*yIncr);
						}
					}
				}
			}




		}
		pDC->SelectObject(POldPen);
		return;
	}

	if (StripRepresentationType == 3)
	{
		BunchNumber = pApp->NumberOfBunch;
		old_col_number = pApp->ColorImageProcess->ColorInt[StripNumber].NumberOfColoredIntervals;
		bunch_number = pApp->ColorImageProcess->ColorInt[StripNumber].RefinedNumberOfBunches;

		if (BunchNumber >= bunch_number)
		{
			return;
		}
		blocking_bunch = pApp->ColorImageProcess->ColorInt[StripNumber].bunch_blocking;
		old_col_num = pApp->ColorImageProcess->ColorInt[StripNumber].old_bunch_number[BunchNumber];
		if (old_col_num<old_col_number)
		{

			low_intense =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->LowerIntensity[old_col_num];
			upper_intense =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->UpperIntensity[old_col_num];
			BunchRange = upper_intense - low_intense + 1;
			lower_hue =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->LowerHueValue[old_col_num];
			upper_hue =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->UpperHueValue[old_col_num];
			bunch_average_hue =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageHue[old_col_num];
			bunch_average_sat =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageSat[old_col_num];
			bunch_average_gray =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageGray[old_col_num];
			lower_sat =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->LowerSatValue[old_col_num];
			upper_sat =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->UpperSatValue[old_col_num];
			number_ext =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->Cardinality[old_col_num];
			grain_intensity =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->GrainIntensity[old_col_num];
			bunch_significance =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->Significance[old_col_num];
			lower_gray =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->LowerGrayscale[old_col_num];
			upper_gray =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->UpperGrayscale[old_col_num];

			Beg_bunch =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->BegInterv[old_col_num];
			End_bunch =
				pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->EndInterv[old_col_num];
			left_contrast = pApp->ColorImageProcess->ColorInt[StripNumber].left_continuation[old_col_num];
			if (left_contrast>0)
			{
				left_contrast -= 1;
			}
			else
			{
				if (left_contrast<0)
				{
					left_contrast += 1;
				}
			}
			right_contrast = pApp->ColorImageProcess->ColorInt[StripNumber].right_continuation[old_col_num];
			if (right_contrast>0)
			{
				right_contrast -= 1;
			}
			else
			{
				if (right_contrast<0)
				{
					right_contrast += 1;
				}
			}
			left_adjacent = pApp->ColorImageProcess->ColorInt[StripNumber].left_adjacent[old_col_num];
			right_adjacent = pApp->ColorImageProcess->ColorInt[StripNumber].right_adjacent[old_col_num];
			if (left_adjacent>0)
			{
				left_adjacent = left_adjacent - 1;
				new_adjacent_bunch_num = pApp->ColorImageProcess->ColorInt[StripNumber].new_bunch_number[left_adjacent];
				if (new_adjacent_bunch_num >= 0)
				{
					left_adjacent = new_adjacent_bunch_num;
				}
				else
				{
					left_adjacent = -left_adjacent;
				}
			}
			else
			{
				if (left_adjacent<0)
				{
					left_adjacent = abs(left_adjacent) - 1;
					new_adjacent_bunch_num = pApp->ColorImageProcess->ColorInt[StripNumber].new_bunch_number[left_adjacent];
					if (new_adjacent_bunch_num >= 0)
					{
						left_adjacent = new_adjacent_bunch_num;
					}
					else
					{
						left_adjacent = -left_adjacent;
					}
				}
				else
				{
					left_adjacent = -1;
				}
			}

			if (right_adjacent>0)
			{
				right_adjacent = right_adjacent - 1;
				new_adjacent_bunch_num = pApp->ColorImageProcess->ColorInt[StripNumber].new_bunch_number[right_adjacent];
				if (new_adjacent_bunch_num >= 0)
				{
					right_adjacent = new_adjacent_bunch_num;
				}
				else
				{
					right_adjacent = -right_adjacent;
				}
			}
			else
			{
				if (right_adjacent<0)
				{
					right_adjacent = abs(right_adjacent) - 1;
					new_adjacent_bunch_num = pApp->ColorImageProcess->ColorInt[StripNumber].new_bunch_number[right_adjacent];
					if (new_adjacent_bunch_num >= 0)
					{
						right_adjacent = new_adjacent_bunch_num;
					}
					else
					{
						right_adjacent = -right_adjacent;
					}
				}
				else
				{
					right_adjacent = -1;
				}
			}
			if (bunch_average_gray >= 0)
			{
				NumSideHues = (NUM_HUES / 3);
				if (bunch_average_hue>47)
				{
					bunch_average_hue -= 48;
				}
				SideTriangle = bunch_average_hue / NumSideHues;
				SideHue = bunch_average_hue - NumSideHues*SideTriangle;
				if (SideTriangle == 0)
				{
					Coor1 = 255 - CoorHuePoints[SideHue];
					Coor2 = CoorHuePoints[SideHue];
					Scoor1 = 84 + (bunch_average_sat*(Coor1 - 84)) / 15;
					Scoor2 = 84 + (bunch_average_sat*(Coor2 - 84)) / 15;
					Scoor3 = (84 * (15 - bunch_average_sat)) / 15;

					Imax = max(Scoor1, max(Scoor2, Scoor3));
					Scoor1 = (Scoor1 * 255) / Imax;
					Scoor2 = (Scoor2 * 255) / Imax;
					Scoor3 = (Scoor3 * 255) / Imax;

					PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
					GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
					GrayLev = GrayLev / 4;
					if (GrayLev>bunch_average_gray)
					{
						/*Scoor1=(Scoor1*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
						Scoor2=(Scoor2*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
						Scoor3=(Scoor3*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;*/
						NScoor1 = (Scoor1*bunch_average_gray) / GrayLev;
						NScoor2 = (Scoor2*bunch_average_gray) / GrayLev;
						NScoor3 = (Scoor3*bunch_average_gray) / GrayLev;
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
					Coor1 = 255 - CoorHuePoints[SideHue];
					Coor2 = CoorHuePoints[SideHue];
					Scoor1 = (84 * (15 - bunch_average_sat)) / 15;
					Scoor2 = 84 + (bunch_average_sat*(Coor1 - 84)) / 15;
					Scoor3 = 84 + (bunch_average_sat*(Coor2 - 84)) / 15;
					Imax = max(Scoor1, max(Scoor2, Scoor3));
					Scoor1 = (Scoor1 * 255) / Imax;
					Scoor2 = (Scoor2 * 255) / Imax;
					Scoor3 = (Scoor3 * 255) / Imax;
					PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
					GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
					GrayLev = GrayLev / 4;
					if (GrayLev>bunch_average_gray)
					{
						NScoor1 = (Scoor1*bunch_average_gray) / GrayLev;
						NScoor2 = (Scoor2*bunch_average_gray) / GrayLev;
						NScoor3 = (Scoor3*bunch_average_gray) / GrayLev;
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
					Coor1 = CoorHuePoints[SideHue];
					Coor2 = 255 - CoorHuePoints[SideHue];
					Scoor1 = 84 + (bunch_average_sat*(Coor1 - 84)) / 15;
					Scoor2 = (84 * (15 - bunch_average_sat)) / 15;
					Scoor3 = 84 + (bunch_average_sat*(Coor2 - 84)) / 15;
					Imax = max(Scoor1, max(Scoor2, Scoor3));
					Scoor1 = (Scoor1 * 255) / Imax;
					Scoor2 = (Scoor2 * 255) / Imax;
					Scoor3 = (Scoor3 * 255) / Imax;
					PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
					GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
					GrayLev = GrayLev / 4;
					if (GrayLev>bunch_average_gray)
					{
						NScoor1 = (Scoor1*bunch_average_gray) / GrayLev;
						NScoor2 = (Scoor2*bunch_average_gray) / GrayLev;
						NScoor3 = (Scoor3*bunch_average_gray) / GrayLev;
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
				NScoor1 = (NScoor1 + Scoor1) / 2;
				NScoor2 = (NScoor2 + Scoor2) / 2;
				NScoor3 = (NScoor3 + Scoor3) / 2;
			}
			else
			{

				NScoor1 = 2 * bunch_average_gray + 128;
				NScoor2 = 2 * bunch_average_gray + 128;
				NScoor3 = 2 * bunch_average_gray + 128;
				Scoor1 = NScoor1;
				Scoor2 = NScoor2;
				Scoor3 = NScoor3;
				PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
			}
			PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);

			OldNum = pApp->ColorImageProcess->ColorInt[StripNumber].OldNumbers;
			//HuePen.CreatePen(PS_SOLID, 3, PeakColor2);
			HuePen.CreatePen(PS_SOLID, 3, PeakColor1);

			POldPen = pDC->SelectObject(&HuePen);
			for (int i = 0; i<pApp->ColorImageProcess->ColorInt[StripNumber].NumInterestingIntensities; i++) //draw the subsegments for the bunch intensity
			{

				old_num = OldNum[i];
				for (k = 0; k<CurrentStrip[StripNumber].IntAllInform[old_num].num_of_int; k++)
				{
					belong_bunch = pApp->ColorImageProcess->ColorInt[StripNumber].ColorInform[i].NumberOfColorBunch[k];
					if (belong_bunch >= 0)
					{
						covering_belong_bunch = *(blocking_bunch + belong_bunch);

						if ((old_col_num == belong_bunch) || ((covering_belong_bunch) &&
							(old_col_num == covering_belong_bunch - 1)))
						{
							if (CurrentStrip[StripNumber].IntAllInform[old_num].num_of_int)
							{
								if (Dimension <= 320)
								{
									pDC->MoveTo(xBase + old_num*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[old_num].BegInt[k])*yIncr);
									pDC->LineTo(xBase + old_num*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[old_num].EndInt[k])*yIncr);
								}
								else
								{
									pDC->MoveTo(xBase + old_num*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[old_num].BegInt[k] / 2)*yIncr);
									pDC->LineTo(xBase + old_num*xIncr, yBase + (CurrentStrip[StripNumber].IntAllInform[old_num].EndInt[k] / 2)*yIncr);
								}

							}
						}
					}
				}
			}

			pDC->SelectObject(POldPen);

			CFont Tempfont1;
			CFont Font2;

			Tempfont1.CreateStockObject(SYSTEM_FONT);
			Tempfont1.GetObject(sizeof(LOGFONT), &LF);
			TextShift = 20 * LF.lfWidth;
			Shifty = (3 * LF.lfHeight) / 2;


			memset(&LF, 0, sizeof(LOGFONT));
			LF.lfHeight = 12;

			Font2.CreateFontIndirect(&LF);
			PtrOldFont = pDC->SelectObject(&Font2);
			pDC->SelectStockObject(BLACK_PEN);

			pDC->GetTextMetrics(&TextMetr);

			POINT Text_Origin;


			Text_Origin.y = SPACEATBOTTOM - TextMetr.tmHeight + 2;
			Text_Origin.x = 2;
			Symbol_width = TextMetr.tmAveCharWidth;
			str = "GI";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", grain_intensity);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "AH";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", bunch_average_hue);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "AS";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", bunch_average_sat);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "AG";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", bunch_average_gray);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "LI";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", low_intense);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "UI";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", upper_intense);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "LH";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", lower_hue);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "UH";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", upper_hue);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;



			str = "LS";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", lower_sat);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "US";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", upper_sat);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;



			str = "LG";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", lower_gray);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "UG";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", upper_gray);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			Text_Origin.x = 2;
			Text_Origin.y += TextMetr.tmHeight + 2;

			str = "Beg";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 4 * Symbol_width;
			str1.Format("=%d", Beg_bunch);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 5 * Symbol_width;

			str = "End";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 4 * Symbol_width;
			str1.Format("=%d", End_bunch);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 5 * Symbol_width;

			str = "NE";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", number_ext);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;

			str = "Si";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", bunch_significance);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 8 * Symbol_width;

			str = "LC";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", left_contrast);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;
			str = "RC";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", right_contrast);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;
			str = "LA";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", left_adjacent);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;
			str = "RA";
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
			Text_Origin.x += 3 * Symbol_width;
			str1.Format("=%d", right_adjacent);
			pDC->TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
			Text_Origin.x += 4 * Symbol_width;


			pDC->SelectObject(PtrOldFont);
		}
	}
	/*#ifdef _DEBUG

	newMemState.Checkpoint();
	if(newMemState.Difference(oldMemState,newMemState))
	{
	TRACE("Difference between first and now!\n\n");
	diffMemState.DumpStatistics();
	}
	#endif*/

}

/////////////////////////////////////////////////////////////////////////////

void
CVizStripView::SetMaxCoordinates()
{
	CRect rect;

	GetClientRect(rect);


	xMax = rect.right;
	yMax = rect.bottom;
	pApp = (CColorVisionApp *)AfxGetApp();
	StripNumber = pApp->NumberStripClicked;

}
/////////////////////////////////////////////////////////////////////////////
// CVizStripView diagnostics

#ifdef _DEBUG
void CVizStripView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVizStripView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVizStripView message handlers

void CVizStripView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class

	SetMaxCoordinates();

	pDoc = GetDocument();

	Invalidate();
	pDoc->UpdateAllViews(this);
	CScrollView::OnUpdate(pSender, lHint, pHint);

}

void CVizStripView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	SetMaxCoordinates();

	pDoc = GetDocument();

	Invalidate();
	pDoc->UpdateAllViews(this);

}

void CVizStripView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// TODO: Add your message handler code here and/or call default
	CFont* PtrOldFont;
	int num_intensity;
	int IntBeg;
	int IntEnd;
	int Signif;
	int LowerGr;
	int UpperGr;
	int MeanGr;
	int LowerMR;
	int UpperMR;
	int MeanMR;
	int new_number_of_intensity;
	int NumBunch;
	int ColType;
	int ZeroFract;
	int Z1;
	int PosFr;
	int NegFr;
	int PosPeak;
	int PMFr;
	int NegPeak;
	int NMFr;
	int MeanHue;
	int MeanCircleHue;
	int MeanSat;
	int Peak_Triangle_Side;
	int SideHue;
	int NumSideHues;
	int Coor1;
	int Coor2;
	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;
	//int Coor3;
	int GrayLev;
	int NewGrayLev;
	int Imax;
	int TextShift;
	int Shifty;
	int Shifty1;
	int TrHeight;
	int TrBaseLength;
	int CircleSize;
	int MainOpRatio;
	int color_deviation;
	int color_deviation1;
	float Center_of_mass_point;
	float Center_of_mass_point1;
	int LineLength;
	int StepDev;
	int ChartLength;
	COLORREF PeakColor1;
	COLORREF PeakColor2;



	if ((StripRepresentationType == 1) || (StripRepresentationType == 2))
	{
		PosPeak = -1;
		NegPeak = -1;
		ZeroFract = -1;
		Z1 = -1;
		PosFr = 0;
		PMFr = 0;
		NegFr = 0;
		NMFr = 0;

		if (ImageRect.PtInRect(point))
		{
			if (CalculateIntervalCharacteristics(point))
			{
				CScrollView::OnLButtonDown(nFlags, point);
				CClientDC dc(this);
				TEXTMETRIC tm;
				LOGFONT LF;
				CFont Tempfont;
				CFont Font;

				Tempfont.CreateStockObject(SYSTEM_FONT);
				Tempfont.GetObject(sizeof(LOGFONT), &LF);
				TextShift = 20 * LF.lfWidth;
				Shifty = (3 * LF.lfHeight) / 2;


				memset(&LF, 0, sizeof(LOGFONT));
				LF.lfHeight = 12;

				Font.CreateFontIndirect(&LF);
				PtrOldFont = dc.SelectObject(&Font);
				dc.SelectStockObject(BLACK_PEN);
				//POINT Coord;

				POINT Text_Origin;
				POINT TriangleOrigin;
				POINT TriangleBaseEnd;
				POINT TriangleTopVertex;
				POINT CenterPoint;
				POINT GBPoint;
				POINT NegDevPoint;
				POINT PosDevPoint;
				POINT ZeroPoint;
				POINT LinePoint1;
				POINT LinePoint2;
				POINT LineCenter;
				POINT DevScalePoint;
				POINT ColorPoint;
				CBrush GrBrush;
				CBrush RedBrush;
				CBrush GreenBrush;
				CBrush BlueBrush;
				CBrush YellowBrush;
				CBrush HueBrush;
				CBrush HueBrush1;
				CPen   GrPen;
				CPen   GrThinPen;
				CPen   RedPen;
				CPen   GreenPen;
				CPen   BluePen;
				CPen YellowPen;
				CPen HuePen;
				CPen HuePen1;
				CBrush* PtrOldBrush;
				CPen* PtrOldPen;
				//CString str,str1;
				long Symbol_width;
				CWnd *p_Wnd;

				if (dc.GetTextMetrics(&tm))
				{
					p_Wnd = dc.GetWindow();
					p_Wnd->Invalidate();
					p_Wnd->UpdateWindow();
					/*Coord.x = SPACEATLEFT/6;
					Coord.y = yMax-tm.tmHeight;*/

					Symbol_width = tm.tmAveCharWidth;
					Text_Origin.y = yMax - tm.tmHeight;
					Text_Origin.x = 2;



					if (StripRepresentationType == 1)
					{
						if ((NumRatio>60) && (NumRatio<71))
						{
							num_intensity = NumRatio - 39;
						}
						else
						{
							if ((NumRatio>70) && (NumRatio<81))
							{
								num_intensity = NumRatio - 49;
							}
							else
							{
								if ((NumRatio>80) && (NumRatio<95))
								{
									num_intensity = NumRatio - 49;
								}
								else
								{
									if ((NumRatio>94) && (NumRatio <= 108))
									{
										num_intensity = NumRatio - 63;
									}
									else
									{
										if ((NumRatio>108) && (NumRatio <= 123))
										{
											num_intensity = NumRatio - 63;
										}
										else
										{
											/*if(NumRatio>123)
											{
											if((NumRatio==124)||(NumRatio==135))
											{
											num_intensity=31;
											}
											else
											{
											if(NumRatio%2==0)
											{
											num_intensity=30;
											}
											else
											{
											num_intensity=32;
											}
											}
											}*/
											//else
											//{
											num_intensity = NumRatio;
											//}


										}
									}
								}

							}
						}
						IntBeg = CurrentStrip[StripNumber].IntAllInform[NumRatio].BegInt[NumInterval];
						IntEnd = CurrentStrip[StripNumber].IntAllInform[NumRatio].EndInt[NumInterval];
						Signif = CurrentStrip[StripNumber].IntAllInform[NumRatio].Signif[NumInterval];
						LowerGr = CurrentStrip[StripNumber].IntAllInform[NumRatio].LowerGrayScale[NumInterval];
						UpperGr = CurrentStrip[StripNumber].IntAllInform[NumRatio].UpperGrayScale[NumInterval];
						MeanGr = CurrentStrip[StripNumber].IntAllInform[NumRatio].GrayScaleMean[NumInterval];
						LowerMR = CurrentStrip[StripNumber].IntAllInform[NumRatio].LowerMRatio[NumInterval];
						UpperMR = CurrentStrip[StripNumber].IntAllInform[NumRatio].UpperMRatio[NumInterval];
						MeanMR = CurrentStrip[StripNumber].IntAllInform[NumRatio].MeanMRatio[NumInterval];
						if (NumRatio>123)
						{
							num_intensity = MeanMR;
						}
						MainOpRatio =
							CurrentStrip[StripNumber].IntAllInform[NumRatio].MainOpponentRatiosBalance[NumInterval];
						NumBunch = -1;
						MeanHue = -1;
						MeanCircleHue = -1;
						MeanSat = -1;
						ColType = -1;

						if (GGBorGGR)
						{
							str = "GB";
						}
						else
						{
							str = "GR";
						}
						//str = "GB";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						Text_Origin.x += 3 * Symbol_width;
						str1.Format("=%d", num_intensity);
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 3 * Symbol_width;
						str = "--";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						Text_Origin.x += Symbol_width;
						str1.Format("%d", NumRatio);
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;
						if ((MainOpRatio != -1) && (NumRatio != 0))
						{

							ZeroFract = CurrentStrip[StripNumber].IntAllInform[NumRatio].ZeroRatio[NumInterval];
							Z1 = CurrentStrip[StripNumber].IntAllInform[NumRatio].ZeroRatio1[NumInterval];
							PosFr = CurrentStrip[StripNumber].IntAllInform[NumRatio].PositiveFraction[NumInterval];
							NegFr = CurrentStrip[StripNumber].IntAllInform[NumRatio].NegativeFraction[NumInterval];
							PosPeak = CurrentStrip[StripNumber].IntAllInform[NumRatio].ColorPeak[NumInterval];
							pApp = (CColorVisionApp *)AfxGetApp();
							if (PosPeak>0)
							{
								color_deviation = (pApp->ColorImageProcess->invert_color_difference2[PosPeak] +
									pApp->ColorImageProcess->invert_color_difference1[PosPeak]) / 2;
								Center_of_mass_point =
									(float)CurrentStrip[StripNumber].IntAllInform[NumRatio].CenterOfMass[NumInterval] /
									(float)16;

								PMFr = CurrentStrip[StripNumber].IntAllInform[NumRatio].PeakFraction[NumInterval];
							}
							NegPeak = CurrentStrip[StripNumber].IntAllInform[NumRatio].ColorPeak1[NumInterval];
							if (NegPeak>0)
							{
								color_deviation1 =
									(pApp->ColorImageProcess->invert_color_difference2[NegPeak] +
										pApp->ColorImageProcess->invert_color_difference1[NegPeak]) / 2;
								Center_of_mass_point1 =
									(float)CurrentStrip[StripNumber].IntAllInform[NumRatio].CenterOfMass1[NumInterval] /
									(float)16;
								NMFr = CurrentStrip[StripNumber].IntAllInform[NumRatio].PeakFraction1[NumInterval];
							}
							new_number_of_intensity =
								pApp->ColorImageProcess->ColorInt[StripNumber].intensities_with_colored_int[NumRatio];
							NumBunch = pApp->ColorImageProcess->ColorInt[StripNumber].
								ColorInform[new_number_of_intensity].NumberOfColorBunch[NumInterval];
							ColType =
								pApp->ColorImageProcess->ColorInt[StripNumber].
								ColorInform[new_number_of_intensity].TypeOfColor[NumInterval];
							MeanCircleHue = pApp->ColorImageProcess->ColorInt[StripNumber].
								ColorInform[new_number_of_intensity].TotCMHue[NumInterval];
							MeanHue = pApp->ColorImageProcess->ColorInt[StripNumber].
								ColorInform[new_number_of_intensity].TriangleHue[NumInterval];
							MeanSat = pApp->ColorImageProcess->ColorInt[StripNumber].
								ColorInform[new_number_of_intensity].TotCMSat[NumInterval];
							if (MeanHue >= 0)
							{
								//MeanSat=pApp->ColorImageProcess->ColorInt[StripNumber].
								//ColorInform[new_number_of_intensity].TotCMSat[NumInterval];
								NumSideHues = (NUM_HUES / 3);
								Peak_Triangle_Side = MeanHue / NumSideHues;

								SideHue = MeanHue - NumSideHues*Peak_Triangle_Side;
								if (Peak_Triangle_Side == 0)
								{
									Coor1 = 255 - CoorHuePoints[SideHue];
									Coor2 = CoorHuePoints[SideHue];
									Scoor1 = 84 + (MeanSat*(Coor1 - 84)) / 15;
									Scoor2 = 84 + (MeanSat*(Coor2 - 84)) / 15;
									Scoor3 = (84 * (15 - MeanSat)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev>MeanGr)
									{
										/*Scoor1=(Scoor1*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
										Scoor2=(Scoor2*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;
										Scoor3=(Scoor3*(MeanGr+(GrayLev-MeanGr)/2))/GrayLev;*/
										NScoor1 = (Scoor1*MeanGr) / GrayLev;
										NScoor2 = (Scoor2*MeanGr) / GrayLev;
										NScoor3 = (Scoor3*MeanGr) / GrayLev;
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
								if (Peak_Triangle_Side == 1)
								{
									Coor1 = 255 - CoorHuePoints[SideHue];
									Coor2 = CoorHuePoints[SideHue];
									Scoor1 = (84 * (15 - MeanSat)) / 15;
									Scoor2 = 84 + (MeanSat*(Coor1 - 84)) / 15;
									Scoor3 = 84 + (MeanSat*(Coor2 - 84)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev>MeanGr)
									{
										NScoor1 = (Scoor1*MeanGr) / GrayLev;
										NScoor2 = (Scoor2*MeanGr) / GrayLev;
										NScoor3 = (Scoor3*MeanGr) / GrayLev;
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
								if (Peak_Triangle_Side == 2)
								{
									Coor1 = CoorHuePoints[SideHue];
									Coor2 = 255 - CoorHuePoints[SideHue];
									Scoor1 = 84 + (MeanSat*(Coor1 - 84)) / 15;
									Scoor2 = (84 * (15 - MeanSat)) / 15;
									Scoor3 = 84 + (MeanSat*(Coor2 - 84)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev>MeanGr)
									{
										NScoor1 = (Scoor1*MeanGr) / GrayLev;
										NScoor2 = (Scoor2*MeanGr) / GrayLev;
										NScoor3 = (Scoor3*MeanGr) / GrayLev;
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

								NScoor1 = (NScoor1 + Scoor1) / 2;
								NScoor2 = (NScoor2 + Scoor2) / 2;
								NScoor3 = (NScoor3 + Scoor3) / 2;

							}
							else
							{
								Scoor1 = 255;
								Scoor2 = 255;
								Scoor3 = 255;
								NScoor1 = 2 * MeanGr + 128;
								NScoor2 = 2 * MeanGr + 128;
								NScoor3 = 2 * MeanGr + 128;
								PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
							}
							PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
							/*str = "GB";
							dc.TextOut((int)Text_Origin.x,(int)Text_Origin.y,str);
							Text_Origin.x+=3*Symbol_width;
							str1.Format("=%d",num_intensity);
							dc.TextOut((int)Text_Origin.x,(int)Text_Origin.y,str1);
							Text_Origin.x+=4*Symbol_width;*/
						}
					}

					if (StripRepresentationType == 2)
					{
						IntBeg = CurrentStrip[StripNumber].IntAllInformGray[NumRatio].BegInt[NumInterval];
						IntEnd = CurrentStrip[StripNumber].IntAllInformGray[NumRatio].EndInt[NumInterval];
						Signif = CurrentStrip[StripNumber].IntAllInformGray[NumRatio].Signif[NumInterval];
						str = "GS";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						Text_Origin.x += 3 * Symbol_width;
						str1.Format("=%d", NumRatio);
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;
					}



					str = "NInt";
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
					str1.Format("=%d", NumInterval);
					Text_Origin.x += 4 * Symbol_width;
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
					Text_Origin.x += 3 * Symbol_width;
					str = "Beg";
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
					Text_Origin.x += 4 * Symbol_width;

					str1.Format("=%d", IntBeg);
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
					Text_Origin.x += 5 * Symbol_width;
					str = "End";
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
					Text_Origin.x += 4 * Symbol_width;

					str1.Format("=%d", IntEnd);
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
					Text_Origin.x += 5 * Symbol_width;
					str = "Sgf";
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

					str1.Format("=%d", Signif);
					Text_Origin.x += 4 * Symbol_width;
					dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);

					if (StripRepresentationType == 1)
					{
						Text_Origin.x += 6 * Symbol_width;
						str = "LGr";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

						str1.Format("=%d", LowerGr);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;

						str = "UGr";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", UpperGr);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;

						str = "MGr";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", MeanGr);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;

						str = "LR";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", LowerMR);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;

						str = "UR";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", UpperMR);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 4 * Symbol_width;

						str = "MR";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", MeanMR);
						Text_Origin.x += 4 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						if (MainOpRatio != -1)
						{
							Text_Origin.x += 4 * Symbol_width;
							str = "NBu";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

							str1.Format("=%d", NumBunch);
							Text_Origin.x += 3 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "CT";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

							str1.Format("=%d", ColType);
							Text_Origin.x += 3 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "MTH";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

							str1.Format("=%d", MeanHue);
							Text_Origin.x += 5 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "MCH";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

							str1.Format("=%d", MeanCircleHue);
							Text_Origin.x += 5 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "MS";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);

							str1.Format("=%d", MeanSat);
							Text_Origin.x += 3 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						}

						Text_Origin.x = SPACEATLEFT / 4 + TextShift / 4;
						Text_Origin.y = Shifty;
						Shifty1 = Shifty + tm.tmHeight;
						str = "time";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", ProcTime);
						Text_Origin.x += 5 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						Text_Origin.x += 6 * Symbol_width;
						str = "MOR";
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
						str1.Format("=%d", MainOpRatio);
						Text_Origin.x += 5 * Symbol_width;
						dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
						if ((MainOpRatio != -1) && (NumRatio != 0))
						{

							Text_Origin.x += 4 * Symbol_width;
							str = "ZeroF";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", ZeroFract);
							Text_Origin.x += 5 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "Z1";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", Z1);
							Text_Origin.x += 3 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "Pos";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", PosFr);
							Text_Origin.x += 4 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "Neg";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", NegFr);
							Text_Origin.x += 4 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "PosM";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", PosPeak);
							Text_Origin.x += 6 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "PMFr";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", PMFr);
							Text_Origin.x += 5 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "NegM";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", NegPeak);
							Text_Origin.x += 6 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							Text_Origin.x += 4 * Symbol_width;
							str = "NMFr";
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str);
							str1.Format("=%d", NMFr);
							Text_Origin.x += 5 * Symbol_width;
							dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							CircleSize = 3;
							TriangleTopVertex.y = Shifty1 + CircleSize + 1;
							TriangleOrigin.y = yMax - PlotHeight - CircleSize - 1;
							TrHeight = TriangleOrigin.y - TriangleTopVertex.y;
							//TrHeight=TriangleOrigin.y-Shifty1;
							TrBaseLength = (TrHeight * 100) / 173;
							TriangleOrigin.x = xBase + 6;
							TriangleBaseEnd.x = TriangleOrigin.x + 2 * TrBaseLength;
							TriangleBaseEnd.y = TriangleOrigin.y;
							TriangleTopVertex.x = TriangleOrigin.x + TrBaseLength;
							CenterPoint.x = TriangleTopVertex.x;
							CenterPoint.y = TriangleOrigin.y - TrHeight / 3;

							GrPen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));



							PtrOldPen = dc.SelectObject(&GrPen);

							LinePoint1.x = TriangleBaseEnd.x + 6;
							LinePoint1.y = TriangleOrigin.y - (TriangleOrigin.y - TriangleTopVertex.y) / 4;
							ChartLength = LinePoint1.y - TriangleTopVertex.y;
							LinePoint2.y = LinePoint1.y;
							LinePoint2.x = xMax - SPACEATRIGHT;
							LineCenter.x = (LinePoint1.x + LinePoint2.x) / 2;
							LineCenter.y = LinePoint1.y;
							LineLength = LinePoint2.x - LinePoint1.x;
							StepDev = LineLength / 16 - 1;
							DevScalePoint.y = LinePoint1.y;
							Text_Origin.y = DevScalePoint.y + tm.tmHeight / 2;

							dc.MoveTo(LinePoint1);
							dc.LineTo(LinePoint2);

							for (int i_sc = 0; i_sc< 8; i_sc++)
							{
								DevScalePoint.x = LineCenter.x + i_sc*StepDev;
								dc.MoveTo(DevScalePoint);
								dc.LineTo(DevScalePoint.x, DevScalePoint.y + 3);
								str1.Format("%d", i_sc);
								Text_Origin.x = DevScalePoint.x;
								dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							}
							for (int i_sc = 0; i_sc< 7; i_sc++)
							{
								DevScalePoint.x = LineCenter.x - (i_sc + 1)*StepDev;
								dc.MoveTo(DevScalePoint);
								dc.LineTo(DevScalePoint.x, DevScalePoint.y + 3);
								str1.Format("%d", -(i_sc + 1));
								Text_Origin.x = DevScalePoint.x;
								dc.TextOut((int)Text_Origin.x, (int)Text_Origin.y, str1);
							}

							dc.MoveTo(TriangleOrigin);
							dc.LineTo(TriangleTopVertex);
							dc.MoveTo(TriangleOrigin);
							dc.LineTo(TriangleBaseEnd);
							dc.MoveTo(TriangleBaseEnd);
							dc.LineTo(TriangleTopVertex);
							dc.SelectObject(PtrOldPen);
							GrThinPen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
							GrBrush.CreateSolidBrush(RGB(128, 128, 128));
							PtrOldPen = dc.SelectObject(&GrThinPen);
							PtrOldBrush = dc.SelectObject(&GrBrush);
							dc.Ellipse(CenterPoint.x - CircleSize + 1, CenterPoint.y - CircleSize + 1,
								CenterPoint.x + CircleSize - 1, CenterPoint.y + CircleSize - 1);
							if (GGBorGGR)
							{
								GBPoint.y = TriangleOrigin.y;
								GBPoint.x = TriangleOrigin.x + (num_intensity*(TriangleBaseEnd.x - TriangleOrigin.x)) / (NUM_INTEN1 - 1);
								dc.MoveTo(TriangleTopVertex);
							}
							else
							{
								GBPoint.x = TriangleTopVertex.x + ((TriangleBaseEnd.x - TriangleTopVertex.x)*num_intensity) / (NUM_INTEN1 - 1);
								GBPoint.y = TriangleTopVertex.y + ((TriangleBaseEnd.y - TriangleTopVertex.y)*num_intensity) / (NUM_INTEN1 - 1);
								dc.MoveTo(TriangleOrigin);
							}

							dc.LineTo(GBPoint);

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

							RedPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
							RedBrush.CreateSolidBrush(RGB(255, 0, 0));
							PtrOldPen = dc.SelectObject(&RedPen);
							PtrOldBrush = dc.SelectObject(&RedBrush);
							dc.Ellipse(TriangleTopVertex.x - CircleSize, TriangleTopVertex.y - CircleSize,
								TriangleTopVertex.x + CircleSize, TriangleTopVertex.y + CircleSize);
							if ((NMFr>0) && (NegPeak>0))
							{
								if (GGBorGGR)
								{
									if (num_intensity>31)
									{
										NegDevPoint.x = (TriangleTopVertex.x + TriangleBaseEnd.x) / 2 +
											((TriangleTopVertex.x - TriangleBaseEnd.x)*(color_deviation1)) / (NUM_INTEN1 - 1);
										NegDevPoint.y = (TriangleTopVertex.y + TriangleBaseEnd.y) / 2 +
											((TriangleTopVertex.y - TriangleBaseEnd.y)*color_deviation1) / (NUM_INTEN1 - 1);

										dc.MoveTo(TriangleOrigin);
									}
									else
									{
										NegDevPoint.x = (TriangleTopVertex.x + TriangleOrigin.x) / 2 -
											((TriangleTopVertex.x - TriangleOrigin.x)*(color_deviation1)) / (NUM_INTEN1 - 1);
										NegDevPoint.y = (TriangleTopVertex.y + TriangleOrigin.y) / 2 -
											((TriangleTopVertex.y - TriangleOrigin.y)*color_deviation1) / (NUM_INTEN1 - 1);

										dc.MoveTo(TriangleBaseEnd);
									}
								}
								else
								{
									if (num_intensity>31)
									{
										NegDevPoint.x = TriangleOrigin.x + ((31 - color_deviation1)*(TriangleBaseEnd.x - TriangleOrigin.x)) / (NUM_INTEN1 - 1);
										NegDevPoint.y = TriangleOrigin.y;
										dc.MoveTo(TriangleTopVertex);
									}
									else
									{
										NegDevPoint.x = (TriangleTopVertex.x + TriangleOrigin.x) / 2 -
											((TriangleTopVertex.x - TriangleOrigin.x)*(color_deviation1)) / (NUM_INTEN1 - 1);
										NegDevPoint.y = (TriangleTopVertex.y + TriangleOrigin.y) / 2 -
											((TriangleTopVertex.y - TriangleOrigin.y)*color_deviation1) / (NUM_INTEN1 - 1);
										dc.MoveTo(TriangleBaseEnd);
									}
								}
								dc.LineTo(NegDevPoint);
								DevScalePoint.x = LineCenter.x - NegPeak*StepDev;
								dc.Ellipse(DevScalePoint.x - CircleSize, DevScalePoint.y - CircleSize,
									DevScalePoint.x + CircleSize, DevScalePoint.y + CircleSize);
								dc.Rectangle(DevScalePoint.x - 2, DevScalePoint.y - (NMFr*ChartLength) / 16 - 2,
									DevScalePoint.x + 2, DevScalePoint.y - 2);
								DevScalePoint.x = LineCenter.x - (int)(Center_of_mass_point1*((float)StepDev));
								dc.Ellipse(DevScalePoint.x - CircleSize - 1, DevScalePoint.y - CircleSize - 1 + 4,
									DevScalePoint.x + CircleSize + 1, DevScalePoint.y + CircleSize + 4 + 1);
							}

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

							GreenPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
							GreenBrush.CreateSolidBrush(RGB(0, 255, 0));
							PtrOldBrush = dc.SelectObject(&GreenBrush);
							PtrOldPen = dc.SelectObject(&GreenPen);
							dc.Ellipse(TriangleBaseEnd.x - CircleSize, TriangleBaseEnd.y - CircleSize,
								TriangleBaseEnd.x + CircleSize, TriangleBaseEnd.y + CircleSize);
							if ((PMFr>0) && (PosPeak>0))
							{

								if (GGBorGGR)
								{
									if (num_intensity>31)
									{
										PosDevPoint.x = (TriangleTopVertex.x + TriangleBaseEnd.x) / 2 +
											((TriangleBaseEnd.x - TriangleTopVertex.x)*color_deviation) / (NUM_INTEN1 - 1);
										PosDevPoint.y = (TriangleTopVertex.y + TriangleBaseEnd.y) / 2 +
											((TriangleBaseEnd.y - TriangleTopVertex.y)*color_deviation) / (NUM_INTEN1 - 1);
										dc.MoveTo(TriangleOrigin);
									}
									else
									{
										PosDevPoint.x = (TriangleTopVertex.x + TriangleOrigin.x) / 2 -
											((TriangleOrigin.x - TriangleTopVertex.x)*color_deviation) / (NUM_INTEN1 - 1);
										PosDevPoint.y = (TriangleTopVertex.y + TriangleOrigin.y) / 2 -
											((TriangleOrigin.y - TriangleTopVertex.y)*color_deviation) / (NUM_INTEN1 - 1);
										dc.MoveTo(TriangleBaseEnd);
									}
								}
								else
								{
									if (num_intensity>31)
									{
										PosDevPoint.y = TriangleOrigin.y;
										PosDevPoint.x = TriangleOrigin.x + ((31 + color_deviation)*(TriangleBaseEnd.x - TriangleOrigin.x)) / (NUM_INTEN1 - 1);
										dc.MoveTo(TriangleTopVertex);
									}
									else
									{
										PosDevPoint.x = (TriangleTopVertex.x + TriangleOrigin.x) / 2 -
											((TriangleOrigin.x - TriangleTopVertex.x)*color_deviation) / (NUM_INTEN1 - 1);
										PosDevPoint.y = (TriangleTopVertex.y + TriangleOrigin.y) / 2 -
											((TriangleOrigin.y - TriangleTopVertex.y)*color_deviation) / (NUM_INTEN1 - 1);
										dc.MoveTo(TriangleBaseEnd);
										dc.MoveTo(TriangleBaseEnd);
									}
								}
								dc.LineTo(PosDevPoint);
								DevScalePoint.x = LineCenter.x + PosPeak*StepDev;
								dc.Ellipse(DevScalePoint.x - CircleSize, DevScalePoint.y - CircleSize,
									DevScalePoint.x + CircleSize, DevScalePoint.y + CircleSize);
								dc.Rectangle(DevScalePoint.x - 2, DevScalePoint.y - (PMFr*ChartLength) / 16 - 2,
									DevScalePoint.x + 2, DevScalePoint.y - 2);
								DevScalePoint.x = LineCenter.x + (int)(Center_of_mass_point*((float)StepDev));
								dc.Ellipse(DevScalePoint.x - CircleSize - 1, DevScalePoint.y - CircleSize - 1 + 4,
									DevScalePoint.x + CircleSize + 1, DevScalePoint.y + CircleSize + 4 + 1);
							}

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

							BluePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
							BlueBrush.CreateSolidBrush(RGB(0, 0, 255));
							PtrOldBrush = dc.SelectObject(&BlueBrush);
							PtrOldPen = dc.SelectObject(&BluePen);
							dc.Ellipse(TriangleOrigin.x - CircleSize, TriangleOrigin.y - CircleSize,
								TriangleOrigin.x + CircleSize, TriangleOrigin.y + CircleSize);
							if (GGBorGGR)
							{
								if (num_intensity>31)
								{
									ZeroPoint.x = TriangleTopVertex.x + (TriangleBaseEnd.x - TriangleTopVertex.x) / 2;
									ZeroPoint.y = TriangleTopVertex.y + (TriangleBaseEnd.y - TriangleTopVertex.y) / 2;
								}
								else
								{
									ZeroPoint.x = TriangleTopVertex.x + (TriangleOrigin.x - TriangleTopVertex.x) / 2;
									ZeroPoint.y = TriangleTopVertex.y + (TriangleOrigin.y - TriangleTopVertex.y) / 2;
								}
							}
							else
							{
								if (num_intensity>31)
								{
									ZeroPoint.x = TriangleOrigin.x + (TriangleBaseEnd.x - TriangleOrigin.x) / 2;
									ZeroPoint.y = TriangleOrigin.y + (TriangleBaseEnd.y - TriangleOrigin.y) / 2;
								}
								else
								{
									ZeroPoint.x = TriangleTopVertex.x + (TriangleOrigin.x - TriangleTopVertex.x) / 2;
									ZeroPoint.y = TriangleTopVertex.y + (TriangleOrigin.y - TriangleTopVertex.y) / 2;
								}
							}
							if ((ZeroFract) && (num_intensity <= 31))
							{
								if (GGBorGGR)
								{
									dc.MoveTo(TriangleBaseEnd);
								}
								else
								{
									dc.MoveTo(TriangleBaseEnd);
								}
								dc.LineTo(ZeroPoint);
								DevScalePoint.x = LineCenter.x;
								dc.Ellipse(DevScalePoint.x - CircleSize, DevScalePoint.y - CircleSize,
									DevScalePoint.x + CircleSize, DevScalePoint.y + CircleSize);
								dc.Rectangle(DevScalePoint.x - 2, DevScalePoint.y - (ZeroFract*ChartLength) / 16 - 2,
									DevScalePoint.x + 2, DevScalePoint.y - 2);
							}

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

							YellowPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
							YellowBrush.CreateSolidBrush(RGB(255, 255, 0));
							PtrOldPen = dc.SelectObject(&YellowPen);
							PtrOldBrush = dc.SelectObject(&YellowBrush);
							if ((ZeroFract) && (num_intensity>31))
							{
								if (GGBorGGR)
								{
									dc.MoveTo(TriangleOrigin);
								}
								else
								{
									dc.MoveTo(TriangleTopVertex);
								}
								dc.LineTo(ZeroPoint);
								DevScalePoint.x = LineCenter.x;
								dc.Ellipse(DevScalePoint.x - CircleSize, DevScalePoint.y - CircleSize,
									DevScalePoint.x + CircleSize, DevScalePoint.y + CircleSize);
								dc.Rectangle(DevScalePoint.x - 2, DevScalePoint.y - (ZeroFract*ChartLength) / 16 - 2,
									DevScalePoint.x + 2, DevScalePoint.y - 2);
							}

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

							//PeakColor1=RGB(226,226,226);
							HuePen.CreatePen(PS_SOLID, 1, PeakColor1);
							HueBrush.CreateSolidBrush(PeakColor1);
							PtrOldPen = dc.SelectObject(&HuePen);
							PtrOldBrush = dc.SelectObject(&HueBrush);
							ColorPoint.x = CenterPoint.x / 2;
							ColorPoint.y = TriangleTopVertex.y + (CenterPoint.y - TriangleTopVertex.y) / 2;
							dc.Rectangle(ColorPoint.x - 10, ColorPoint.y - 10, ColorPoint.x + 10, ColorPoint.y + 10);

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);
							//PeakColor2=RGB(192,192,192);
							HuePen1.CreatePen(PS_SOLID, 1, PeakColor2);
							HueBrush1.CreateSolidBrush(PeakColor2);
							PtrOldPen = dc.SelectObject(&HuePen1);
							PtrOldBrush = dc.SelectObject(&HueBrush1);

							ColorPoint.y -= 30;
							dc.Rectangle(ColorPoint.x - 10, ColorPoint.y - 10, ColorPoint.x + 10, ColorPoint.y + 10);

							dc.SelectObject(PtrOldPen);
							dc.SelectObject(PtrOldBrush);

						}
					}
					dc.SelectObject(PtrOldFont);
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
BOOL

CVizStripView::CalculateIntervalCharacteristics(CPoint point)
{
	int Product;
	int Difference;
	int Coord;
	int IntBeg;
	int IntEnd;
	int int_count;
	int NumInt;
	int CoordY;
	int PreNumRatio;
	int Dimension;

	pApp = (CColorVisionApp *)AfxGetApp();

	StripNumber = pApp->NumberStripClicked;

	HorizVert = CurrentStrip[StripNumber].HorizontalVertical;

	if (HorizVert == 1)
	{
		Dimension = CurrentStrip[StripNumber].DimY;
	}
	else
	{
		Dimension = CurrentStrip[StripNumber].DimX;
	}
	Coord = point.x - xBase;
	PreNumRatio = Coord / xIncr;
	Product = PreNumRatio*xIncr;
	Difference = Coord - Product;
	if (Difference>xIncr / 2)
	{
		PreNumRatio += 1;
	}
	if ((PreNumRatio >= NumLevels) || (PreNumRatio<0))
	{
		return FALSE;
	}

	if (StripRepresentationType == 1)
	{
		NumInt = CurrentStrip[StripNumber].IntAllInform[PreNumRatio].num_of_int;
	}
	if (StripRepresentationType == 2)
	{
		NumInt = CurrentStrip[StripNumber].IntAllInformGray[PreNumRatio].num_of_int;
	}
	if (!NumInt)
	{
		return FALSE;
	}
	NumRatio = PreNumRatio;
	CoordY = (yMax - point.y - yBase) / yIncr;
	NumInterval = -1;
	for (int_count = 0; int_count<NumInt; int_count++)
	{
		if (StripRepresentationType == 1)
		{
			IntBeg = CurrentStrip[StripNumber].IntAllInform[NumRatio].BegInt[int_count];
			IntEnd = CurrentStrip[StripNumber].IntAllInform[NumRatio].EndInt[int_count];
			if (Dimension>320)
			{
				IntBeg = IntBeg / 2;
				IntEnd = IntEnd / 2;
			}
		}

		if (StripRepresentationType == 2)
		{
			IntBeg = CurrentStrip[StripNumber].IntAllInformGray[NumRatio].BegInt[int_count];
			IntEnd = CurrentStrip[StripNumber].IntAllInformGray[NumRatio].EndInt[int_count];
			if (Dimension>320)
			{
				IntBeg = IntBeg / 2;
				IntEnd = IntEnd / 2;
			}
		}
		if ((CoordY >= IntBeg) && (CoordY <= IntEnd))
		{
			NumInterval = int_count;
			break;
		}
	}
	if (NumInterval<0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
