#if !defined(AFX_GLOBALOBJECTSVIEW_H__7506D649_C917_4D7E_BC7E_1637A07F9500__INCLUDED_)
#define AFX_GLOBALOBJECTSVIEW_H__7506D649_C917_4D7E_BC7E_1637A07F9500__INCLUDED_

#include "GlobalObjectsDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobalObjectsView.h : header file
//
#define SPACEATLEFT    30   // reserved pixels at left   of Strip Details
#define SPACEATBOTTOM  20   // reserved pixels at bottom of Strip Details
#define X_TICKS        32   // number of ticks on axes X
#define Y_TICKS        16   //                           and Y
#define YSCALEMAX      16   //number of grades of ratios
#define NUMCLRS        16
#define NUMDATAPOINTS  10   //number of ratios for the bar chart
#define SPACEATTOP     20   //Reserved pixets at top of the chart
#define SPACEATRIGHT   20   //Reserved pixets at right of the chart
#define SPACEVERTICAL (SPACEATTOP + SPACEATBOTTOM)
#define SPACEHORIZONTAL (SPACEATLEFT + SPACEATRIGHT)
#define HALFSPACEATBOTTOM (SPACEATBOTTOM / 2)
#define HALFSPACEATRIGHT  (SPACEATRIGHT / 2)
#define YAXISX (SPACEATLEFT )
#define YAXISY (SPACEATBOTTOM/2)
#define YMARKERX1 (SPACEATLEFT - SPACEATLEFT / 8)
#define YMARKERX2 (YMARKERX1 +(SPACEATLEFT / 4))

static int CoorHuePoints1[16] = { 7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183,
199, 215, 231, 247
};
/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsView view

class CGlobalObjectsView : public CScrollView
{
protected:
	CGlobalObjectsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGlobalObjectsView)

	// Attributes
public:
	CStrip* CurrentStrip;
	CColorIntervalSelect* Bunches;
	ColorSectionDescr* Section;  // pointer to Section description
	CColorSection* SectInform;
	BOOL HorizVert;

private:
	int GlobalObjectsRepresentationType;
	//int NumSections;
	CColorVisionApp *pApp;
	CString strTitle;
	CString strCaptions;
	CDocument* pDoc;
	int NumOfSect;
	int ChosenSection;  // number of the section shown on the original image
	int Num_Levels;
	int NumberOfStrips;

	int         xBase, yBase;  // X and Y of the origin in the client area
	int         xMax, yMax;    // Maximum values of coordinates
	int         xIncr, yIncr;
	int         xMarkTick, yMarkTick;  // intervals between ticks on axes X and Y

									   // Operations
public:

	void

		CGlobalObjectsView::CalculateColor(int Hue, int Satur, int Gray, int* STCoor1, int* STCoor2,
			int* STCoor3, int* NTCoor1, int* NTCoor2, int* NTCoor3);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalObjectsView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

	// Implementation
public:
	void
		CGlobalObjectsView::SetMaxCoordinates();
protected:
	virtual ~CGlobalObjectsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGlobalObjectsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALOBJECTSVIEW_H__7506D649_C917_4D7E_BC7E_1637A07F9500__INCLUDED_)
