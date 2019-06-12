#include "VideoImageInputDoc.h"

#pragma once

/*static int CoorHuPoints[16]= {7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183, 
199, 215, 231, 247
};*/

// CVideoImageInputView view

class CVideoImageInputView : public CView
{
	DECLARE_DYNCREATE(CVideoImageInputView)

protected:
	CVideoImageInputView();           // protected constructor used by dynamic creation
	virtual ~CVideoImageInputView();
// Operations
public:
	CVideoImageInputDoc* GetDocument ();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoImageInputView)
public:
	virtual 
		void OnDraw(CDC* pDC);      // overridden to draw this view
protected:
	
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL
	//virtual void OnUpdate(CView* pSender,LPARAM lHint,CObject* pHint);


public:
	BOOL CameraImageLoaded;
	CColorVisionApp *pApp;
	CVideoImageInputDoc* pDoc;
	CString strTitle;
	CString m_CannotDisp;
	CString m_CannotDispOut;
	int VideoImageRepresentationType;
	int VideoImageProcessedNumber;

public:

BOOL
  CameraInputDraw(CDC* pDC);
/*void
DirectArrayDraw();*/

/*BOOL
  
CVideoImageInputView::CameraInputDraw();*/
BOOL
 
CameraOutputDraw(CDC* pDC);

void

CalculateBrush(int side_triangle,int side_hue,int BunAverSat,int BunAverGr,
int* scoor1,int* scoor2,int* scoor3,int* nscoor1,int* nscoor2,int* nscoor3);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//#endif

protected:
	DECLARE_MESSAGE_MAP()
};