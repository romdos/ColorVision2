// VizStripFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "VizStripFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVizStripFrame

IMPLEMENT_DYNCREATE(CVizStripFrame, CMDIChildWnd)

CVizStripFrame::CVizStripFrame()
{
CString Str;

CWnd* pWnd=GetActiveWindow( );
pWnd->GetWindowText(_T(Str));
}

CVizStripFrame::~CVizStripFrame()
{
}


BEGIN_MESSAGE_MAP(CVizStripFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CVizStripFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVizStripFrame message handlers

BOOL CVizStripFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	CString Str;
	
//Str = "Strip Interval Representation";	
	// TODO: Add your specialized code here and/or call the base class
//cs.lpszName =NULL;


    cs.x=2+320;
	cs.y=2;
    cs.cx=320;
    cs.cy=280;	
	if(CMDIChildWnd::PreCreateWindow(cs))
	{
CWnd* pWnd=GetActiveWindow( );
pWnd->GetWindowText(_T(Str));
return TRUE;
	}
	else
	{
		return FALSE;
	}
}
