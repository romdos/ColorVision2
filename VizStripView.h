#if !defined(AFX_VIZSTRIPVIEW_H__A8E60B25_AC23_4FF5_A213_33E92274E93B__INCLUDED_)
#define AFX_VIZSTRIPVIEW_H__A8E60B25_AC23_4FF5_A213_33E92274E93B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VizStripView.h : header file
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

/*static COLORREF   RG[16]= {0x00000FFL, 0x00011FFL,0x00024FFL,0x0003AFFL,0x00055FFL,
0x00074FFL,0x00098FFL,0x000A2FFL,0x000FFA2L,0x000FF98L,0x000FF74L,0x000FF55L,
0x000FF3AL,0x000FF24L,0x000FF11L,0x000FF00L
};   //array of colors on the RG side
static COLORREF   GB[16]= {0x000FF00L, 0x011FF00L,0x024FF00L,0x03AFF00L,0x055FF00L,
0x074FF00L,0x098FF00L,0x0A2FF00L,0x0FFA200L,0x0FF9800L,0x0FF7400L,0x0FF5500L,
0x0FF3A00L,0x0FF2400L,0x0FF1100L,0x0FF0000L
};
//array of colors on the GB side
static COLORREF   RB[16]= {0x00000FFL, 0x01100FFL,0x02400FFL,0x03A00FFL,0x05500FFL,
0x07400FFL,0x09800FFL,0x0A200FFL,0x0FF00A2L,0x0FF0098L,0x0FF0074L,0x0FF0055L,
0x0FF003AL,0x0FF0024L,0x0FF0011L,0x0FF0000L
};    //array of colors on the RB side*/

static int CoorHuePoints[16] = { 7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183,
199, 215, 231, 247
};
/////////////////////////////////////////////////////////////////////////////
// CVizStripView view

class CVizStripView : public CScrollView
{
protected:
	CVizStripView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVizStripView)

	// Attributes
public:
	CStrip* CurrentStrip;
	int StripNumber;
	int BunchNumber;
	BOOL HorizVert;
	BOOL GGBorGGR;
	int Dimension;
	//CSpinButtonCtrl* MySpinner;
private:
	int         xBase, yBase;  // X and Y of the origin in the client area
	int         xMax, yMax;    // Maximum values of coordinates
	int         xIncr, yIncr;
	int         xMarkTick, yMarkTick;  // intervals between ticks on axes X and Y
	int         NumLevels;
	int         NumRatio;
	int         NumInterval;
	int         StripRepresentationType;
	int         PlotHeight;
	int         ProcTime;
	CColorVisionApp *pApp;
	CString strTitle;
	CString strCaptions;
	CString str, str1;
	CDocument* pDoc;
	CRect ImageRect;
	POINT TextOriginTop;
	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVizStripView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	virtual ~CVizStripView();
public:

	void
		CVizStripView::SetMaxCoordinates();

	BOOL

		CVizStripView::CalculateIntervalCharacteristics(CPoint point);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CVizStripView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIZSTRIPVIEW_H__A8E60B25_AC23_4FF5_A213_33E92274E93B__INCLUDED_)
