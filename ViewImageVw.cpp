//
//
//
//
//





#include "stdafx.h"


 
#include "ColorVision.h"
#include "ViewImageDoc.h"
#include "ViewImageVw.h"


#include <math.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CViewImageVw

IMPLEMENT_DYNCREATE(CViewImageVw, CScrollView)

static int CoorHuPoints[16] = { 7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183, 199, 215, 231, 247 };


CViewImageVw::CViewImageVw()
{
	whiteRoadMarkingPen.CreatePen(PS_SOLID, 3, RGB(50, 50, 200));
	m_Dragging = 0;

	m_HArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	 
	WindowShift.x = 10;
	WindowShift.y = 20;
	
	 
	ImageIsSegmented = FALSE;
	AreaWasClicked = FALSE;
	SectInform = NULL;
	
	pApp = (CColorVisionApp *)AfxGetApp();
	ImageRepresentationType = pApp->ImageRepresentationType;
	
	if (ImageRepresentationType == GRAYSCALE)
	{
		strTitle = "Grayscale";
	} 
}



CViewImageVw::~CViewImageVw()
{
	pApp = (CColorVisionApp *)AfxGetApp();
	if (ImageRepresentationType == 1)
	{
		pApp->m_GrayScaleOpened = FALSE;
		pApp->ImageRepresentationType = 0;
	}
	if (ImageRepresentationType == 2)
	{
		//pApp->m_GrayScaleOpened=FALSE;
		pApp->ImageRepresentationType = 0;
	}
}



BEGIN_MESSAGE_MAP(CViewImageVw, CScrollView)
	//{{AFX_MSG_MAP(CViewImageVw)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CViewImageVw::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	 
	pApp = (CColorVisionApp *)AfxGetApp();
	  
	WMHeight = (pApp->pm_BitmapApp)->bmHeight;
	WMWidth = (pApp->pm_BitmapApp)->bmWidth;

	ImageLoaded = pApp->m_ImageIsLoaded;
	CameraImageLoaded = pApp->m_VideoCameraIsLoaded;
	HorizVert = pApp->HorizontalVertical;

	CSize sizeTotal; 

	// TODO: calculate the total size of this view
	if (ImageLoaded || CameraImageLoaded)
	{
		sizeTotal.cx = WMWidth;
		sizeTotal.cy = WMHeight;
		sizeTotal.cx += 2 * WindowShift.x;
		sizeTotal.cy += 2 * WindowShift.y;
	}
	else
	{
		sizeTotal.cx = 640;
		sizeTotal.cy = 480;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);
	pDoc = GetDocument();
	
	if (ImageRepresentationType == 1)
	{
		pDoc->SetTitle((LPCTSTR)strTitle);
		pApp->pDocGrayscaleImage = pDoc;
	}

	if (ImageRepresentationType == 0)
	{
		pApp->pDocColorImage = pDoc;
	}
}



