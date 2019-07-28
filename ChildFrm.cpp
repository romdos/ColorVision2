// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "ColorVision.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CViewImageFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CViewImageFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CViewImageFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CViewImageFrame::CViewImageFrame()
{
	// TODO: add member initialization code here
	
}

CViewImageFrame::~CViewImageFrame()
{
}

BOOL CViewImageFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    long WMHeight;
	long WMWidth;
	int ImageRepresentationType;

	CColorVisionApp *pApp;

	pApp= (CColorVisionApp *)AfxGetApp ();

    
	ImageRepresentationType = pApp->ImageRepresentationType;
	

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	if(ImageRepresentationType==0)
	{
	cs.x=2;
	cs.y=2;
    cs.cx=380+20;
    cs.cy=300+20;
	}
	if(ImageRepresentationType==1)
	{
	WMWidth=pApp->pm_BitmapApp->bmWidth;
	WMHeight=pApp->pm_BitmapApp->bmHeight;
	cs.x=2;
	cs.y=300+30+15;	//maxser +15
    cs.cx=WMWidth+40;
    cs.cy=WMHeight+60;
	
	}
	if(ImageRepresentationType==2)
	{
	cs.x=2;
	cs.y=2;
    cs.cx=340+100;	
    cs.cy=260;
	}
	if(ImageRepresentationType==3)
	{
	cs.x=380;
	cs.y=2;
    cs.cx=340;	
    cs.cy=260;
	}

	//cs.dwExStyle=WS_EX_LEFTSCROLLBAR |WS_EX_RIGHTSCROLLBAR;   
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CViewImageFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CViewImageFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
