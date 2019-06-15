#if !defined(AFX_VIEWIMAGEVW_H__73776B00_0DC3_4C1F_9716_68EEFE838F00__INCLUDED_)
#define AFX_VIEWIMAGEVW_H__73776B00_0DC3_4C1F_9716_68EEFE838F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewImageVw.h : header file
//
/*static int CoorHuPoints[16]= {7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183,
199, 215, 231, 247
};*/
/////////////////////////////////////////////////////////////////////////////
// CViewImageVw view

class CViewImageVw : public CScrollView
{
protected:
	CViewImageVw();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewImageVw)
protected:
	int m_Dragging;
	HCURSOR m_HArrow;
	HCURSOR m_HCross;
	CPoint   WindowShift;
	long WMHeight;
	long WMWidth;
	BOOL ImageLoaded;
	BOOL CameraImageLoaded;
	BOOL ImageIsSegmented;
	BOOL m_Video_ImageSegmented;
	BOOL AreaWasClicked;
	CRect ImageRect;
	BOOL HorizVert;
	int NumStrips;
	CColorVisionApp *pApp;
	CViewImageDoc* pDoc;
	CString str, str1;
	CString strTitle;
	int NumClicked;
	int ImageRepresentationType;
	CStrip* CurrentStrip;
	CString m_CannotDisp;
	CColorIntervalSelect* Bunches;
	CColorSection* SectInform;
	ColorSectionDescr* Sect1;
	// Attributes
public:
	void

		CViewImageVw::Calculate(CPoint point, unsigned char *RedComp, unsigned char *GreenComp,
			unsigned char *BlueComp, int *HueComp, int *GrayComp, float *SaturComp);

	//}

	// Operations
public:

	CViewImageDoc* CViewImageVw::GetDocument();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewImageVw)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
										//}}AFX_VIRTUAL

										// Implementation
protected:
	virtual ~CViewImageVw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewImageVw)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG
inline CViewImageDoc* CViewImageVw::GetDocument()
{
	return (CViewImageDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWIMAGEVW_H__73776B00_0DC3_4C1F_9716_68EEFE838F00__INCLUDED_)