void CViewImageVw::OnDraw(CDC* pDC)
{
	POINT OrPoint;
	POINT EndPoint; 

	POINT NewOrPoint;
	POINT NewEndPoint;

	POINT CnPoint;
	POINT New1CnPoint;
	POINT New2CnPoint;
	 
	int LineStart;
	int SideHue;
	int NumSideHues;
	int SideTriangle;
	
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
	int StripNumber;

	int colorBunchNum;
	int grayBunchNum;
	
	int Beg_bunch;
	int End_bunch;
	
	int bunch_average_hue;
	int bunch_average_sat;
	int bunch_average_gray;
	
	int old_col_number;
	int old_col_num;
	int bunch_number;
	int bunch_number1;
	int coun_bunch;
	int* blocking_bunch;
	int* OldNum;
	int HorizVertic;
	int left_contrast;
	int left_edge_point;
	int right_contrast;
	int right_edge_point;
	int label_sign;

	int num_fibre;
	int beg;
	int end;
	int num_bunch;
	int Dim_x;
	int Dim_y;
	int StripWidth;
	int StripWidthPrev;
	int StrWidthPrev;
	int StrWidth;
	int StripWidth1;
	int SectNumber;
	int StripWidthPrev1;
	int bunch_occurrence;
	int video_limit;
	int sky_index;
	int left_green_boun_bunch;
	int right_green_boun_bunch;
	int length_of_vert_line;
	
	int line_member;
	int line_member_old;
	int line_member_old_beg;
	int line_member_old_end;
	
	int first_vert_line_strip;
	int coun_strip_v;
	int NumberVLines;
	
	int SignalConnectedLine;
	int SignalConnectedLineRight;
	
	int CarInFront;
	int CarInFrontRight;

	CPen* WhitePen;
	CPen* PtrOldPen;
	CPen* POldPen1;
	CPen* pHuePen3;

	CPoint BeginPoint;
 	BOOL VertFind;

	BOOL IdenCard = TRUE;
	BOOL SkyFind  = FALSE;
	BOOL GreenFind = FALSE;
	CPen pen;
	CPen* pHuePen;
	CPen* POldPen;

	COLORREF PeakColor1;
	COLORREF PeakColor2;
	sky_index = 0;
	CPoint ShiftDimensions;
	bunch_occurrence = 0;
	
	pApp = (CColorVisionApp *)AfxGetApp();
	
	NumStrips   = pApp->NumberOfStrips;
	StripNumber = pApp->NumberStripClicked;
	
	ImageIsSegmented       = pApp->m_ImageSegmented;
	m_Video_ImageSegmented = pApp->m_Video_ImageSegmented;
	 
	if (ImageRepresentationType == COLOR)
	{
		pDoc = GetDocument();
		if (pDoc)
		{//pDoc
			if (pDoc->m_DibDoc)
			{
				pDoc->m_DibDoc->Draw(pDC);
			}
			if (pDoc->m_DibTgaDoc)
			{
				pDoc->m_DibTgaDoc->Draw(pDC);
			}
			 
			// Show clicked point characteristics
			if (ImageIsSegmented && (pApp->m_StripColorRepresentation || pApp->m_ColorBunchRepresentation || (pApp->m_StripGrayRepresentation)
				|| (pApp->m_GrayScaleOpened)) && AreaWasClicked)
			{//condlog

				NumStrips    = pApp->ColorImageProcess->NumStrips;
				HorizVert    = pApp->ColorImageProcess->HorizontalVertical;
				StrWidthPrev = pApp->ColorImageProcess->CurStrip[0].StripWidthPrev;
				
				if (HorizVert)
				{
					OrPoint.y = WMHeight + WindowShift.y - 1;
					for (LineStart = 0; LineStart<NumStrips; LineStart++)
					{
						OrPoint.x = WindowShift.x + (StrWidthPrev)*LineStart;
						pDC->MoveTo(OrPoint);
						EndPoint.x = OrPoint.x;
						EndPoint.y = OrPoint.y + 12;
						pDC->LineTo(EndPoint);
					} 
				}
				else
				{
					OrPoint.x = WMWidth + WindowShift.x;

					for (LineStart = 0; LineStart<NumStrips; LineStart++)
					{
						//StrWidth = pApp->ColorImageProcess->CurStrip[LineStart].StripWidth;
						OrPoint.y = WMHeight + WindowShift.y - (StrWidthPrev)*LineStart;
						pDC->MoveTo(OrPoint);
						EndPoint.y = OrPoint.y;
						EndPoint.x = OrPoint.x + 12;
						pDC->LineTo(EndPoint);
					}
				} 
			}//condlog

			  

			if (ImageIsSegmented && pApp->m_ColorSectionsRepresentation) 
			{//iseg 
				if (1 == pApp->m_pColorSectDialog->radioBtnColorSection.GetCheck())
				{
					SectNumber = pApp->m_pColorSectDialog->m_SectionNumber;
					SkyFind = pApp->m_FindSky;
					GreenFind = pApp->m_FindGreen;

					video_limit = pApp->VideoInputLimit;

					if (GreenFind && (!video_limit))
					{//grf
						if (!SectNumber)
						{
							COLORREF PeakColor5;
							NScoor1 = 255;
							NScoor2 = 0;
							NScoor3 = 0;
							PeakColor5 = RGB(NScoor1, NScoor2, NScoor3);
							pHuePen3 = new CPen(PS_SOLID, 5, PeakColor5);
							POldPen1 = pDC->SelectObject(pHuePen3);
							for (int coun_strip1 = 0; coun_strip1 < NumStrips; coun_strip1++) //draw color bunches
							{//strip_loop
								old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip1].NumberOfColoredIntervals;
								bunch_number1 = pApp->ColorImageProcess->ColorInt[coun_strip1].RefinedNumberOfBunches;
								old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip1].NumberOfColoredIntervals;

								StripWidth1 = pApp->ColorImageProcess->CurStrip[coun_strip1].StripWidth;
								StripWidthPrev1 = pApp->ColorImageProcess->CurStrip[coun_strip1].StripWidthPrev;

								left_green_boun_bunch = pApp->ColorImageProcess->LeftGreenBoundaryBunch[coun_strip1];
								right_green_boun_bunch = pApp->ColorImageProcess->RightGreenBoundaryBunch[coun_strip1];

								if (left_green_boun_bunch > 0)
								{
									left_green_boun_bunch--;
								}
								else
								{
									left_green_boun_bunch = -1;
								}
								if (right_green_boun_bunch > 0)
								{
									right_green_boun_bunch--;
								}
								else
								{
									right_green_boun_bunch = -1;
								}
								for (int coun_bunch2 = 0; coun_bunch2 < bunch_number1; coun_bunch2++) //draw color bunches
								{//bunch_loop
									old_col_num = pApp->ColorImageProcess->ColorInt[coun_strip1].old_bunch_number[coun_bunch2];
									if (old_col_num < old_col_number)
									{//restrict_bn
										Beg_bunch =
											pApp->ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->BegInterv[old_col_num];
										End_bunch =
											pApp->ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->EndInterv[old_col_num];
										bunch_occurrence = pApp->ColorImageProcess->ColorInt[coun_strip1].visible_bunches[old_col_num];

										HorizVert = pApp->HorizontalVertical;

										if ((left_green_boun_bunch >= 0) || (right_green_boun_bunch >= 0))
										{//lgb||rgb
											if ((left_green_boun_bunch == old_col_num) && (left_green_boun_bunch >= 0))
											{//ldb=
												if (HorizVert)
												{//horvert
													OrPoint.y = (WMHeight - End_bunch) + WindowShift.x;
													OrPoint.x = (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1 + WindowShift.y;
													pDC->MoveTo(OrPoint);
													EndPoint.x = OrPoint.x - min(5, StripWidth1 / 2);
													EndPoint.y = OrPoint.y;
													pDC->LineTo(EndPoint);
												}//horvert
												else
												{//ehorvert
													OrPoint.x = End_bunch + WindowShift.x;
													OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1 + WindowShift.y;
													pDC->MoveTo(OrPoint);
													EndPoint.x = OrPoint.x;
													EndPoint.y = OrPoint.y - min(5, StripWidth1 / 2);//!
													pDC->LineTo(EndPoint);
												}//ehorvert	
											}//ldb=
											if ((right_green_boun_bunch == old_col_num) && (right_green_boun_bunch >= 0))
											{//rgb=
												if (HorizVert)
												{//horvert

													OrPoint.y = (WMHeight - Beg_bunch);
													OrPoint.x = (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													EndPoint.x = OrPoint.x + WindowShift.x;
													EndPoint.y = WMHeight - Beg_bunch + WindowShift.y;
													pDC->MoveTo(EndPoint);
													NewOrPoint.x = EndPoint.x - min(5, StripWidth1 / 2);//!
													NewOrPoint.y = EndPoint.y;
													pDC->LineTo(NewOrPoint);
												}//horvert
												else
												{//ehorvert
													OrPoint.x = Beg_bunch;
													OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													EndPoint.x = Beg_bunch + WindowShift.x;
													EndPoint.y = OrPoint.y + WindowShift.y;
													NewEndPoint = EndPoint;
													pDC->MoveTo(EndPoint);
													NewOrPoint.x = EndPoint.x;
													NewOrPoint.y = EndPoint.y - min(5, StripWidth1 / 2);//!
													pDC->LineTo(NewOrPoint);
												}//ehorvert	
											}//rgb=

										}//lgb||rgb
									}//restrict_bn

								}//bunch_loop
							}//strip_loop
							pDC->SelectObject(POldPen1);
							delete pHuePen3;
						}
					}//grf
					CPen* pHuePen5;
					COLORREF PeakColor7;

					NScoor1 = 0;
					NScoor2 = 255;
					NScoor3 = 255;

					PeakColor7 = RGB(NScoor1, NScoor2, NScoor3);
					pHuePen5 = new CPen(PS_SOLID, 4, PeakColor7);
					POldPen1 = pDC->SelectObject(pHuePen5);
					VertFind = pApp->ColorImageProcess->VertFinding;
					if ((VertFind) && (!video_limit))
					{//vertfind	
						NumberVLines = pApp->ColorImageProcess->NumberOfVertLines;
						HorizVert = pApp->HorizontalVertical;

						for (int vert_number = 0; vert_number < NumberVLines; vert_number++) //draw vertical lines
						{//vert_loop
							length_of_vert_line = pApp->ColorImageProcess->VerticalLinesLength[vert_number];
							//length_of_vert_line=0;
							SignalConnectedLine = pApp->ColorImageProcess->ConnectedVertLines[vert_number];
							SignalConnectedLineRight = pApp->ColorImageProcess->ConnectedVertLinesRight[vert_number];
							CarInFront = pApp->ColorImageProcess->ConnectedLeftBounVert[vert_number];
							CarInFrontRight = pApp->ColorImageProcess->RightBounVert[vert_number];
							if (!length_of_vert_line)
							{
								goto K;
							}
							/*if((length_of_vert_line>0)&&((SignalConnectedLine>0)||(SignalConnectedLineRight>0)||
							(CarInFront>0)))*/
							if ((length_of_vert_line >= 3) && ((SignalConnectedLine > 0) || (SignalConnectedLineRight > 0) ||
								(CarInFrontRight > 0) || (CarInFront > 0)))
								//if((length_of_vert_line>4)&&(CarInFront>0))
							{//length>
								first_vert_line_strip = pApp->ColorImageProcess->VertLineFirstStrip[vert_number];
								if (first_vert_line_strip > 0)
								{
									first_vert_line_strip -= 1;
								}
								else
								{
									goto L;
								}
								for (int vert_count = 0; vert_count < length_of_vert_line; vert_count++) //draw particular vert line
								{//line_loop
									line_member = pApp->ColorImageProcess->VerticalContrastCurves[24 * vert_number + vert_count];
									if (!line_member)
									{
										break;
									}
									if (line_member > 0)
									{//linemember>
										line_member -= 1;
										coun_strip_v = first_vert_line_strip + vert_count;
										StripWidth1 = pApp->ColorImageProcess->CurStrip[coun_strip_v].StripWidth;
										StripWidthPrev1 = pApp->ColorImageProcess->CurStrip[coun_strip_v].StripWidthPrev;
										line_member_old =
											pApp->ColorImageProcess->ColorInt[coun_strip_v].old_ordered_bunch_number[line_member];
										line_member_old_beg =
											pApp->ColorImageProcess->ColorInt[coun_strip_v].ColoredIntervalsStructure->BegInterv[line_member_old];
										line_member_old_end =
											pApp->ColorImageProcess->ColorInt[coun_strip_v].ColoredIntervalsStructure->EndInterv[line_member_old];
										if (HorizVert)
										{//horvert
											OrPoint.y = (WMHeight - line_member_old_end) + WindowShift.x;
											OrPoint.x = (StripWidthPrev1 * coun_strip_v + StripWidth1 / 2) - 1 + WindowShift.y;
											pDC->MoveTo(OrPoint);
											EndPoint.x = OrPoint.x - min(5, StripWidth1 / 2);
											EndPoint.y = OrPoint.y;

											pDC->LineTo(EndPoint);
										}//horvert
										else
										{//ehorvert
											OrPoint.x = line_member_old_end + WindowShift.x;
											OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip_v + StripWidth1 / 2) - 1 + WindowShift.y;
											pDC->MoveTo(OrPoint);
											EndPoint.x = OrPoint.x;
											EndPoint.y = OrPoint.y - min(5, StripWidth1 / 2);//!

											pDC->LineTo(EndPoint);
										}//ehorvert	
									}//linemember>
								}//line_loop
							}//length>
						}//vert_loop
					K:;
					}//vertfind
					pDC->SelectObject(POldPen1);
					delete pHuePen5;

					if (SkyFind)
					{
						sky_index = pApp->ColorImageProcess->SkyGreenComponents[SectNumber];
						SectNumber = pApp->m_pColorSectDialog->m_SectionNumber;
						if ((!video_limit) && (!sky_index))
						{
							IdenCard = FALSE;
						}
					}
					int NumSect = pApp->ColorImageProcess->ColorSection->Number_of_sections;

					Dim_x = pApp->ColorImageProcess->DimX;
					Dim_y = pApp->ColorImageProcess->DimY;

					if ((!SectNumber) && SkyFind && (!video_limit))
					{
						goto L;
					}
					if ((SectNumber >= 0) && (IdenCard))
					{//sn>=0

						if (SectNumber < NumSect)
						{

							Sect1 = &(pApp->ColorImageProcess->ColorSection->DescrSec[pApp->m_pColorSectDialog->m_SectionNumber]);
						}
						else
						{
							Sect1 = &(pApp->ColorImageProcess->ColorSection->DescrSec[0]);
						}
						Bunches = pApp->ColorImageProcess->ColorInt;
						CurrentStrip = pApp->ColorImageProcess->CurStrip;

						HorizVertic = pApp->ColorImageProcess->HorizontalVertical;
						SectInform = pApp->ColorImageProcess->ColorSection;

						WhitePen = new CPen;
						if ((sky_index == 1) && (SkyFind))
						{
							WhitePen->CreatePen(PS_SOLID, 3, RGB(10, 10, 10));
						}
						else
						{
							WhitePen->CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
						}
						PtrOldPen = pDC->SelectObject(WhitePen);
						for (num_fibre = Sect1->base_first; num_fibre <= Sect1->base_last; num_fibre++)
						{//f_loop
							num_bunch = Sect1->location_of_section[num_fibre];
							if (num_bunch > 0)
							{//nb>0
								num_bunch--;
								num_bunch =
									Bunches[num_fibre].old_bunch_number[num_bunch];
								beg =
									Bunches[num_fibre].ColoredIntervalsStructure->BegInterv[num_bunch];
								end =
									Bunches[num_fibre].ColoredIntervalsStructure->EndInterv[num_bunch];
								left_edge_point = pApp->ColorImageProcess->SectionTraceLeft[num_fibre * MAX_COL_INT + num_bunch];
								right_edge_point = pApp->ColorImageProcess->SectionTraceRight[num_fibre * MAX_COL_INT + num_bunch];
								StripWidth = CurrentStrip[num_fibre].StripWidth;
								StripWidthPrev = CurrentStrip[num_fibre].StripWidthPrev;
								if (HorizVertic == 1)
								{
									BeginPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
									BeginPoint.y = Dim_y - beg - 1 + WindowShift.y;
									EndPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
									EndPoint.y = Dim_y - end - 1 + WindowShift.y;

								}
								else
								{
									BeginPoint.x = beg + WindowShift.x;
									BeginPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
									EndPoint.x = end + WindowShift.x;
									EndPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
								}

								pDC->MoveTo(BeginPoint);
								pDC->LineTo(EndPoint);

								if (left_edge_point > 1000)
								{
									pDC->Ellipse(BeginPoint.x - min(5, StripWidth / 2), BeginPoint.y - min(5, StripWidth / 2),
										BeginPoint.x + min(5, StripWidth / 2), BeginPoint.y + min(5, StripWidth / 2));
								}
								if (right_edge_point > 1000)
								{
									pDC->Ellipse(EndPoint.x - min(5, StripWidth / 2), EndPoint.y - min(5, StripWidth / 2),
										EndPoint.x + min(5, StripWidth / 2), EndPoint.y + min(5, StripWidth / 2));
								}


							}//nb>0
						}//f_loop
						pDC->SelectObject(PtrOldPen);
						delete WhitePen;
					L:;
						Bunches = pApp->ColorImageProcess->ColorInt;
						CurrentStrip = pApp->ColorImageProcess->CurStrip;

						HorizVertic = pApp->ColorImageProcess->HorizontalVertical;
						SectInform = pApp->ColorImageProcess->ColorSection;
						if ((SkyFind) && (!SectNumber) && (!video_limit))
						{//sfsn=ns 
							CPen pen(PS_SOLID, 3, RGB(10, 10, 10));
							PtrOldPen = pDC->SelectObject(&pen);
							for (int num_sect = 0; num_sect < NumSect; num_sect++)
							{//sect_loop
								sky_index = pApp->ColorImageProcess->SkyGreenComponents[num_sect];

								if (sky_index == 1)
								{//sky_log_cond
									Sect1 = &(pApp->ColorImageProcess->ColorSection->DescrSec[num_sect]);
									for (num_fibre = Sect1->base_first; num_fibre <= Sect1->base_last; num_fibre++)
									{//fn_loop
										num_bunch = Sect1->location_of_section[num_fibre];
										if (num_bunch > 0)
										{//nb>0
											num_bunch--;
											num_bunch = Bunches[num_fibre].old_bunch_number[num_bunch];

											beg = Bunches[num_fibre].ColoredIntervalsStructure->BegInterv[num_bunch];
											end = Bunches[num_fibre].ColoredIntervalsStructure->EndInterv[num_bunch];

											StripWidth = CurrentStrip[num_fibre].StripWidth;
											StripWidthPrev = CurrentStrip[num_fibre].StripWidthPrev;

											if (HorizVertic == 1)
											{
												BeginPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
												BeginPoint.y = Dim_y - beg - 1 + WindowShift.y;
												EndPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
												EndPoint.y = Dim_y - end - 1 + WindowShift.y;

											}
											else
											{
												BeginPoint.x = beg + WindowShift.x;
												BeginPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
												EndPoint.x = end + WindowShift.x;
												EndPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
											}

											pDC->MoveTo(BeginPoint);
											pDC->LineTo(EndPoint);
										}//nb>0
									}//fn_loop
								}//sky_log_cond
							}//sect_loop
							//pDC->SelectObject(PtrOldPen);
							//delete WhitePen;
						}//sfsn=ns
					}//sn>=0
				}
				else if (1 == pApp->m_pColorSectDialog->radioBtnMarking.GetCheck())
				{ 
					pDC->SelectObject(&whiteRoadMarkingPen);
					pDC->MoveTo(CPoint(200, 100));
					pDC->LineTo(CPoint(400, 100));
				
					int marking_number = pApp->ColorImageProcess->ColorSection->Number_of_markings;
				
					int yellow_marking_number = pApp->ColorImageProcess->ColorSection->Number_of_yellow_markings;
					int number_of_yellow_marking_left = pApp->ColorImageProcess->ColorSection->Number_of_yellow_markings_left;
					int number_of_yellow_marking_right = pApp->ColorImageProcess->ColorSection->Number_of_yellow_markings_right;
					int white_marking_number = pApp->ColorImageProcess->ColorSection->Number_of_white_markings;
					int number_of_white_marking_left = pApp->ColorImageProcess->ColorSection->Number_of_white_markings_left;
					int number_of_white_marking_right = pApp->ColorImageProcess->ColorSection->Number_of_white_markings_right;
				
					int NumSect = yellow_marking_number;
					/*
					Bunches = pApp->ColorImageProcess->ColorInt;
					CurrentStrip = pApp->ColorImageProcess->CurStrip;

					HorizVertic = pApp->ColorImageProcess->HorizontalVertical;
					SectInform = pApp->ColorImageProcess->ColorSection;

					WhitePen = new CPen;
					WhitePen->CreatePen(PS_SOLID, 3, RGB(255, 100, 0));

					Sect1 = &(pApp->ColorImageProcess->ColorSection->DescrMarking[pApp->m_pColorSectDialog->m_MarkingNumber]);
					  
					pDC->SelectObject(WhitePen);

					for (num_fibre = Sect1->base_first; num_fibre <= Sect1->base_last; num_fibre++)
					{ 
						num_bunch = Sect1->location_of_section[num_fibre];
						if (num_bunch > 0)
						{ 
							num_bunch--; 
							  
							num_bunch = Bunches[num_fibre].old_bunch_number[num_bunch]; 
							beg = Bunches[num_fibre].ColoredIntervalsStructure->BegInterv[num_bunch];
							end = Bunches[num_fibre].ColoredIntervalsStructure->EndInterv[num_bunch];
							if ((video_limit != 2) && (video_limit != 3))
							{
								left_edge_point = pApp->ColorImageProcess->SectionTraceLeft[num_fibre * MAX_COL_INT + num_bunch];
								right_edge_point = pApp->ColorImageProcess->SectionTraceRight[num_fibre * MAX_COL_INT + num_bunch];
							}
							StripWidth = CurrentStrip[num_fibre].StripWidth;
							StripWidthPrev = CurrentStrip[num_fibre].StripWidthPrev;
							if (HorizVertic == 1)
							{
								BeginPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
								BeginPoint.y = Dim_y - beg - 1 + WindowShift.y;
								EndPoint.x = num_fibre * StripWidthPrev + StripWidth / 2 + WindowShift.x;
								EndPoint.y = Dim_y - end - 1 + WindowShift.y;

							}
							else
							{
								BeginPoint.x = beg + WindowShift.x;
								BeginPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
								EndPoint.x = end + WindowShift.x;
								EndPoint.y = Dim_y - (num_fibre * StripWidthPrev + StripWidth / 2) + WindowShift.y;
							}

							pDC->MoveTo(BeginPoint);
							pDC->LineTo(EndPoint);
							if ((video_limit != 2) && (video_limit != 3))
							{
								if (left_edge_point > 1000)
								{
									pDC->Ellipse(BeginPoint.x - min(5, StripWidth / 2), BeginPoint.y - min(5, StripWidth / 2),
										BeginPoint.x + min(5, StripWidth / 2), BeginPoint.y + min(5, StripWidth / 2));
								}
								if (right_edge_point > 1000)
								{
									pDC->Ellipse(EndPoint.x - min(5, StripWidth / 2), EndPoint.y - min(5, StripWidth / 2),
										EndPoint.x + min(5, StripWidth / 2), EndPoint.y + min(5, StripWidth / 2));
								}
							} 
						} 
					}  */


					// TODO: show marking based on grayscale bursts
					/* 
					for (UINT8 markingNum = 0U; 
						pApp->ColorImageProcess->markings[markingNum].isValid; 
						markingNum++)
					{
						Marking marking = pApp->ColorImageProcess->markings[markingNum];
						UINT8 begStrip = marking.begStrip;
						UINT8 endStrip = marking.endStrip;
						for (UINT8 stripNum = begStrip; stripNum <= endStrip; stripNum++)
						{
							UINT8 bunchNum = marking.bunchNumbers[stripNum];
							GrayBunch burst = CurrentStrip[stripNum].bursts[bunchNum]; 
							pDC->MoveTo(CPoint(burst.beg, stripNum * 10));
							pDC->LineTo(CPoint(burst.end, stripNum * 10));
						}
					} */
				}
			}//iseg
		}
	}

	else if (ImageRepresentationType == GRAYSCALE)
	{
		ShiftDimensions = GetDeviceScrollPosition(); 

		video_limit = pApp->VideoInputLimit;
		pDoc        = GetDocument();

		if (pDoc)
		{
			if (pDoc->m_DibGrayScaleDoc)
			{
				pDoc->m_DibGrayScaleDoc->Draw(pDC);
			}

			BOOL hide;//last_cor01.13.19
			int WhiteYellowMarkingLabel;//last_cor01.13.19

			if (ImageIsSegmented && (pApp->m_ColorBunchRepresentation || pApp->m_GrayScaleOpened))
			{ 
				bunch_number = pApp->ColorImageProcess->ColorInt[StripNumber].RefinedNumberOfBunches;

				if (bunch_number == 0)
				{
					return;
				}

				NumStrips = pApp->ColorImageProcess->NumStrips;
				old_col_number = pApp->ColorImageProcess->ColorInt[StripNumber].NumberOfColoredIntervals;
				CurrentStrip = pApp->ColorImageProcess->CurStrip;
				
				StripWidth = CurrentStrip[StripNumber].StripWidth;
				StripWidthPrev = CurrentStrip[StripNumber].StripWidthPrev;

				if (1 == pApp->m_pBunchCountDialog->radioBtnColorBunch.GetCheck())
				{
					colorBunchNum = pApp->m_pBunchCountDialog->m_colorBunchNum;

					if (colorBunchNum == 62) // in one strip
					{
						for (coun_bunch = 0; coun_bunch < bunch_number; coun_bunch++) //draw color bunches
						{
							WhiteYellowMarkingLabel = pApp->ColorImageProcess->ColorInt[StripNumber].MarkingSignal[coun_bunch];
							old_col_num             = pApp->ColorImageProcess->ColorInt[StripNumber].old_bunch_number[coun_bunch];
							
							if ((old_col_num < old_col_number) && ((video_limit == 1) ||
								((!video_limit) && (WhiteYellowMarkingLabel >= 2))))
							{
								bunch_average_hue =
									pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageHue[old_col_num];
								bunch_average_sat =
									pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageSat[old_col_num];
								bunch_average_gray =
									pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageGray[old_col_num];
								Beg_bunch =
									pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->BegInterv[old_col_num];
								End_bunch =
									pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->EndInterv[old_col_num];

								bunch_occurrence = pApp->ColorImageProcess->ColorInt[StripNumber].visible_bunches[old_col_num];

								left_contrast = pApp->ColorImageProcess->ColorInt[StripNumber].left_continuation[old_col_num];
								right_contrast = pApp->ColorImageProcess->ColorInt[StripNumber].right_continuation[old_col_num];

								label_sign = pApp->ColorImageProcess->ColorInt[StripNumber].label_segments[old_col_num];

								NumSideHues = (NUM_HUES / 3);

								if (bunch_average_hue > 47)
								{
									bunch_average_hue -= 48;
								}

								SideTriangle = bunch_average_hue / NumSideHues;
								SideHue = bunch_average_hue - NumSideHues * SideTriangle;


								if (SideTriangle == 0)
								{
									Coor1 = 255 - CoorHuPoints[SideHue];
									Coor2 = CoorHuPoints[SideHue];
									Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
									Scoor2 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
									Scoor3 = (84 * (15 - bunch_average_sat)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev > bunch_average_gray)
									{

										NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
										NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
										NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
										NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
									Coor1 = 255 - CoorHuPoints[SideHue];
									Coor2 = CoorHuPoints[SideHue];
									Scoor1 = (84 * (15 - bunch_average_sat)) / 15;
									Scoor2 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
									Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev > bunch_average_gray)
									{
										NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
										NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
										NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
										NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
									Coor1 = CoorHuPoints[SideHue];
									Coor2 = 255 - CoorHuPoints[SideHue];
									Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
									Scoor2 = (84 * (15 - bunch_average_sat)) / 15;
									Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
									Imax = max(Scoor1, max(Scoor2, Scoor3));
									Scoor1 = (Scoor1 * 255) / Imax;
									Scoor2 = (Scoor2 * 255) / Imax;
									Scoor3 = (Scoor3 * 255) / Imax;
									PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
									GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
									GrayLev = GrayLev / 4;
									if (GrayLev > bunch_average_gray)
									{
										NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
										NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
										NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
										NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
								if (((bunch_average_gray <= 5) && (NScoor1 > NScoor2) && (NScoor1 > NScoor3)) ||
									((bunch_average_gray <= 3) && (bunch_average_sat <= 1)) ||
									(bunch_average_gray <= 2))
								{//last_cor13.11.1729.11.17						
									NScoor1 = 10;
									NScoor2 = 10;
									NScoor3 = 10;
								}
								else
								{
									if ((bunch_average_gray >= 58) && (bunch_average_sat <= 1))
									{//last_cor13.11.1729.11.17
										NScoor1 = min(min(NScoor1, NScoor2), NScoor3);
										NScoor2 = NScoor1;
										NScoor3 = NScoor1;
									}
								}
								OldNum = pApp->ColorImageProcess->ColorInt[StripNumber].OldNumbers;

								PeakColor1 = RGB(NScoor1, NScoor2, NScoor3); 
								pHuePen = new CPen(PS_SOLID, 3, PeakColor1); 
								POldPen = pDC->SelectObject(pHuePen);

								HorizVert = pApp->HorizontalVertical;
								if (HorizVert)
								{
									OrPoint.y = (WMHeight - Beg_bunch);
									if (bunch_occurrence > 0)
									{
										OrPoint.x = (StripWidthPrev * StripNumber + StripWidth / 2) - 1;
									}
									else
									{
										OrPoint.x = (StripWidthPrev * StripNumber + StripWidth / 2) + 3;
									}

									pDC->MoveTo(OrPoint);

									EndPoint.x = OrPoint.x;
									EndPoint.y = WMHeight - End_bunch;

									NewEndPoint = EndPoint;

									pDC->LineTo(EndPoint);

									if (right_contrast < 0)
									{
										pDC->MoveTo(EndPoint);
										NewOrPoint.x = EndPoint.x - min(5, StripWidth / 2);
										NewOrPoint.y = EndPoint.y;
										pDC->LineTo(NewOrPoint);
									}

									if (left_contrast < 0)
									{
										pDC->MoveTo(OrPoint);
										EndPoint.x = OrPoint.x - min(5, StripWidth / 2);
										EndPoint.y = OrPoint.y;
										pDC->LineTo(EndPoint);
									}

									CnPoint.x = OrPoint.x;
									CnPoint.y = OrPoint.y + (NewEndPoint.y - OrPoint.y) / 2;

									New1CnPoint.y = CnPoint.y;
									New2CnPoint.y = CnPoint.y;
									New1CnPoint.x = CnPoint.x - min(10, StripWidth / 2);
									New2CnPoint.x = CnPoint.x + min(10, StripWidth / 2);

									if ((label_sign >= 3) && (label_sign <= 10) || ((label_sign >= 13) && (label_sign <= 20)))
									{
										pDC->MoveTo(New1CnPoint);
										pDC->LineTo(New2CnPoint);
									}

								}
								else
								{
									OrPoint.x = Beg_bunch;
									if (bunch_occurrence > 0)
									{
										OrPoint.y = WMHeight - (StripWidthPrev * StripNumber + StripWidth / 2) - 1;
									}
									else
									{
										OrPoint.y = WMHeight - (StripWidthPrev * StripNumber + StripWidth / 2) + 3;
									}
									pDC->MoveTo(OrPoint);
									EndPoint.x = End_bunch;
									EndPoint.y = OrPoint.y;
									NewEndPoint = EndPoint;
									pDC->LineTo(EndPoint);
									OrPoint.y -= 1;
									EndPoint.y = OrPoint.y;
									pDC->MoveTo(OrPoint);
									pDC->LineTo(EndPoint);
									OrPoint.y += 2;
									EndPoint.y = OrPoint.y;
									pDC->MoveTo(OrPoint);
									pDC->LineTo(EndPoint);
									if (right_contrast < 0)
									{
										pDC->MoveTo(EndPoint);
										NewOrPoint.x = EndPoint.x;
										NewOrPoint.y = EndPoint.y - min(5, StripWidth / 2);
										pDC->LineTo(NewOrPoint);
									}
									if (left_contrast < 0)
									{
										pDC->MoveTo(OrPoint);
										EndPoint.x = OrPoint.x;
										EndPoint.y = OrPoint.y - min(5, StripWidth / 2);
										pDC->LineTo(EndPoint);
									}
									CnPoint.y = OrPoint.y;
									CnPoint.x = OrPoint.x + (NewEndPoint.x - OrPoint.x) / 2;
									New1CnPoint.x = CnPoint.x;
									New2CnPoint.x = CnPoint.x;
									New1CnPoint.y = CnPoint.y - min(10, StripWidth / 2);
									New2CnPoint.y = CnPoint.y + min(10, StripWidth / 2);
									if ((label_sign >= 3) && (label_sign <= 10) || ((label_sign >= 13) && (label_sign <= 20)))
									{
										pDC->MoveTo(New1CnPoint);
										pDC->LineTo(New2CnPoint);
									}
								}

								pDC->SelectObject(POldPen);

								delete pHuePen;
							}

						}
						return;
					}

					// over all strips
					if (colorBunchNum == 63)
					{//BN63
						CPen* pHuePen1;

						COLORREF PeakColor3;
						COLORREF PeakColor4;
						for (int coun_strip = 0; coun_strip < NumStrips; coun_strip++) //draw color bunches
						{//strip_loop
							old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip].NumberOfColoredIntervals;
							bunch_number1 = pApp->ColorImageProcess->ColorInt[coun_strip].RefinedNumberOfBunches;
							old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip].NumberOfColoredIntervals;
							StripWidth1 = CurrentStrip[coun_strip].StripWidth;
							StripWidthPrev1 = CurrentStrip[coun_strip].StripWidthPrev;

							for (int coun_bunch1 = 0; coun_bunch1 < bunch_number1; coun_bunch1++) //draw color bunches
							{//bunch_loop
								WhiteYellowMarkingLabel =
									pApp->ColorImageProcess->ColorInt[coun_strip].MarkingSignal[coun_bunch1];
								old_col_num = pApp->ColorImageProcess->ColorInt[coun_strip].old_bunch_number[coun_bunch1];
								if ((old_col_num < old_col_number) && ((video_limit == 1) ||
									((!video_limit) && (WhiteYellowMarkingLabel >= 2))))
								{//restrict_bn
									bunch_average_hue =
										pApp->ColorImageProcess->ColorInt[coun_strip].ColoredIntervalsStructure->AverageHue[old_col_num];
									bunch_average_sat =
										pApp->ColorImageProcess->ColorInt[coun_strip].ColoredIntervalsStructure->AverageSat[old_col_num];
									bunch_average_gray =
										pApp->ColorImageProcess->ColorInt[coun_strip].ColoredIntervalsStructure->AverageGray[old_col_num];
									Beg_bunch =
										pApp->ColorImageProcess->ColorInt[coun_strip].ColoredIntervalsStructure->BegInterv[old_col_num];
									End_bunch =
										pApp->ColorImageProcess->ColorInt[coun_strip].ColoredIntervalsStructure->EndInterv[old_col_num];
									bunch_occurrence = pApp->ColorImageProcess->ColorInt[coun_strip].visible_bunches[old_col_num];
									left_contrast = pApp->ColorImageProcess->ColorInt[coun_strip].left_continuation[old_col_num];
									left_edge_point = pApp->ColorImageProcess->SectionTraceLeft[coun_strip * MAX_COL_INT + old_col_num];
									right_contrast = pApp->ColorImageProcess->ColorInt[coun_strip].right_continuation[old_col_num];
									right_edge_point = pApp->ColorImageProcess->SectionTraceRight[coun_strip * MAX_COL_INT + old_col_num];
									label_sign = pApp->ColorImageProcess->ColorInt[coun_strip].label_segments[old_col_num];
									NumSideHues = (NUM_HUES / 3);
									if (bunch_average_hue > 47)
									{
										bunch_average_hue -= 48;
									}
									SideTriangle = bunch_average_hue / NumSideHues;
									SideHue = bunch_average_hue - NumSideHues * SideTriangle;
									if (SideTriangle == 0)
									{
										Coor1 = 255 - CoorHuPoints[SideHue];
										Coor2 = CoorHuPoints[SideHue];
										Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
										Scoor2 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
										Scoor3 = (84 * (15 - bunch_average_sat)) / 15;
										Imax = max(Scoor1, max(Scoor2, Scoor3));
										Scoor1 = (Scoor1 * 255) / Imax;
										Scoor2 = (Scoor2 * 255) / Imax;
										Scoor3 = (Scoor3 * 255) / Imax;
										PeakColor4 = RGB(Scoor1, Scoor2, Scoor3);
										GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
										GrayLev = GrayLev / 4;
										if (GrayLev > bunch_average_gray)
										{

											NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
											NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
											NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
											NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
										Coor1 = 255 - CoorHuPoints[SideHue];
										Coor2 = CoorHuPoints[SideHue];
										Scoor1 = (84 * (15 - bunch_average_sat)) / 15;
										Scoor2 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
										Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
										Imax = max(Scoor1, max(Scoor2, Scoor3));
										Scoor1 = (Scoor1 * 255) / Imax;
										Scoor2 = (Scoor2 * 255) / Imax;
										Scoor3 = (Scoor3 * 255) / Imax;
										PeakColor4 = RGB(Scoor1, Scoor2, Scoor3);
										GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
										GrayLev = GrayLev / 4;
										if (GrayLev > bunch_average_gray)
										{
											NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
											NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
											NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
											NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
										Coor1 = CoorHuPoints[SideHue];
										Coor2 = 255 - CoorHuPoints[SideHue];
										Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
										Scoor2 = (84 * (15 - bunch_average_sat)) / 15;
										Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
										Imax = max(Scoor1, max(Scoor2, Scoor3));
										Scoor1 = (Scoor1 * 255) / Imax;
										Scoor2 = (Scoor2 * 255) / Imax;
										Scoor3 = (Scoor3 * 255) / Imax;
										PeakColor4 = RGB(Scoor1, Scoor2, Scoor3);
										GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
										GrayLev = GrayLev / 4;
										if (GrayLev > bunch_average_gray)
										{
											NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
											NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
											NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
											NewGrayLev = int(0.3 * ((float)NScoor1) + 0.59 * ((float)NScoor2) + 0.11 * ((float)NScoor3));
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
									//PeakColor3=RGB(NScoor1,NScoor2, NScoor3);
									if (((bunch_average_gray <= 5) && (NScoor1 > NScoor2) && (NScoor1 > NScoor3)) ||
										((bunch_average_gray <= 3) && (bunch_average_sat <= 1)))
									{//last_cor13.11.1729.11.17						
										NScoor1 = 10;
										NScoor2 = 10;
										NScoor3 = 10;
									}
									else
									{
										if ((bunch_average_gray >= 58) && (bunch_average_sat <= 1))
										{//last_cor13.11.1729.11.17
											NScoor1 = min(min(NScoor1, NScoor2), NScoor3);
											NScoor2 = NScoor1;
											NScoor3 = NScoor1;
										}
									}
									OldNum = pApp->ColorImageProcess->ColorInt[coun_strip].OldNumbers;
									PeakColor3 = RGB(NScoor1, NScoor2, NScoor3);

									pHuePen1 = new CPen(PS_SOLID, 3, PeakColor3);

									POldPen = pDC->SelectObject(pHuePen1);
									HorizVert = pApp->HorizontalVertical;
									if (HorizVert)
									{//horvert
										OrPoint.y = (WMHeight - Beg_bunch);
										if (bunch_occurrence > 0)
										{
											OrPoint.x = (StripWidthPrev1 * coun_strip + StripWidth1 / 2) - 1;
										}
										else
										{
											OrPoint.x = (StripWidthPrev1 * coun_strip + StripWidth1 / 2) + 3;
										}
										//OrPoint.x=StripWidthPrev1*coun_strip + StripWidth1/2;
										pDC->MoveTo(OrPoint);
										EndPoint.x = OrPoint.x;
										EndPoint.y = WMHeight - End_bunch;
										NewEndPoint = EndPoint;
										pDC->LineTo(EndPoint);
										if (right_contrast < 0)
										{
											pDC->MoveTo(EndPoint);
											NewOrPoint.x = EndPoint.x - min(5, StripWidth / 2);
											NewOrPoint.y = EndPoint.y;
											pDC->LineTo(NewOrPoint);
											if (right_edge_point > 1000)
											{
												pDC->Ellipse(EndPoint.x - min(5, StripWidth / 2), EndPoint.y - min(5, StripWidth / 2),
													EndPoint.x + min(5, StripWidth / 2), EndPoint.y + min(5, StripWidth / 2));
											}
										}
										if (left_contrast < 0)
										{//lc<
											pDC->MoveTo(OrPoint);
											EndPoint.x = OrPoint.x - min(5, StripWidth / 2);
											EndPoint.y = OrPoint.y;
											pDC->LineTo(EndPoint);
											if (left_edge_point > 1000)
											{
												pDC->Ellipse(OrPoint.x - min(5, StripWidth / 2), OrPoint.y - min(5, StripWidth / 2),
													OrPoint.x + min(5, StripWidth / 2), OrPoint.y + min(5, StripWidth / 2));
											}
										}//lc<
										CnPoint.x = OrPoint.x;
										CnPoint.y = OrPoint.y + (NewEndPoint.y - OrPoint.y) / 2;
										New1CnPoint.y = CnPoint.y;
										New2CnPoint.y = CnPoint.y;
										New1CnPoint.x = CnPoint.x - min(10, StripWidth / 2);
										New2CnPoint.x = CnPoint.x + min(10, StripWidth / 2);
										if (label_sign >= 3)
										{
											pDC->MoveTo(New1CnPoint);
											pDC->LineTo(New2CnPoint);
										}
									}//horvert
									else
									{//ehorvert
										OrPoint.x = Beg_bunch;
										if (bunch_occurrence > 0)
										{
											OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip + StripWidth1 / 2) - 1;
										}
										else
										{
											OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip + StripWidth1 / 2) + 3;
										}
										//OrPoint.y = WMHeight - (StripWidthPrev1*coun_strip + StripWidth1/2);
										pDC->MoveTo(OrPoint);
										EndPoint.x = End_bunch;
										EndPoint.y = OrPoint.y;
										NewEndPoint = EndPoint;
										pDC->LineTo(EndPoint);
										if (right_contrast < 0)
										{//rc<0
											pDC->MoveTo(EndPoint);
											NewOrPoint.x = EndPoint.x;
											NewOrPoint.y = EndPoint.y - min(5, StripWidth / 2);
											pDC->LineTo(NewOrPoint);
											if (right_edge_point > 1000)
											{
												pDC->Ellipse(EndPoint.x - min(5, StripWidth / 2), EndPoint.y - min(5, StripWidth / 2),
													EndPoint.x + min(5, StripWidth / 2), EndPoint.y + min(5, StripWidth / 2));
											}
										}//rc<0
										if (left_contrast < 0)
										{//lc<
											pDC->MoveTo(OrPoint);
											EndPoint.x = OrPoint.x;
											EndPoint.y = OrPoint.y - min(5, StripWidth / 2);
											pDC->LineTo(EndPoint);
											if (left_edge_point > 1000)
											{
												pDC->Ellipse(OrPoint.x - min(5, StripWidth / 2), OrPoint.y - min(5, StripWidth / 2),
													OrPoint.x + min(5, StripWidth / 2), OrPoint.y + min(5, StripWidth / 2));
											}
										}//lc<
										CnPoint.y = OrPoint.y;
										CnPoint.x = OrPoint.x + (NewEndPoint.x - OrPoint.x) / 2;
										New1CnPoint.x = CnPoint.x;
										New2CnPoint.x = CnPoint.x;
										New1CnPoint.y = CnPoint.y - min(10, StripWidth / 2);
										New2CnPoint.y = CnPoint.y + min(10, StripWidth / 2);
										if ((label_sign >= 3) && (label_sign <= 10) || ((label_sign >= 13) && (label_sign <= 20)))
										{
											pDC->MoveTo(New1CnPoint);
											pDC->LineTo(New2CnPoint);
										}
									}//ehorvert

									pDC->SelectObject(POldPen);

									delete pHuePen1;
									 
								}//restrict_bn

							}//bunch_loop
						}//strip_loop

						HorizVert = pApp->HorizontalVertical;

						if (!HorizVert)
						{//horizvert  
							COLORREF PeakColor5;
							NScoor1 = 255;
							NScoor2 = 100;
							NScoor3 = 100;
							PeakColor5 = RGB(NScoor1, NScoor2, NScoor3);
							CPen* pHuePen2 = new CPen(PS_SOLID, 4, PeakColor5);
							POldPen = pDC->SelectObject(pHuePen2);
							for (int coun_strip1 = 0; coun_strip1 < NumStrips; coun_strip1++) //draw color bunches
							{//strip_loop
								old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip1].NumberOfColoredIntervals;
								bunch_number1 = pApp->ColorImageProcess->ColorInt[coun_strip1].RefinedNumberOfBunches;
								old_col_number = pApp->ColorImageProcess->ColorInt[coun_strip1].NumberOfColoredIntervals;
								StripWidth1 = CurrentStrip[coun_strip1].StripWidth;
								StripWidthPrev1 = CurrentStrip[coun_strip1].StripWidthPrev;
								left_green_boun_bunch = pApp->ColorImageProcess->LeftGreenBoundaryBunch[coun_strip1];
								right_green_boun_bunch = pApp->ColorImageProcess->RightGreenBoundaryBunch[coun_strip1];

								if (left_green_boun_bunch > 0)
								{
									left_green_boun_bunch--;
								}
								else
								{
									left_green_boun_bunch = -1;
								}

								if (right_green_boun_bunch > 0)
								{
									right_green_boun_bunch--;
								}
								else
								{
									right_green_boun_bunch = -1;
								}

								for (int coun_bunch2 = 0; coun_bunch2 < bunch_number1; coun_bunch2++) //draw color bunches
								{//bunch_loop
									old_col_num = pApp->ColorImageProcess->ColorInt[coun_strip1].old_bunch_number[coun_bunch2];
									if (old_col_num < old_col_number)
									{//restrict_bn
										Beg_bunch =
											pApp->ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->BegInterv[old_col_num];
										End_bunch =
											pApp->ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->EndInterv[old_col_num];
										bunch_occurrence = pApp->ColorImageProcess->ColorInt[coun_strip1].visible_bunches[old_col_num];

										HorizVert = pApp->HorizontalVertical;

										if ((left_green_boun_bunch >= 0) || (right_green_boun_bunch >= 0))
										{//lgb||rgb
											if ((left_green_boun_bunch == old_col_num) && (left_green_boun_bunch >= 0))
											{//ldb=
												if (HorizVert)
												{//horvert
													OrPoint.y = (WMHeight - End_bunch);
													OrPoint.x = (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													pDC->MoveTo(OrPoint);
													EndPoint.x = OrPoint.x - min(5, StripWidth / 2);
													EndPoint.y = OrPoint.y;
													pDC->LineTo(EndPoint);
												}//horvert
												else
												{//ehorvert
													OrPoint.x = End_bunch;
													OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													pDC->MoveTo(OrPoint);
													EndPoint.x = OrPoint.x;
													EndPoint.y = OrPoint.y - min(5, StripWidth / 2);
													pDC->LineTo(EndPoint);
												}//ehorvert	
											}//ldb=
											if ((right_green_boun_bunch == old_col_num) && (right_green_boun_bunch >= 0))
											{//rgb=
												if (HorizVert)
												{//horvert

													OrPoint.y = (WMHeight - Beg_bunch);
													OrPoint.x = (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													EndPoint.x = OrPoint.x;
													EndPoint.y = WMHeight - Beg_bunch;
													pDC->MoveTo(EndPoint);
													NewOrPoint.x = EndPoint.x - min(5, StripWidth / 2);
													NewOrPoint.y = EndPoint.y;
													pDC->LineTo(NewOrPoint);
												}//horvert
												else
												{//ehorvert
													OrPoint.x = Beg_bunch;
													OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip1 + StripWidth1 / 2) - 1;
													EndPoint.x = Beg_bunch;
													EndPoint.y = OrPoint.y;
													NewEndPoint = EndPoint;
													pDC->MoveTo(EndPoint);
													NewOrPoint.x = EndPoint.x;
													NewOrPoint.y = EndPoint.y - min(5, StripWidth / 2);
													pDC->LineTo(NewOrPoint);
												}//ehorvert	
											}//rgb=

										}//lgb||rgb
									}//restrict_bn

								}//bunch_loop
							}//strip_loop
							pDC->SelectObject(POldPen);
							delete pHuePen2;
						}//horizvert


						VertFind = pApp->ColorImageProcess->VertFinding;
						if (VertFind)
						{//vertfind
							CPen* pHuePen4;
							COLORREF PeakColor6;
							NScoor1 = 0;
							NScoor2 = 100;
							NScoor3 = 255;
							PeakColor6 = RGB(NScoor1, NScoor2, NScoor3);
							pHuePen4 = new CPen(PS_SOLID, 4, PeakColor6);
							POldPen = pDC->SelectObject(pHuePen4);
							NumberVLines = pApp->ColorImageProcess->NumberOfVertLines;
							HorizVert = pApp->HorizontalVertical;


							for (int vert_number = 0; vert_number < NumberVLines; vert_number++) //draw vertical lines
							{//vert_loop
								length_of_vert_line = pApp->ColorImageProcess->VerticalLinesLength[vert_number];
								if (!length_of_vert_line)
								{
									goto D;
								}
								if (length_of_vert_line > 0)
								{//length>
									first_vert_line_strip = pApp->ColorImageProcess->VertLineFirstStrip[vert_number];
									if (first_vert_line_strip > 0)
									{
										first_vert_line_strip -= 1;
									}
									else
									{
										goto L;
									}
									for (int vert_count = 0; vert_count < length_of_vert_line; vert_count++) //draw particular vert line
									{//line_loop
										line_member = pApp->ColorImageProcess->VerticalContrastCurves[24 * vert_number + vert_count];
										if (!line_member)
										{
											break;
										}
										if (line_member > 0)
										{//linemember>
											line_member -= 1;
											coun_strip_v = first_vert_line_strip + vert_count;
											StripWidth1 = pApp->ColorImageProcess->CurStrip[coun_strip_v].StripWidth;
											StripWidthPrev1 = pApp->ColorImageProcess->CurStrip[coun_strip_v].StripWidthPrev;
											line_member_old =
												pApp->ColorImageProcess->ColorInt[coun_strip_v].old_ordered_bunch_number[line_member];
											line_member_old_beg =
												pApp->ColorImageProcess->ColorInt[coun_strip_v].ColoredIntervalsStructure->BegInterv[line_member_old];
											line_member_old_end =
												pApp->ColorImageProcess->ColorInt[coun_strip_v].ColoredIntervalsStructure->EndInterv[line_member_old];
											if (HorizVert)
											{//horvert
												OrPoint.y = (WMHeight - line_member_old_end);
												OrPoint.x = (StripWidthPrev1 * coun_strip_v + StripWidth1 / 2) - 1;
												pDC->MoveTo(OrPoint);
												EndPoint.x = OrPoint.x - min(5, StripWidth1 / 2);
												EndPoint.y = OrPoint.y;
												pDC->LineTo(EndPoint);
											}//horvert
											else
											{//ehorvert
												OrPoint.x = line_member_old_end;
												OrPoint.y = WMHeight - (StripWidthPrev1 * coun_strip_v + StripWidth1 / 2) - 1;
												pDC->MoveTo(OrPoint);
												EndPoint.x = OrPoint.x;
												EndPoint.y = OrPoint.y - min(5, StripWidth1 / 2);
												pDC->LineTo(EndPoint);
											}//ehorvert	
										}//linemember>
									}//line_loop
								}//length>
							}//vert_loop
						D:;
							pDC->SelectObject(POldPen);
							delete pHuePen4;
						}//vertfind

						return; 
					}

					if (colorBunchNum >= bunch_number)
					{
						colorBunchNum = 0;
					}

					blocking_bunch = pApp->ColorImageProcess->ColorInt[StripNumber].bunch_blocking;
					old_col_num    = pApp->ColorImageProcess->ColorInt[StripNumber].old_bunch_number[colorBunchNum];

					if (old_col_num < old_col_number)
					{
						bunch_average_hue = pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageHue[old_col_num];
						bunch_average_sat = pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageSat[old_col_num];
						bunch_average_gray = pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->AverageGray[old_col_num];

						Beg_bunch = pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->BegInterv[old_col_num];
						End_bunch = pApp->ColorImageProcess->ColorInt[StripNumber].ColoredIntervalsStructure->EndInterv[old_col_num];

						left_contrast  = pApp->ColorImageProcess->ColorInt[StripNumber].left_continuation[old_col_num];
						right_contrast = pApp->ColorImageProcess->ColorInt[StripNumber].right_continuation[old_col_num];

						NumSideHues = (NUM_HUES / 3);

						if (bunch_average_hue > 47)
						{
							bunch_average_hue -= 48;
						}

						SideTriangle = bunch_average_hue / NumSideHues;
						SideHue = bunch_average_hue - NumSideHues * SideTriangle;

						if (SideTriangle == 0)
						{
							Coor1 = 255 - CoorHuPoints[SideHue];
							Coor2 = CoorHuPoints[SideHue];
							Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
							Scoor2 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
							Scoor3 = (84 * (15 - bunch_average_sat)) / 15;
							Imax = max(Scoor1, max(Scoor2, Scoor3));
							Scoor1 = (Scoor1 * 255) / Imax;
							Scoor2 = (Scoor2 * 255) / Imax;
							Scoor3 = (Scoor3 * 255) / Imax;
							PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
							GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
							GrayLev = GrayLev / 4;
							if (GrayLev > bunch_average_gray)
							{

								NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
								NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
								NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
								NewGrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
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
							Coor1 = 255 - CoorHuPoints[SideHue];
							Coor2 = CoorHuPoints[SideHue];
							Scoor1 = (84 * (15 - bunch_average_sat)) / 15;
							Scoor2 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
							Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;
							Imax = max(Scoor1, max(Scoor2, Scoor3));
							Scoor1 = (Scoor1 * 255) / Imax;
							Scoor2 = (Scoor2 * 255) / Imax;
							Scoor3 = (Scoor3 * 255) / Imax;
							PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);
							GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
							GrayLev = GrayLev / 4;
							if (GrayLev > bunch_average_gray)
							{
								NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
								NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
								NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
								NewGrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
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
							Coor1 = CoorHuPoints[SideHue];
							Coor2 = 255 - CoorHuPoints[SideHue];
							Scoor1 = 84 + (bunch_average_sat * (Coor1 - 84)) / 15;
							Scoor2 = (84 * (15 - bunch_average_sat)) / 15;
							Scoor3 = 84 + (bunch_average_sat * (Coor2 - 84)) / 15;

							Imax = max(Scoor1, max(Scoor2, Scoor3));

							Scoor1 = (Scoor1 * 255) / Imax;
							Scoor2 = (Scoor2 * 255) / Imax;
							Scoor3 = (Scoor3 * 255) / Imax;

							PeakColor2 = RGB(Scoor1, Scoor2, Scoor3);

							GrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
							GrayLev = GrayLev / 4;

							if (GrayLev > bunch_average_gray)
							{
								NScoor1 = (Scoor1 * bunch_average_gray) / GrayLev;
								NScoor2 = (Scoor2 * bunch_average_gray) / GrayLev;
								NScoor3 = (Scoor3 * bunch_average_gray) / GrayLev;
								NewGrayLev = int(0.3 * ((float)Scoor1) + 0.59 * ((float)Scoor2) + 0.11 * ((float)Scoor3));
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

						PeakColor1 = RGB(NScoor1, NScoor2, NScoor3);
						OldNum = pApp->ColorImageProcess->ColorInt[StripNumber].OldNumbers;

						pen.CreatePen(PS_SOLID, 3, PeakColor1);

						POldPen = pDC->SelectObject(&pen);
						HorizVert = pApp->HorizontalVertical;
						
						if (HorizVert)
						{
							OrPoint.y = (WMHeight - Beg_bunch);

							OrPoint.x = StripWidthPrev * StripNumber + StripWidth / 2;
							pDC->MoveTo(OrPoint);
							EndPoint.x = OrPoint.x;
							EndPoint.y = WMHeight - End_bunch;
							pDC->LineTo(EndPoint);

							if (right_contrast < 0)
							{
								pDC->MoveTo(EndPoint);
								NewOrPoint.x = EndPoint.x - min(5, StripWidth / 2);
								NewOrPoint.y = EndPoint.y;
								pDC->LineTo(NewOrPoint);
							}
							if (left_contrast < 0)
							{
								pDC->MoveTo(OrPoint);
								EndPoint.x = OrPoint.x - min(5, StripWidth / 2);
								EndPoint.y = OrPoint.y;
								pDC->LineTo(EndPoint);
							}
						}
						else
						{
							OrPoint.x = Beg_bunch;
							OrPoint.y = WMHeight - (StripWidthPrev * StripNumber + StripWidth / 2);

							pDC->MoveTo(OrPoint);

							EndPoint.x = End_bunch;
							EndPoint.y = OrPoint.y;

							pDC->LineTo(EndPoint);

							if (right_contrast < 0)
							{
								pDC->MoveTo(EndPoint);
								NewOrPoint.x = EndPoint.x;
								NewOrPoint.y = EndPoint.y - min(5, StripWidth / 2);
								pDC->LineTo(NewOrPoint);
							}
							if (left_contrast < 0)
							{
								pDC->MoveTo(OrPoint);
								EndPoint.x = OrPoint.x;
								EndPoint.y = OrPoint.y - min(5, StripWidth / 2);
								pDC->LineTo(EndPoint);
							}
						}
						pDC->SelectObject(POldPen);
					}
				}
				else if (1 == pApp->m_pBunchCountDialog->radioBtnGrayBunch.GetCheck())
				{ 
					pen.CreatePen(PS_SOLID, 5, RGB(240, 20, 20));
					pDC->SelectObject(&pen);
					grayBunchNum = pApp->m_pBunchCountDialog->m_grayBunchNum; 
					 
					OrPoint.x = CurrentStrip->bursts[grayBunchNum].beg;
					OrPoint.y = WMHeight - (StripWidthPrev * StripNumber + StripWidth / 2);

					pDC->MoveTo(OrPoint);

					EndPoint.x = CurrentStrip->bursts[grayBunchNum].end;
					EndPoint.y = OrPoint.y;

					pDC->LineTo(EndPoint); 
				} 
			}
		}
	}
}



/////////////////////////////////////////////////////////////////////////////
// CViewImageVw message handlers

void CViewImageVw::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//	RECT Rect;
	CPoint ShiftDimensions;
	//CPoint Curpoint;

	//GetClientRect (&Rect);
	ShiftDimensions = GetDeviceScrollPosition();
	if (ImageRepresentationType == 0)
	{
		ImageRect.left = max(0, (WindowShift.x - ShiftDimensions.x));
		ImageRect.top = max(0, (WindowShift.y - ShiftDimensions.y));


		ImageRect.bottom = WindowShift.y + WMHeight - ShiftDimensions.y;
		ImageRect.right = WindowShift.x + WMWidth - ShiftDimensions.x;
		if (ImageRect.PtInRect(point))
		{

			::SetCursor(m_HCross);
		}

		CScrollView::OnMouseMove(nFlags, point);
	}
}



// Calculates of a given point's color characteristics
void CViewImageVw::Calculate(CPoint point, unsigned char *RedComp, unsigned char *GreenComp,
	unsigned char * BlueComp, int *HueComp, int *GrayComp, float *SaturComp)
{
	unsigned char RComp, GComp, BComp;
	//int HComp;
	float SComp;
	int minRGB;
	float H;
	int VComp;
	int Cor_Width;
	int Res_Width;
	
	CColorVisionApp *pApp;
	
	unsigned char *LineAddr;
	long linear_shift;
	POINT Coord;

	Coord.x = point.x - WindowShift.x;
	Coord.y = (int)WMHeight - point.y + WindowShift.y;
	
	if (Coord.y >= WMHeight)
	{
		RComp = 0;
		GComp = 0;
		BComp = 0;
		VComp = 0;
		SComp = 0;
		*HueComp = -1;
		goto L;;
	}
	
	Res_Width = (3 * ((int)WMWidth)) % 4;
	
	if (Res_Width)
	{
		Cor_Width = 4 - Res_Width;
	}
	else
	{
		Cor_Width = 0;
	}
	pApp = (CColorVisionApp *)AfxGetApp();
	LineAddr = (unsigned char *)pApp->pm_BitmapApp->bmBits;
	linear_shift = (long)((3 * WMWidth + Cor_Width)*Coord.y) + (long)(3 * Coord.x);

	RComp = LineAddr[linear_shift + 2];
	GComp = LineAddr[linear_shift + 1];
	BComp = LineAddr[linear_shift];
	
	VComp = max(max(RComp, GComp), BComp);
	minRGB = min(min(RComp, GComp), BComp);
	
	if (VComp > 0) 
		SComp = ((float)(VComp - minRGB)) / (float)VComp;
	else       
		SComp = 0;

	if (VComp == minRGB) 
		H = 0;
	else 
	{
		if (VComp == RComp)
			H = (float)(GComp - BComp) / (VComp - minRGB);
		else if (VComp == GComp)
			H = 2 + (float)(BComp - RComp) / (VComp - minRGB);
		else if (VComp == BComp)
			H = 4 + (float)(RComp - GComp) / (VComp - minRGB);

		H = H * 60;   // put H into degrees
		if (H < 0) H += 360;
	}
	H = (47 * H) / 360;
	*HueComp = (int)H;
	VComp = (0.3*RComp + 0.59*GComp + 0.11*BComp) / 4;
L:
	*RedComp = RComp;
	*GreenComp = GComp;
	*BlueComp = BComp;
	*GrayComp = VComp;
	*SaturComp = SComp;
}



// Draws clicked point's coordinates and color characteristics 
void CViewImageVw::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	unsigned char Red, Green, Blue, gb, gr;
	int   Hue, V;
	float Saturation;
	int StrWidth;
	int StrWidthPrev;
	CBrush WBrush;
	CPen   RPen;
	CBrush* PtrOldBrush;
	CPen* PtrOldPen;
	POINT CenterPoint;
	CPoint point1;
	CPoint ShiftDimensions;
	int Height;
	int NumStr;

	pApp = (CColorVisionApp *)AfxGetApp();
	
	if (ImageRepresentationType == 0)
	{
		CClientDC dc(this);
		 
		if (ImageRect.PtInRect(point))
		{
			ShiftDimensions = GetDeviceScrollPosition();
			point1 = point + ShiftDimensions;
			
			Calculate(point1, &Red, &Green, &Blue, &Hue, &V, &Saturation);
			
			if (Hue == -1)
			{
				return;
			}

			if (Blue + Green != 0)
			{
				gb = (unsigned char)(255 * (long)Green / (Blue + Green));
				gb = gb / 4;
			}
			else
			{
				gb = 0;
			}
			if (Red + Green != 0)
			{
				gr = (unsigned char)(255 * (long)Green / (Red + Green));
				gr = gr / 4;
			}
			else
			{
				gr = 0;
			}

			CScrollView::OnLButtonDown(nFlags, point);


			HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FONT);
			CFont fnt;
			CFont* pFont = fnt.FromHandle(hFont);
			CFont* pfntOld = dc.SelectObject(pFont);
			POINT Coord;
			TEXTMETRIC tm;
			POINT Text_Origin;
			long Symbol_width;
			CWnd *p_Wnd;


			if (dc.GetTextMetrics(&tm))
			{
				p_Wnd = dc.GetWindow();
				p_Wnd->Invalidate();
				p_Wnd->UpdateWindow();
				Coord.x = point1.x - WindowShift.x;
				Coord.y = (int)WMHeight - point1.y + WindowShift.y;
				Symbol_width = tm.tmAveCharWidth;
				Text_Origin.y = tm.tmHeight + 1;
				Text_Origin.x = 5;
				str = "x";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += Symbol_width;
				str1.Format("=%d", (int)Coord.x);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "y";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += Symbol_width;
				str1.Format("=%d", (int)Coord.y);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "r";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += Symbol_width;
				str1.Format("=%d", (int)Red);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "g";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += Symbol_width;
				str1.Format("=%d", (int)Green);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "b";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += Symbol_width;
				str1.Format("=%d", (int)Blue);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "gb";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += 2 * Symbol_width;
				str1.Format("=%d", (int)gb);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "gr";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += 2 * Symbol_width;
				str1.Format("=%d", (int)gr);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "H";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += 2 * Symbol_width;
				str1.Format("=%d", Hue);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "V";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += 2 * Symbol_width;
				str1.Format("=%d", V);
				dc.TextOut((int)Text_Origin.x, 1, str1);
				Text_Origin.x += 5 * Symbol_width;
				str = "S";
				dc.TextOut((int)Text_Origin.x, 1, str);
				Text_Origin.x += 2 * Symbol_width;
				str1.Format("=%4.2f", Saturation);
				dc.TextOut((int)Text_Origin.x, 1, str1);

			}
			dc.SelectObject(pfntOld);

		}
		RPen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
		WBrush.CreateSolidBrush(RGB(255, 0, 0));
		PtrOldPen = dc.SelectObject(&RPen);
		PtrOldBrush = dc.SelectObject(&WBrush);

		if (pApp->ColorImageProcess != NULL)
		{
			HorizVert = pApp->ColorImageProcess->HorizontalVertical;
		}
		else
		{
			HorizVert = pApp->HorizontalVertical;
		}

		if ((((point.x >= ImageRect.left) && (point.x <= ImageRect.right) &&
			(point.y>ImageRect.bottom) && (point.y <= ImageRect.bottom + 12) && (HorizVert))
			|| ((point.x>ImageRect.right) && (point.x<ImageRect.right + 12) &&
			(point.y >= ImageRect.top) && (point.y <= ImageRect.bottom) && (!HorizVert)))
			&& ((pApp->m_ImageSegmented) &&
			((pApp->m_StripColorRepresentation) || (pApp->m_StripGrayRepresentation)
				|| (pApp->m_ColorBunchRepresentation) || (pApp->m_GrayScaleOpened))))
		{
			Height = pApp->ColorImageProcess->DimY;
			NumStr = pApp->ColorImageProcess->NumStrips;
			ShiftDimensions = GetDeviceScrollPosition();
			point1 = point + ShiftDimensions;
			StrWidthPrev = pApp->ColorImageProcess->CurStrip[0].StripWidthPrev;
			if (HorizVert)
			{
				NumClicked = (point1.x - WindowShift.x) / StrWidthPrev;
			}
			else
			{
				NumClicked = (Height - (point1.y - WindowShift.y)) / StrWidthPrev;
			}
			AreaWasClicked = TRUE;
			if (NumClicked >= NumStr)
			{
				NumClicked = NumStr - 1;
			}
			pApp->NumberStripClicked = NumClicked;
			StrWidth = pApp->ColorImageProcess->CurStrip[NumClicked].StripWidth;

			CDocument* pDoc1 = pApp->pDocGrayscaleImage;
			CDocument* pDocs1 = pApp->pDocs1;
			CDocument* pDocs2 = pApp->pDocs2;
			CDocument* pDocs3 = pApp->pDocs3;
			CDocument* pDocCSec1 = pApp->pDocColSec1;


			if (pDocs1 != NULL)
			{
				pDocs1->UpdateAllViews(NULL);
			}

			if (pDocs2 != NULL)
			{
				pDocs2->UpdateAllViews(NULL);
			}
			if (pDocs3 != NULL)
			{
				pDocs3->UpdateAllViews(NULL);

			}
			if (pDoc1 != NULL)
			{
				pDoc1->UpdateAllViews(NULL);
			}

			int ElWid;
			CWnd *p_Wnd1;
			p_Wnd1 = dc.GetWindow();
			p_Wnd1->Invalidate();
			p_Wnd1->UpdateWindow();
			ShiftDimensions = GetDeviceScrollPosition();


			ElWid = min(StrWidth, 6);
			if (HorizVert)
			{
				CenterPoint.x = WindowShift.x + (StrWidthPrev)*NumClicked + StrWidth / 2;
				CenterPoint.y = WMHeight + WindowShift.y + ElWid - 1;
			}
			else
			{
				CenterPoint.x = WMWidth + WindowShift.x + ElWid;
				CenterPoint.y = WMHeight + WindowShift.y - (StrWidthPrev)*(NumClicked)-StrWidth / 2;
			}
			CenterPoint.x -= ShiftDimensions.x;
			CenterPoint.y -= ShiftDimensions.y;
			dc.Ellipse(CenterPoint.x - 6, CenterPoint.y - 6, CenterPoint.x + 6, CenterPoint.y + 6);
			//return;
		}
		dc.SelectObject(PtrOldPen);
		dc.SelectObject(PtrOldBrush); 
	} 
}




/////////////////////////////////////////////////////////////////////////////
// CViewImageVw diagnostics

#ifdef _DEBUG
void CViewImageVw::AssertValid() const
{
	CScrollView::AssertValid();
}

void CViewImageVw::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CViewImageDoc* CViewImageVw::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewImageDoc)));
	return (CViewImageDoc*)m_pDocument;
}

#endif //_DEBUG
